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