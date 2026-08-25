//
// Created by dayu on 2026/8/16.
//

// 完整实现搞清，智能指针、工厂模式、PIMPL、资源池、缓存系统、树结构等实际场景。
// 为什么需要智能指针---智能指针通过RAII（资源获取即初始化）机制，在对象销毁时自动释放内存。
// 三种核心智能指针：
// 1、unique_ptr（独占所有权）--最轻量、最常用的智能指针，不能拷贝，只能移动。
// 适用场景：对象有明确、唯一的所有者。
//
// 2、shared_ptr（共享所有权）--通过引用计数管理，最一个shared_ptr销毁时释放资源。
// 适用场景：多个对象共享资源，生命周期不确定。
//
// 3、weak_ptr（弱引用）--配合shared_ptr使用，不增加引用计数，用于打破循环引用。
//

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <map>
#include <optional>
#include <cassert>

// ============================================================
// 一、unique_ptr 的实际应用场景
// ============================================================

// 1.1 工厂模式 - 返回 unique_ptr 明确所有权转移
class Product {
public:
    Product(std::string name, int id)
        : name_(std::move(name)), id_(id) {
        std::cout << "创建产品: " << name_ << " (ID:" << id_ << ")\n";
    }
    virtual ~Product() {
        std::cout << "销毁产品: " << name_ << "\n";
    }

    virtual void operate() const = 0;
    const std::string& getName() const { return name_; }

protected:
    std::string name_;
    int id_;
};

class ConcreteProductA : public Product {
public:
    using Product::Product;
    void operate() const override {
        std::cout << "产品A [" << name_ << "] 执行操作\n";
    }
};


class ConcreteProductB : public Product {
public:
    using Product::Product;
    void operate() const override {
        std::cout << "产品B [" << name_ << "] 执行操作\n";
    }
};

// C++17 工厂：明确表达所有权转移
class ProductFactory {
public:
    enum class Type { A, B };

    // 使用 unique_ptr 返回，明确由调用者拥有
    static std::unique_ptr<Product> create(Type type, std::string name, int id) {
        switch (type) {
            case Type::A:
                return std::make_unique<ConcreteProductA>(std::move(name), id);
            case Type::B:
                return std::make_unique<ConcreteProductB>(std::move(name), id);
        }
        return nullptr;  // C++17允许[[fallthrough]]优化
    }
};

// 1.2 PIMPL 惯用法 - 隐藏实现细节
class DatabaseConnection {
    // 前向声明的实现类
    class Impl;
    std::unique_ptr<Impl> pImpl;  // 关键：持有实现指针

public:
    DatabaseConnection(std::string connStr);
    ~DatabaseConnection();  // 必须在Impl定义后实现析构函数
    DatabaseConnection(DatabaseConnection&&) noexcept = default;  // 移动语义
    DatabaseConnection& operator=(DatabaseConnection&&) noexcept = default;

    bool connect();
    std::string query(const std::string& sql);
    bool disconnect();
};

// 在cpp文件中定义实现（这里为演示放在一起）
class DatabaseConnection::Impl {
public:
    std::string connectionString;
    bool connected = false;

    Impl(std::string str) : connectionString(std::move(str)) {
        std::cout << "Impl 创建: " << connectionString << "\n";
    }
    ~Impl() { std::cout << "Impl 销毁\n"; }

    bool connect() {
        connected = true;
        std::cout << "连接数据库: " << connectionString << "\n";
        return true;
    }

    std::string query(const std::string& sql) {
        return "查询结果: [" + sql + "] 执行成功";
    }
};

DatabaseConnection::DatabaseConnection(std::string connStr)
    : pImpl(std::make_unique<Impl>(std::move(connStr))) {
    std::cout << "DatabaseConnection 创建\n";
}

DatabaseConnection::~DatabaseConnection() = default;  // unique_ptr自动释放Impl

bool DatabaseConnection::connect() { return pImpl->connect(); }
std::string DatabaseConnection::query(const std::string& sql) {
    return pImpl->query(sql);
}

// 1.3 自定义删除器的使用
class FileResource {
    FILE* file_;
    std::string filename_;

public:
    explicit FileResource(const std::string& filename)
        : filename_(filename) {
        file_ = fopen(filename.c_str(), "w+");
        std::cout << "打开文件: " << filename << "\n";
    }
    ~FileResource() {
        if (file_) {
            fclose(file_);
            std::cout << "关闭文件: " << filename_ << "\n";
        }
    }

