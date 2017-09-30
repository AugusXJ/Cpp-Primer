# C++ Primer 第十五章：面向对象程序设计
-------------------------------------------
 
## Exercise 15.1
> 什么是虚函数？

基类通过派生类进行覆盖的函数。

## Exercise 15.2
> protected访问说明符与private有何区别？

- 受保护的访问运算符说明的成员可以被派生类访问，但是不可被其他用户访问。
- 私有的访问运算符的说明成员均不可访问。

## Exercise 15.3
> 定义你自己的Quote类和print_total函数

`Quote`:  [hpp](ex15_3_Quote.h) | [test](ex15_3_QuoteTest.cpp)

## Exercise 15.4
> 下面哪条声明语句是不正确的？请解释原因。
> class Base{ ... };
> (a) class Derived : public Derived{ ... };
> (b) class Derived : private Base{ ... };
> (c) class Derived : public Base;

(a) 错误，继承了本身
(b) 错误，这是定义不是声明
(c) 错误，声明不带继承。

## Exercise 15.5
> 定义你自己的`Bulk_Quote`类

`Quote&Bulk_quote`: [hpp](ex15_3_Quote.h)

## Exercise 15.6
> 将`Quote`和`Bulk_Quote`的对象传给15.2.1节（第529页）练习中的`print_total`函数，检查该函数是否正确。

`Quote&Bulk_quote`: [hpp](ex15_3_Quote.h) | [test](ex15_3_QuoteTest.cpp)

## Exercise 15.7
> 定义一个类使其实现一种数量受限的折扣策略，具体策略是：当购买书籍的数量不超过一定给定的限量时享受折扣，如果购买量超过了限量，则超出的部分将以原价销售。

`Quote&Bulk_quote&Limit_Bulk_quote`: [hpp](ex15_3_Quote.h) | [test](ex15_3_QuoteTest.cpp)

## Exercise 15.6
> 给出静态类型和动态类型的定义

- 静态类型： 是已知的，变量声明时的类型或表达式生成的类型。
- 动态类型： 运行时才可知，变量或表达式表示的内存中的对象的类型。

## Exercise 15.9
> 在什么情况下表达式的静态类型可能与动态类型不同，请给出三个静态类型与动态类型不同的例子。

当对基类类型的指针或引用引用派生类型的对象时。 在这种情况下，静态类型是基类的引用（或指针），但动态类型是派生的引用（或指针）。

## Exercise 15.10
> 回忆我们在8.1节（第279页）进行的讨论，解释第284页中将`ifstream`传递给`Sales_data`的`read`函数的程序是如何工作的。

`ifstream`继承于`fstream`类，该函数需要`fstream`类的对象，当`ifstream`对象传入时隐式转换为父类`fstream`。

## Exercise 15.11
> 为你的Quote类体系添加一个名为debug的虚函数，令其分别显示每个类的数据成员。

`Quote&Bulk_quote&Limit_Bulk_quote`: [hpp](ex15_3_Quote.h) | [test](ex15_3_QuoteTest.cpp)

## Exercise 15.12
> 有必要将一个成员函数同时声明成`override`和`final`吗？为什么？

可以这么做，`overrider`意味着该函数覆盖基类中的同名虚函数;`final`意味着层次结构中更低级别的派生类无法再覆盖该函数。

## Exercise 15.13
> 给定下面的类，解释每个print函数的机制。

```cpp
class base {
public:
    string name() { return basename; }
    virtual void print(ostream &os) { os << basename; }
private:
    string basename;
};
class derived : public base {
public:
    void print(ostream &os) { print(os); os << " " << i; }
private:
    int i;
};
```
> 在上述代码中存在问题吗？如果有，你该如何修改它？

`derived`的`print`函数调用了`print`，会进行无限递归。

修改为：`void print(ostream &os) { base::print(os); os << " " << i; }`

## Exercise 15.14
> 给定上一题中的类以及下面这些对象，说明在运行时调用哪个函数；

```cpp
base bobj; base *bp1 = &bobj; base &br1 = bobj;
derived dobj; base *bp2 = &dobj; base &br2 = dobj;
(a) bobj.print();   // base::print()
(b) dobj.print();   // derived::print()
(c) bp1->name();    // base::name()
(d) bp2->name();    // derived::name()
(e) br1.print();    // base::print()
(f) br2.print();    // derived::print()
```

## Exercise 15.15
> 定义你自己的`Disc_quote`和`Bulk_quote`。

`Quote&Bulk_quote`: [hpp](ex15_15_Quote.h) | [test](ex15_15_QuoteTest.cpp)

## Exercise 15.16
> 改写你在15.22节（第533页）练习中编写的数量受限的折扣函数，令其继承`Disc_quote`。

`Quote&Bulk_quote`: [hpp](ex15_15_Quote.h) | [test](ex15_15_QuoteTest.cpp)

## Exercise 15.17
> 尝试定义一个`Disc_quote`的对象，看看编译器会给出的错误信息是什么？

