# C++ primer 练习 - 14章：重载运算和类型转换
---------------------------------


## Exercise 14.1
>在什么情况下重载的运算符与内置运算符有区别？在什么情况下重载的运算符又与内置运算符一样？

当对类重载运算符时，对类的对象使用该运算符会调用重载运算符，对于非该类对象不使用重载运算符。

复合赋值运算符作为成员函数，具有对称性的运算符应该为非成员函数。

## Exercise 14.2
> 为`Sales_data`编写重载的输入、输出、加法和符合复制运算符。

输入运算符

	istream& operator>>(istream &is, Sales_data &item)
	{
		double price = 0;
		cout << "输入图书编号:	";
		is >> item.bookNo;
		cout << "输入销售数量:	";
		is >> item.units_sold;
		cout << "输入图书单价:	";
		is >> price;
		item.revenue = price * item.units_sold;
		return is;
	}

输出运算符

	// 友元函数：传入一个ostream对象cout， 一个Sales_data对象， 返回一个ostream对象的引用cout, 便于链式输出  
	ostream& operator<<(ostream &os, const Sales_data &item)
	{
		os << "图书编号：	"<<item.isbn() << "	销售数量：	" << item.units_sold << "	总收益：	 "
			<< item.revenue << "	均价：	" << item.avg_price();
		return os;
	}

加法运算符
	
	Sales_data operator+(const Sales_data &a, const Sales_data &b)
	{
		Sales_data temp = a;
		temp += b;
		return temp;
	}

复合赋值运算符

	// 返回当前对象的引用  
	Sales_data& operator+=(const Sales_data& rhs)
	{
		if (rhs.bookNo == this->bookNo)
		{
			units_sold += rhs.units_sold;
			revenue += rhs.revenue;
			return *this;
		}
	}

## Exercise 14.3
> 在`String`和`vector`都定义了重载的`==`以比较各自的对象，假设`svec1`和`svec2`是存放`string`的vector，确定在下面的表达式中分别使用了哪个版本的`==`。
> 
> - (a) "cobble" == "stone" 
> - (b) "svec[0]" == svec2[0]
> - (c) svec1 == svec2
> - (d) "svec1[0] == "stone"


(a)应用了C++内置版本的==，比较两个指针。

(b)应用了string版本的==。

(c)应用了vector版本的==。

(d)应用了string版本的==。

## Exercise 14.4
> 如何确定下列运算符是否应该是类的成员？
> 
>  - (a) %
>  - (b) %=
>  - (c) ++
>  - (d) ->
>  - (e) <<
>  - (f) &&
>  - (g) ==
>  - (h) ()

(a) %通常定义为非成员。

(b) %=通常定义为类成员，因为它会改变对象的状态。

(c) ++通常定义为类成员，因为它会改变对象的状态。

(d) ->必须定义为类成员，否则编译报错

(e) <<通常定义为非成员

(f) && 通常定义为非成员。

(g) ==通常定义为非成员。

(h) ()必须定义为类成员，否则编译会报错


## Exercise 14.5 
> 在7.5.1节的练习7.40（第261页）中，编写了下列类中某一个的框架，请问在这个类中应该定义重载的运算符吗？如果是，请写出来。

选择了`Data`

	#include <iostream>
	using std::ostream;
	using std::endl;

	class Date
	{
	public:
		Date() { }
		Date(int y, int m, int d) {year = y; month = m; day = d;}
		friend ostream& operator<<(ostream &os, const Date &dt);
	
	private:
		int year, month, day;
	};
	
	ostream& operator<<(ostream& os, const Date& d)
	{
		const char sep = '\t';
		os << "year:" << d.year << sep << "month:" << d.month << sep << "day:" << d.day << endl;
		return os;
	}

## Exercise 14.6
> 为你的Sales_data 类定义输出运算符。

	// 友元函数：传入一个ostream对象cout， 一个Sales_data对象， 返回一个ostream对象的引用cout, 便于链式输出  
	ostream& operator<<(ostream &os, const Sales_data &item)
	{
		os << "图书编号：	" << item.isbn() << "	销售数量：	" << item.units_sold << "	总收益：	 "
			<< item.revenue << "	均价：	" << item.avg_price();
		return os;
	}