    void write(const std::string& data) {
        if (file_) fputs(data.c_str(), file_);
    }
};

// 使用 unique_ptr 管理 FILE*，带自定义删除器
class FileManager {
    // C++17：用 lambda 作为删除器
    std::unique_ptr<FILE, std::function<void(FILE*)>> file_;

public:
    explicit FileManager(const std::string& path)
        : file_(fopen(path.c_str(), "w+"),
            [](FILE* f) {
                if (f) {
                    std::cout << "lambda删除器：关闭FILE*\n";
                    fclose(f);
                }
            }) {
        if (!file_) {
            throw std::runtime_error("无法打开文件: " + path);
        }
        std::cout << "FileManager 打开文件: " << path << "\n";
    }

    void writeData(const std::string& data) {
        fputs(data.c_str(), file_.get());
    }
};


// ============================================================
// 二、shared_ptr 的实际应用场景
// ============================================================

// 2.1 观察者模式 - 使用 shared_ptr 共享观察目标
class Subject {
public:
    using ObserverFunc = std::function<void(const std::string&)>;

    void addObserver(ObserverFunc func) {
        observers_.push_back(std::move(func));
    }

    void notify(const std::string& message) {
        for (auto& observer : observers_) {
            observer(message);
        }
    }

private:
    std::vector<ObserverFunc> observers_;
};

class SharedState {
    std::string state_;
    Subject subject_;

public:
    void setState(std::string newState) {
        state_ = std::move(newState);
        subject_.notify("状态更新: " + state_);
    }

    const std::string& getState() const { return state_; }
    Subject& getSubject() { return subject_; }
};

// 2.2 资源池 - 使用 shared_ptr 管理共享资源
class ResourcePool {
public:
    class Connection {
        int id_;
        bool busy_ = false;
    public:
        explicit Connection(int id) : id_(id) {
            std::cout << "创建连接 #" << id << "\n";
        }
        ~Connection() { std::cout << "销毁连接 #" << id_ << "\n"; }
        int getId() const { return id_; }
        void setBusy(bool b) { busy_ = b; }
        bool isBusy() const { return busy_; }
    };

    std::shared_ptr<Connection> acquire() {
        // 查找空闲连接
        for (auto& [conn, weak] : pool_) {
            if (auto shared = weak.lock()) {
                if (!shared->isBusy()) {
                    shared->setBusy(true);
                    std::cout << "获取连接 #" << shared->getId() << " (引用计数: "
                        << shared.use_count() << ")\n";
                    return shared;
                }
            }
        }

        // 创建新连接
        auto newConn = std::make_shared<Connection>(nextId_++);
        newConn->setBusy(true);
        pool_.push_back({ newConn, newConn });  // 存储weak_ptr用于查找
        std::cout << "新建连接 #" << newConn->getId() << "\n";
        return newConn;
    }

    void release(std::shared_ptr<Connection> conn) {
        if (conn) {
            conn->setBusy(false);
            std::cout << "释放连接 #" << conn->getId()
                << " (剩余引用计数: " << conn.use_count() - 1 << ")\n";
        }
    }

private:
    int nextId_ = 0;
    // C++17：结构化绑定会用到这个pair
    std::vector<std::pair<std::shared_ptr<Connection>, std::weak_ptr<Connection>>> pool_;
};


// ============================================================
// 三、weak_ptr 的实际应用场景
// ============================================================

// 3.1 缓存系统 - 使用 weak_ptr 实现自动清理缓存
template<typename Key, typename Value>
class WeakCache {
    std::map<Key, std::weak_ptr<Value>> cache_;

public:
    void put(const Key& key, std::shared_ptr<Value> value) {
        cache_[key] = value;
        std::cout << "缓存添加: " << key << " (引用计数: "
            << value.use_count() << ")\n";
    }

