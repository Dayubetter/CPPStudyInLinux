# 命名空间
- 在声明一个命名空间时，大括号内不仅可以存放变量，还可以存放以下类型： 变量、常量、函数、结构体、引用、类、对象、模板、命名空间等，它们都称为**实体**
- 命名空间一共有三种使用方式，分别是using编译指令、作用域限定符、using声明机制
1. using编译指令尽量写在局部作用域
```c++
using namespece dy; // 一次性引入dy的实体
```
2. using声明机制
```c++
using std::cout;  // 引入命名空间中的某个实体
using std::endl;
```
> 如果希望将一些内容限定在本文件中使用，就可以将他们定义在匿名空间中，且全局不可以有同名实体，否则只能访问到全局内容，无法访问到匿名空间中重名的实体
> 
> 匿名空间中的实体不能跨模块调用

## 跨模块调用
vim 多窗口操作：
> :e 文件名（带路径） 若文件存在就打开，不存在就创建
> 
>:bp 打开上一个窗口
> 
>:bn 打开下一个窗口
> 
>:bd 关闭当前窗口

1. 全局变量和函数是可以跨模块调用,a和b文件联合编译，实现跨模块调用
```c++
extern int num; // 外部引入声明
extern void print();
```
2. 有名命名空间中的实体可以跨模块调用
- 命名空间中的实体跨模块调用时，要在新的源文件中再次定义同名的命名空间，在其中通过extern引入实体。
- 进行联合编译时，这两次定义被认为是同一个命名空间

3. 静态变量和函数只能在本模块内部使用
4. 匿名空间的实体只能在本模块内部使用。

> <font color=red>**extern与include的对比：**</font>
>
> extern外部引入的方式适合管理较小的代码组织，用什么就引入什么，但是如果跨模块调用的关系不清晰，容易出错；
>
>include头文件的方式在代码组织上更清晰，但是会一次引入全部内容，相较而言效率比较低。

- 在命名空间中可以声明实体、定义实体，但是不能使用实体。**命名空间中的实体一定在命名空间之外使用**，可以理解为命名空间只是用来存放实体。

下面引用当前流行的命名空间使用<font color=red>**指导原则**</font>：

1. 提倡在已命名的名称空间中定义变量，而不是直接定义外部全局变量或者静态全局变量。

2. 如果开发了一个函数库或者类库，提倡将其放在一个命名空间中。

3. **对于using 声明，首先将其作用域设置为局部而不是全局（*）。**

4. 不要在头文件中使用using编译指令，这样，使得可用名称变得模糊，容易出现二义性。

5. 包含头文件的顺序可能会影响程序的行为，如果非要使用using编译指令，建议放

6. 在所有#include预编译指令后。

**规范补充：include多个头文件，首先放自定义的头文件，再放C的头文件，再放C++的头文件，最后放第三方库的头文件。**

# const 关键字
## 修饰内置类型
- const修饰的的变量为const常量，**const常量在定义时必须初始化**
><span style=color:red;background:yellow>**const常量和宏定义常量的区别**</span>
>
>1. <font color=red>**发生的时机不同**</font>：C语言中的宏定义发生时机在预处理时，做字符串的替换；
>  
>   const常量是在编译时（const常量本质还是一个变量，只是用const关键字限定之后，赋予只读属性，使用时依然是以变量的形式去使用）
>
>2. <font color=red>**类型和安全检查不同**</font>：宏定义没有类型，不做任何类型检查；**const常量有具体的类型**，在编译期会执行类型检查。
>
>   在使用中，应尽量以const替换宏定义常量，可以减小犯错误的概率。
## 修饰指针类型*
```c++
int number1 = 10;
int number2 = 20;

const int * p1 = &number1;//指向常量的指针
*p1 = 100;//error 通过p1指针无法修改其所指内容的值
p1 = &numbers;//ok 可以改变p1指针的指向
```
```c++
int * const p3 = &number1;//常量指针?
*p3 = 100;//ok 通过p3指针可以修改其所指内容的值
p3 = &number2;//error 不可以改变p1指针的指向
```
// 函数指针/指针函数
```c++
int add(int x,int y) {
    return x+y;
}
// 函数指针
void test() {
    // 定义函数指针时要确定其指向的函数的返回值和参数信息
    // 省略写法
    int (*p)(int ,int ) = add;
    cout << p(1,2) << endl;
    // 完整写法
    int (*p2)(int ,int ) = &add;
    cout << (*p2)(2,3) << endl;
}
```
```c++
// 指针函数，返回值为指针
// 需要确保返回值这个指针指向的变量生命周期比函数要长
int num = 100；
int * fun() {
    int *p = &num;
    return p;
}

void test() {
    cout << *fun() << endl;
}
```