1>d:\data\cpp-primer\15章\ex15_15_quotetest.cpp(16): error C2259: “Disc_quote”: 不能实例化抽象类
1>d:\data\cpp-primer\15章\ex15_15_quotetest.cpp(16): note: 由于下列成员:
1>d:\data\cpp-primer\15章\ex15_15_quotetest.cpp(16): note: “double Disc_quote::net_price(::size_t) const”: 是抽象的
1>d:\data\cpp-primer\15章\ex15_15_quote.h(37): note: 参见“Disc_quote::net_price”的声明

## Exercise 15.18
> 假定给定了第543页和第544页的类，同时已知每个对象的类型如注释所示，判断下面的哪些赋值语句是合法的。解释那些不合法的语句为什么不被允许：

```cpp
Base *p = &d1;  // d1 has type Pub_Derv     --  合法的
p = &d2;        // d2 has type Priv_Derv    --  不合法的
p = &d3;        // d3 has type Prot_Derv    --  不合法的
p = &dd1;       // dd1 has type Derived_from_Public     --  合法的
p = &dd2;       // dd2 has type Derived_from_Private    --  不合法的
p = &dd3;       // dd3 has type Derived_from_Protected  --  不合法的
```

## Exercise 15.19
> 假设543页和544页的每个类都有如下形式的成员函数：
`void memfcn(Base &b) {b = *this; }`
 对于每个类，分别判断上面的函数是否合法

当D继承B时，不管是通过什么方式继承，D的成员函数和友元都能使用派生类转化为基类。（544页第二条）
所以有三个是可行的：
```cpp
Pub_Derv  d1; // 合法
Priv_Derv d2; // 合法
Prot_Derv d3; // 合法
```

根据544页第三条：
Derived_from_Public     dd1; // 合法
Derived_from_Private    dd2; // 不合法
Derived_from_Protected  dd3; // 合法

## Exercise 15.20
> 编写代码检验你对前面两题的回答是否正确

see [hpp](ex15_20_test.h)

## Exercise 15.21
> 从下面这些一般性抽象概念中任选一个（或者选一个你自己的），将其对应的一组类型组织成一个继承体系：
(a) 图形文件格式（如gif、tff、jpeg、bmp）
(b) 图形基元（如方格、圆、球、圆锥）
(c) C++预言中的类型（如类、函数、成员函数—）

(b): see [hpp](ex15_21_shape.h)

## Exercise 15.22
> 对于你在上一题中的类，为其添加合适的虚函数以及公有成员和受保护的成员。

添加了`shape_name()`, `resize_by_percentage(float pct)`, `area()`, `volume()`等。
[hpp](ex15_21_shape.h)

## Exercise 15.23
> 假设第550页的`D1`类需要覆盖它继承而来的`fcn`函数，你应该如何对其修改？如果你修改之后fcn匹配了`Base`中的定义，则该节的那些调用语句将如何剖析？

只需要将`int fun(int)`改为`int fun()`即可
此时`bp2->fun()`调用的是的`D1::fcn`

## Exercise 15.24
> 哪种类需要虚析构函数？虚析构函数必须执行什么样的操作？

基类需要虚析构函数，由于虚函数可以继承，所以派生类不需要定义虚析构函数。
派生类进行动态分配时调用对应的析构函数。

## Exercise 15.25
> 我们为什么为`Disc_quote`定义一个默认构造函数？如果去除掉该构造函数的话会对`Bulk_quote`的行为产生什么样的影响？

由于存在需要四个变量的`Bulk_quote`构造函数，所以默认构造函数被删除，若不显示定义一个默认构造函数，则在无变量创建`Bulk_quote`类时会报错。

## Exercise 15.26
> 定义`Quote`和`Bulk_quote`的拷贝控制成员，令其与合成的版本行为一致。为这些成员以及其他构造函数添加打印状态的语句，使得我们能够知道正在运算哪个程序。使用这些编写程序，预测程序将创建和销毁哪些对象。重复试验，不断比较你的预测和实际输出结果是否相同，直到预测完全准确再结束。

`Quote&Bulk_quote`: [hpp](ex15_15_Quote.h) | [test](ex15_15_QuoteTest.cpp)


## Exercise 15.27
> 重新定义你的`Bulk_quote`类，令其继承构造函数。

see [hpp](ex15_27_Quote.h)

## Exercise 15.28
> 定义一个存放`Quote`对象的`Vector`，将`Bulk_quote`对象传入其中。计算`Vector`中所有元素的总的`net_price`。

see [hpp](ex15_28_Quote.h) | [cpp](ex15_28_QuoteTest.cpp)

## Exercise 15.29
> 再运行一次你的程序，这次传入`Quote`对象的`Shared_ptr`。如果这次计算出的总额与之前的程序不一致，解释为什么；如果一致，请说明原因。

see [hpp](ex15_28_Quote.h) | [cpp](ex15_29_QuoteTest.cpp)
结果与上一题不同，因为在28题中传入的`Bulk_quote`对象会被转化为`Quote`对象。
如果我们想保存与继承有关的对象，我们应该定义`vector`来保存基类的指针（优选的智能指针）。 因此，`vector`包含对象的动态类型。

## Exercise 15.30
> 编写你自己的`Basket`类，用它计算上一个练习中交易记录的总价格。

see [hpp](ex15_30_Quote.h) | [cpp](ex15_30_Quote.cpp) | [test](ex15_30_QuoteTest.cpp)