    std::shared_ptr<Value> get(const Key& key) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            // C++17：if 初始化语句
            if (auto shared = it->second.lock()) {
                std::cout << "缓存命中: " << key
                    << " (引用计数: " << shared.use_count() << ")\n";
                return shared;
            }
            else {
                std::cout << "缓存过期，删除: " << key << "\n";
                cache_.erase(it);
            }
        }
        std::cout << "缓存未命中: " << key << "\n";
        return nullptr;
    }

    void cleanup() {
        // C++17：erase-remove惯用法改进
        for (auto it = cache_.begin(); it != cache_.end(); ) {
            if (it->second.expired()) {
                std::cout << "自动清理过期缓存: " << it->first << "\n";
                it = cache_.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    size_t size() const { return cache_.size(); }
};

// 3.2 树形结构 - 使用 weak_ptr 解决循环引用
class TreeNode : public std::enable_shared_from_this<TreeNode> {
    std::string name_;
    std::weak_ptr<TreeNode> parent_;               // 弱引用父节点
    std::vector<std::shared_ptr<TreeNode>> children_; // 强引用子节点

public:
    explicit TreeNode(std::string name) : name_(std::move(name)) {
        std::cout << "创建节点: " << name_ << "\n";
    }
    ~TreeNode() { std::cout << "销毁节点: " << name_ << "\n"; }

    void addChild(std::shared_ptr<TreeNode> child) {
        child->parent_ = shared_from_this();  // 关键：使用shared_from_this
        children_.push_back(std::move(child));
        std::cout << name_ << " 添加子节点: "
            << children_.back()->name_ << "\n";
    }

    std::shared_ptr<TreeNode> getParent() const {
        return parent_.lock();  // 尝试提升为shared_ptr
    }

    const std::string& getName() const { return name_; }

    void printTree(int depth = 0) const {
        std::cout << std::string(depth * 2, ' ') << "├─ " << name_ << "\n";
        for (const auto& child : children_) {
            child->printTree(depth + 1);
        }
    }
};


// ============================================================
// 四、C++17 特性增强的智能指针用法
// ============================================================

// 4.1 optional + 智能指针组合
class DataProcessor {
public:
    // 可能返回空的结果
    static std::optional<std::unique_ptr<Product>> createProduct(bool valid) {
        if (valid) {
            return std::make_unique<ConcreteProductA>("有效产品", 100);
        }
        return std::nullopt;  // C++17：明确表示"无值"
    }
};

// 4.2 variant + 智能指针（多态替代方案）
// 这部分展示概念，实际需要 #include <variant>

// 4.3 结构化绑定与智能指针
class PairExample {
public:
    static auto createPair() {
        return std::make_pair(
            std::make_unique<int>(42),
            std::make_shared<std::string>("hello")
        );
    }
};

// ============================================================
// 五、测试
// ============================================================

void testUniquePtr() {
    std::cout << "\n=== 测试 unique_ptr ===\n";

    // 工厂模式
    auto productA = ProductFactory::create(
        ProductFactory::Type::A, "产品1", 1);
    productA->operate();

    // PIMPL
    DatabaseConnection db("mysql://localhost:3306/test");
    db.connect();
    std::cout << db.query("SELECT * FROM users") << "\n";

    // 自定义删除器
    FileManager file("test.txt");
    file.writeData("Hello, Smart Pointers!\n");

    // unique_ptr 容器
    std::vector<std::unique_ptr<Product>> products;
    products.push_back(std::make_unique<ConcreteProductA>("临时A", 1));
    products.push_back(std::make_unique<ConcreteProductB>("临时B", 2));

    // C++17：constexpr if 判断类型
    for (const auto& p : products) {
        p->operate();
    }
}

void testSharedPtr() {
    std::cout << "\n=== 测试 shared_ptr ===\n";

    // 资源共享
    auto state = std::make_shared<SharedState>();

    // 添加多个观察者（共享state）
    state->getSubject().addObserver(
        [state](const std::string& msg) {  // 捕获state增加引用计数
            std::cout << "观察者1: " << msg
                << " (当前状态: " << state->getState() << ")\n";
        });

    state->getSubject().addObserver(
        [](const std::string& msg) {
            std::cout << "观察者2: " << msg << "\n";
        });

    state->setState("活跃");
    state->setState("空闲");

    // 资源池
    ResourcePool pool;
    auto conn1 = pool.acquire();
    auto conn2 = pool.acquire();
    {
        auto conn3 = pool.acquire();
        pool.release(conn3);
    }
    pool.release(conn2);
    pool.release(conn1);
}

void testWeakPtr() {
    std::cout << "\n=== 测试 weak_ptr ===\n";

    // 缓存测试
    WeakCache<std::string, std::string> cache;

    {
        auto data1 = std::make_shared<std::string>("数据1");
        auto data2 = std::make_shared<std::string>("数据2");

        cache.put("key1", data1);
        cache.put("key2", data2);

        // 可以获取到
        auto result1 = cache.get("key1");
        if (result1) std::cout << "获取到: " << *result1 << "\n";

        std::cout << "缓存大小: " << cache.size() << "\n";
        // data1, data2离开作用域被销毁
    }

    // 缓存过期，自动清理
    cache.cleanup();
    std::cout << "清理后缓存大小: " << cache.size() << "\n";

    auto result2 = cache.get("key1");
    if (!result2) std::cout << "key1 已失效\n";

    // 树形结构测试（循环引用解决）
    auto root = std::make_shared<TreeNode>("根节点");
    auto child1 = std::make_shared<TreeNode>("子节点1");
    auto child2 = std::make_shared<TreeNode>("子节点2");

    root->addChild(child1);
    root->addChild(child2);

    auto grandchild = std::make_shared<TreeNode>("孙子节点");
    child1->addChild(grandchild);

    std::cout << "\n树结构:\n";
    root->printTree();

    // 验证weak_ptr打破循环引用
    auto parentOfChild1 = child1->getParent();
    if (parentOfChild1) {
        std::cout << child1->getName() << " 的父节点: "
            << parentOfChild1->getName() << "\n";
    }

    // root释放时，所有子节点正确释放（无循环引用导致的内存泄漏）
    std::cout << "\n释放root前 - 引用计数: " << root.use_count() << "\n";
}


void testCpp17Features() {
    std::cout << "\n=== 测试 C++17 特性 ===\n";

    // optional + unique_ptr
    auto optProduct = DataProcessor::createProduct(true);
    if (optProduct) {
        optProduct.value()->operate();
    }

    auto optNull = DataProcessor::createProduct(false);
    if (!optNull) {
        std::cout << "产品创建失败（optional为空）\n";
    }

    // 结构化绑定
    auto [uniqueInt, sharedStr] = PairExample::createPair();
    std::cout << "解构: *uniqueInt = " << *uniqueInt
        << ", *sharedStr = " << *sharedStr
        << " (引用计数: " << sharedStr.use_count() << ")\n";

    // shared_ptr 数组 (C++17)
    // auto arr = std::make_shared<int[]>(5); // C++20写法
    // for (int i = 0; i < 5; ++i) {
    //     arr[i] = i * 10;
    // }
    // std::cout << "shared_ptr 数组: ";
    // for (int i = 0; i < 5; ++i) {
    //     std::cout << arr[i] << " ";
    // }

    std::shared_ptr<int> arr(new int[5], std::default_delete<int[]>());
    for (int i = 0; i < 5; ++i) {
        arr.get()[i] = i * 10;
    }
    std::cout << "shared_ptr 数组: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << arr.get()[i] << " ";
    }
    std::cout << "\n";

    // weak_ptr 的 lock() 返回 shared_ptr (C++17 保证原子操作)
    auto sp = std::make_shared<int>(100);
    std::weak_ptr<int> wp = sp;

    if (auto locked = wp.lock()) {  // C++17：if 中声明变量
        *locked += 50;
        std::cout << "通过weak_ptr修改: " << *locked << "\n";
    }
}

// 内存泄漏检测辅助（简化版）
struct LeakDetector {
    static inline int objectCount = 0;

    LeakDetector() {
        ++objectCount;
        std::cout << "对象创建 (总数: " << objectCount << ")\n";
    }
    ~LeakDetector() {
        --objectCount;
        std::cout << "对象销毁 (剩余: " << objectCount << ")\n";
    }
};

void testMemoryManagement() {
    std::cout << "\n=== 内存管理验证 ===\n";

    {
        std::vector<std::shared_ptr<LeakDetector>> detectors;
        std::cout << "创建3个对象\n";
        detectors.push_back(std::make_shared<LeakDetector>());
        detectors.push_back(std::make_shared<LeakDetector>());
        detectors.push_back(std::make_shared<LeakDetector>());
        std::cout << "离开作用域，shared_ptr自动释放\n";
    }

    std::cout << "作用域结束后剩余对象: "
        << LeakDetector::objectCount << "\n";
    assert(LeakDetector::objectCount == 0 && "内存泄漏检测通过");
}

// ============================================================
// 主函数
// ============================================================
int main() {
    std::cout << std::string(60, '=') << "\n";
    std::cout << "C++17 智能指针完整示例\n";
    std::cout << std::string(60, '=') << "\n";

    testUniquePtr();
    testSharedPtr();
    testWeakPtr();
    testCpp17Features();
    testMemoryManagement();

    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "所有测试完成，程序退出时自动清理所有资源\n";
    std::cout << std::string(60, '=') << "\n";

    return 0;
}