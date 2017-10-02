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

see [Begin&End](ex16_6_beigin&end.cpp)