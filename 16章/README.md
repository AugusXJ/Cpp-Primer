# C++ Primer 第十六章：模板与泛型编程
-------------------------------------------

## Exercise 16,1
> 给出实例化的定义。

用模板生成的`class`或`function`。

## Exercise 16.2
> 编写并测试你自己版本的`compare`函数。

```cpp
template <typename T> int compare(const T &v1, const T &v2)
{
	if (v1 < v2) return -1;
	if (v2 < v1) return 1;
	else return 0;
}
```

## Exercise 16.3
> 对两个`Sales_data`对象调用你的`compare`函数，观察编译器在实例化过程中如何处理错误。

`error C2678: binary '<': no operator found which takes a left-hand operand of type 'const Sales_data' (or there is no acceptable conversion)`

## Exercise 16.4
> 编写行为类似标准库`find`算法的模板。函数需要两个模板类型参数，一个表示函数的迭代器参数，另一个表示值的类型，使用你的函数在一个`vector<int>`和一个`list<string>`中查找给定值。

see [Find](ex16_4_find.cpp)

## Exercise 16.5
> 为6.2.4节（第195页）中的`print`函数编写模板版本，它接受一个数组的引用，能处理任意大小、任意元素类型的数组。

see [Print](ex16_5_print.cpp)

## Exercise 16.6
> 你认为接受一个数组实参的标准库函数`begin`和`end`是如何工作的？定义你自己版本的`begin`和`end`。

see [Begin&End](ex16_6_beiginEnd.cpp)

## Exercise 16.7
> 编写一个`constexpr`模板，返回给定数组的大小。

see [sizeOfArray](ex16_7_sizeOfArray.cpp)

## Exercise 16.8
> 在第97页的“关键概念”中，我们注意到，C++程序员喜欢使用`!=`而不喜欢`<`。解释这个习惯的原因。

因为大多数迭代器都有`==`和`!=`运算符，而没有`<`运算符，使用`!=`就不必担心我们正在处理的容器的精确类型。

## Exercise 16.9
> 什么是函数模板？什么是类模板？

- 函数模板： 一个函数模板就是一个公式，可用来生成针对特定类型的函数版本。
- 类模板：类模板是用来生成类的蓝图的。
- 区别：编译器不能为类模板推断模板参数的类型。

## Exercise 16.10
> 当一个类模板被实例化时，会发生什么？

编译器将重写类模板，通过给定的模板参数替换模板参数T的每个实例。

## Exercise 16.11
> 下面的`List`定义是错误的。应如何修正它？
``` cpp
template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
  List<elemType>();
  List<elemType>(const List<elemType> &);
  List<elemType>& operator=(const List<elemType> &);
  ~List();
  void insert(ListItem *ptr, elemType value);
private:
  ListItem *front, *end;
};
```

实验类模板`ListItem`时需要模板参数
```cpp
void insert(ListItem<elemType> *ptr, elemType value);
ListItem<elemType> *front, *end;
```

## Exercise 16.12
> 编写你自己版本的`Blob`和`BlobPtr`模板，包含书中未定义的多个`const`成员。

see [cpp](ex16_12_Blob.cpp) | [hpp](ex16_12_Blob.h) | [test](ex16_12_BlobTest.cpp)
这里在编译的时候，出现无法解析的外部符号，解决方法[**戳这里**](http://blog.csdn.net/u011619422/article/details/45148779)。我使用第一种方案解决问题。

## Exercise 16.13
> 解释你为`BlobPtr`的相等和关系运算符选择哪种类型的友好关系？

对于每个`BlobPtr`的实例，如果具有相同的类型，则为友好关系。

## Exercise 16.14
> 编写`Screen`类模板，用非类型参数定义`Screen`的高和宽。

see [hpp](ex16_14_Screen.h) | [cpp](ex16_14_ScreenTest.cpp)

## Exercise 16.15
> 为你的`Screen`模板实现输入和输出运算符，`Screen`类需要哪些友元（如果需要的话）来令输入和输出运算符正确工作？解释每个友元声明（如果有的话）为什么是必要的。

和`Blob`是一样的。