# new/delete 表达式
- **C语言中使用malloc/free函数，C++使用new/delete表达式**

new语句中可以不加参数，初始化为各类型默认值；也可加参数，参数代表要初始化的值

```c++
int * p = (int*)malloc(sizeof(int));
*p = 10;
free(p);

int * p1 = new int();//初始化为该类型的默认值
cout << *p1 << endl;

int * p2 = new int(1);
cout << *p2 << endl;
```
- valgrind是一种开源工具集
<font color=red>**sudo apt install valgrind**</font>
  
- 安装完成后即可通过memcheck工具查看内存泄漏情况，编译后输入如下指令

```C++
valgrind --tool=memcheck ./a.out
```

- 如果想要更详细的泄漏情况，如造成泄漏的代码定位，编译时加上-g

```C++
valgrind --tool=memcheck --leak-check=full ./a.out
```
```c++
==5415== LEAK SUMMARY:
==5415==    definitely lost: 12 bytes in 3 blocks
==5415==    indirectly lost: 0 bytes in 0 blocks
==5415==      possibly lost: 0 bytes in 0 blocks
==5415==    still reachable: 0 bytes in 0 blocks
==5415==         suppressed: 0 bytes in 0 blocks
（1）绝对泄漏了；（2）间接泄漏了；（3）可能泄漏了，基本不会出现；（4）没有被回收，但是不确定要不要回收；（5）被编译器自动回收了，不用管
```

<span style=color:red;background:yellow>**malloc/free 和 new/delete 的区别**</span>
1. malloc/free是库函数；new/delete是表达式，后两者使用时不是函数的写法；
2. new表达式的返回值是相应类型的指针，malloc返回值是void*；
3. malloc申请的空间不会进行初始化，获取到的空间是有脏数据的，但new表达式申请空间时可以直接初始化；
4. malloc的参数是字节数，new表达式不需要传递字节数，会根据相应类型自动获取空间大小。

C++ 中，堆上申请空间存放字符串内容通用做法
1. 申请空间同时初始化
```c++
char *p = new char[6]{'h','e','l','l','o'};
cout << p <<endl;
printf("%p\n",p);
delete [] p;
p = nullptr;
```
2. 先申请空间，初始化为空，再赋值
```c++
const char * pstr = "hello";
char *p2 = new char[strlen(pstr) + 1]();
strcpy(p2,pstr);
cout << p2 << endl;
delete [] p2;
p2 = nullptr;
```
# 引用
- 引用是一个已定义变量的别名
```c++
int num = 2;
int &ref = num;
```
- 声明后必须初始化
- 引用一被绑定，无法更改绑定
> C++中的引用本质上是一种被限制的指针。类似于线性表和栈的关系，栈是被限制的线性表，底层实现相同，只不过逻辑上的用法不同而已。
>
>由于<font color=red>**引用是被限制的指针**</font>，所以引用是占据内存的，占据的大小就是一个指针的大小。有很多的说法，都说引用不会占据存储空间，其只是一个变量的别名，但这种说法并不准确。引用变量会占据存储空间，存放的是一个地址，但是编译器阻止对它本身的任何访问，从一而终总是指向初始的目标单元。在汇编里，引用的本质就是“间接寻址”。
>
>可以尝试对引用取址，发现获取到的地址就是引用所绑定变量的地址。
> 
## 引用的使用场景
### 引用作为函数的参数
- 三种传递，值传递、指针传递、引用传递
减少开销，不会复制
### 引用作为函数的返回值
要求：当以引用作为函数的返回值时，<span style=color:red;background:yellow>**返回的变量其生命周期一定是要大于函数的生命周期**</span>的，即当函数执行完毕时，返回的变量还存在。

目的： 避免复制，节省开销

注意：
1. **不要返回局部变量的引用**。因为局部变量会在函数返回后被销毁，被返回的引用就成为了"无所指"的引用，程序会进入未知状态
2. **不要轻易**返回一个堆空间变量的引用，非常容易造成内存泄漏。