## Exercise 14.7
> 你在13.5节的练习（470页）中曾经编写了一个`String`类，为它定义一个输出运算符。


	ostream &operator << (ostream &os, const String s)
	{
		for (auto i = s.begin; i != s.end; i++)
			os << *i;
		return os;
	}


## Exercise 14.8
> 你在7.5.1节的练习7.40（第261）页中曾经选择并编写了一个类，为它定义一个输出运算符。

see [Exercise 14.5](#exercise-145)

## Exercise 14.9
> 为你的`Sales_data`类定义输入运算符。

	// 友元函数：传入一个istream对象cin, 一个Sales_data对象， 返回一个istream对象的引用cin， 便于连输输入  
	istream& operator>>(istream &is, Sales_data &item)
	{
		double price = 0;
		cout << "输入图书编号:	";
		is >> item.bookNo;
		cout << "输入销售数量:	";
		is >> item.units_sold;
		cout << "输入图书单价:	";
		is >> price;
		if (is)
			item.revenue = price * item.units_sold;
		else
			item = Sales_data();
		return is;
	}

## Exercise 14.10
> 对于`Sales_data`的输入运算符来说如果给定了下面的输入将发生什么情况？
>
> - (a) 0-201-99999-9 10 24.95
> - (b) 10 24.95 0-210-99999-9

- (a) 正常生成一个`Sales_data`类，其图书编号为`0-201-99999-9`，销售数量为`10`，图书单价为`24.95`，并生成对应的总价格。
- (b) 由于输入的数据类型错误，会生成一个空的`Sales_data`对象。

## Exercise 14.11
> 下面的Sales_data输入运算符存在错误吗，若果有，请指出来。对于这个输入运算符如果仍然给定上个练习的输入将会发生什么情况？

```cpp
istream& operator>>(istream& in, Sales_data& s)
{
    double price;
    in >> s.bookNo >> s.units_sold >> price;
    s.revenue = s.units_sold * price;
    return in;
}
```

没有输入检查，(b)物品单价会出错。

## Exercise 14.12
> 你在7.5.1节的练习7.40（第261页）中曾经选择并编写了一个类，为它定义一个输入运算符并确保该运算符可以处理输入错误。

`Data`
see [class Date](Date.cpp)

## Exercise 14.13
> 你认为`Sales_data`类还应该支持哪些其他运算符（参见表4.1，第124页）？如果有的话，请给出它们的定义。

没了。

## Exercise 14.14
> 你觉得为什么调用 `operator+=`来定义`operator+`比其他方法更有效？

`operator+=`比`operator+`少一个不必要的临时变量。

## Exercise 14.15
> 你在7.5.1节的练习7.40（第261页）中曾经编写了一个类，你认为它应该含有其他算数运算符吗？如果是，请实现它们；如果不是，解释原因。

see [cpp](ex14_15_Date.cpp)

## Exercise 14.16
> 为你的`StrBlob`类（参见121.1节，第405页）、`StrBlobPtr`类（参见12.1.6节）、StrVec类（参见13.5节，第405页）和`String`类（参见13.5节，第470页）分别定义相等运算符和不相等运算符。

`StrBlob&&StrBlobPtr`:[hpp](ex14_16_StrBlob.cpp) | [cpp](ex14_16_StrBlob.h) | [test](ex14_16_StrBlobTest.cpp)

`StrVec`:[hpp](ex14_16_StrVec.h) | [cpp](ex14_16_StrVec.cpp) | [test](ex14_16_StrVecTest.cpp)

`String`:[hpp](ex14_16_String.h) | [cpp](ex14_16_String.cpp) | [test](ex14_16_StringTest.cpp)

## Exercise 14.17
> 你在7.51节的练习7.40（第261页）中曾经选择并编写了一个类，你认为它应该含有相等运算符吗？如果是，请实现它；如果不是，解释原因。

是。see [Exercise 14.15](ex14_15_Date.cpp)

## Exercise 14.18
> 为你的`StrBlob`类（参见121.1节，第405页）、`StrBlobPtr`类（参见12.1.6节）、StrVec类（参见13.5节，第405页）和`String`类（参见13.5节，第470页）定义关系运算符。

`StrBlob&&StrBlobPtr`:[hpp](ex14_16_StrBlob.h) | [cpp](ex14_16_StrBlob.cpp) | [test](ex14_16_StrBlobTest.cpp)

`StrVec`:[hpp](ex14_16_StrVec.h) | [cpp](ex14_16_StrVec.cpp) | [test](ex14_16_StrVecTest.cpp)

`String`:[hpp](ex14_16_String.h) | [cpp](ex14_16_String.cpp) | [test](ex14_16_StringTest.cpp)

## Exercise 14.19
> 你在7.51节的练习7.40（第261页）中曾经选择并编写了一个类，你认为它应该含有关系运算符吗？如果是，请实现它；如果不是，解释原因。

是。see [Exercise 14.15](ex14_15_Date.cpp)

## Exercise 14.20
> 为你的`Sales_data`类定义加法和复合赋值运算符。

`Sales_data`: [cpp](ex14_20_sales_data.cpp) | [hpp](ex14_20_sales_data.h)


## Exercise 14.21
> 编写`Sales_data`类的+和+=运算符，使得+执行实际的加法操作而+=调用+。相比于14.3节（第497页）和14.4节（第500页）对这两个运算符的定义，本题的定义有何缺点？试讨论之。

```cpp
Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    Sales_data old_data = *this;
    *this = old_data + rhs;
    return *this;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum;
    sum.units_sold = lhs.units_sold + rhs.units_sold;
    sum.revenue = lhs.revenue + rhs.revenue;
    return sum;
}
```
在+和+=运算符中，都使用了临时变量`Sales_data`，但是这没有必要。

## Exercise 14.22
> 定义赋值运算符的另一个版本，使得我们能把一个表示ISBN的	`string`赋给一个`Sales_data`对象。

`Sales_data`: [cpp](ex14_20_sales_data.cpp) | [hpp](ex14_20_sales_data.h)

## Exercise 14.23
> 为你的`StrVec`类定义一个`initializer_list`赋值运算符。

`StrVec`: [cpp](ex14_23_StrVec.cpp) | [hpp](ex14_23_StrVec.h) | [test](ex14_23_StrVecTest.cpp)

## Exercise 14.24
> 你在7.5.1节的练习7.40（第261页）中曾经选择并编写了一个类，你认为它应该含有拷贝赋值和移动赋值运算符吗？如果是，请实现它们。

`Date`: [cpp](ex14_24_Date.cpp)

## Exercise 14.25
> 上题的这个类还需要定义其他赋值运算符吗？如果是，请实现它们；同时说明运算对象应该是什么类型并解释原因。

see [Exercise 14.24](#exercise-1424)

## Exercise 14.26
> 为你的`StrBlob`类、`StrBlob`类、`StrVec`类和`String`类定义下标运算符。

`StrBlob`/`StrBlobPtr`: [cpp](ex14_16_StrBlob.cpp) | [hpp](ex14_16_StrBlob.h) | [test](ex14_16_StrBlobTest.cpp)
`StrVec`: [cpp](ex14_23_StrVec.cpp) | [hpp](ex14_23_StrVec.h) | [test](ex14_23_StrVecTest.cpp)
`String`: [cpp](ex14_26_String.cpp) | [hpp](ex14_26_String.h) | [test](ex14_26_StringMain.cpp)
注：在`StrVec`和`String`中重构[]运算符不需要检验，如果超出范围会抛出异常。

## Exercise 14.27
> 为你的`StrBlobPtr`类添加递增和递减运算符。

[cpp](ex14_27_28_StrBlob.cpp) | [hpp](ex14_27_28_StrBlob.h) | [test](ex14_27_28_StrBlobTest.cpp)

## Exercise 14.28
> 为你的`StrBlobPtr`类添加加法和减法运算符，使其可以实现指针的算数运算（参见3.5.3，第106页）。

see [Exercise 14.27](#exercise-1427)

## Exercise 14.29
> 为什么不定义const版本的递增和递减运算符？

因为`++`和`--`改变了对象的属性。

<font color = "red">**之后的练习没有做，答案参照[https://github.com/pezy/CppPrimer/tree/master/ch14](https://github.com/pezy/CppPrimer/tree/master/ch14)**
# 小结