总结：
1. 在引用的使用中，单纯给某个变量取个别名没有什么意义，引用的目的主要用于在函数参数传递中，解决大块数据或对象的传递效率和空间不理想的问题。
2. 用引用传递函数的参数，能保证参数传递中不产生副本，提高传递的效率，还可以通过const的使用，保证了引用传递的安全性。
3. 引用与指针的区别是，指针通过某个指针变量指向一个变量后，对它所指向的变量间接操作。程序中使用指针，程序的可读性差；引用底层仍然是指针，但是编译器不允许访问到这个底层的指针，逻辑上简单理解为——对引用的操作就是对目标变量的操作。<font color=red>**可以用指针或引用解决的问题，更推荐使用引用**</font>。

# 强制转换
- static_cast，const_cast，dynamic_cast，reinterpret_cast
## static_cast
- 常用，如把int转换为float
```c++
目标类型 转换后的变量 = static_cast<目标类型>(要转换的变量)
```
```c++
int iNumber = 100；
float fNumber = 0；
fNumber = (float) iNumber；//C风格
fNumber = static_cast<float>(iNumber);
```
## const_cast
该运算符用来修改类型的const属性，**基本不用**。

- 指向常量的指针被转化成普通指针，并且仍然指向原来的对象；

- 常量引用被转换成非常量引用，并且仍然指向原来的对象；
## dynamic_cast：该运算符主要用于基类和派生类间的转换
## reinterpret_cast：功能强大，万能转换
-该运算符可以用来处理无关类型之间的转换，即用在任意指针（或引用）类型之间的转换，以及指针与足够大的整数类型之间的转换。由此可以看出，reinterpret_cast的效果很强大，但错误的使用reinterpret_cast很容易导致程序的不安全，<font color=red>**只有将转换后的类型值转换回到其原始类型，这样才是正确使用reinterpret_cast方式**</font>。

# 函数重载
- 在同一作用域内，可以有一组具有相同函数名，不同参数列表的函数，这组函数被称为重载函数。
C 语言中不支持
- **函数参数的数量、类型、顺序任一不同则可以构成重载。**
- 只有返回类型不同，参数完全相同，是不能构成重载的

原理：
实现原理：  名字改编(name mangling)——当函数名称相同时 ，会根据参数的类型、顺序、个数进行改编

- g++ -c Overload.cc

- nm Overload.o
- <font color=red>编译器的名字改编机制将函数的名字改编成了与参数信息相关的名字</font>
```c++
0000000000001269 T _Z5func1v
0000000000001333 T _Z5func2v
00000000000013e9 T _Z5func3v
00000000000014b9 T _Z5func4v
```
## extern "C"
在C/C++混合编程的场景下，如果在C++代码中想要对部分内容按照C的方式编译
```c++
extern "C" void func() //用 extern"C"修饰单个函数
{

}
//如果是多个函数都希望用C的方式编译
//或是需要使用C语言的库文件
//都可以放到如下{}中
extern "C"
{
//……
}

```
# 默认参数
- 目的：c++可以给函数定义默认参数值
```c++
// 传入参数优先级高于默认参数
void func(int a = 1, int b = 2, int c = 3);
```
- 声明：一般默认参数在函数声明中提供，只写一次
- <font color=red>**默认参数的顺序必须从右向左逐渐定义**</font>
```c++
void func2(int a = 1, int b, int c = 0, int d);//error
void func2(int a, int b, int c = 0, int d = 0);//ok
```
- 函数重载时，要谨慎使用默认参数,缺省调用会冲突
```c++
void func3();
void func3(int x);
void func3(int x, int y);
//上面三个函数可以合成下面这一个
void func3(int x = 0, int y = 0);

// 如果一组重载函数（可能带有默认参数）都允许相同实参个数的调用，将会引起调用的二义性。
void func4(int x);
void func4(int x, int y = 0);

func4(1);//error,无法确定调用的是哪种形式的func4
```

# bool
true和false是字面值，可以通过转换变为int类型，true为1，false为0
- 任何数字或指针值都可以隐式转换为bool值
- 任何非零值都将转换为true，而零值转换为false（注意：-1也是代表true）
- bool变量占1个字节的空间

# inline函数

