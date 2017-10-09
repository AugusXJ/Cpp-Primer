#include <allocators>
#include <memory>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>


using namespace std;


// 类vector类内存分配策略的简化实现
template <typename T>
class Vec
{
	friend bool operator==<T>(const Vec<T> &sv1, const Vec<T> &sv2);
	friend bool operator!=<T>(const Vec<T> &sv1, const Vec<T> &sv2);
	friend bool operator< <T>(const Vec<T> &sv1, const Vec<T> &sv2);
	friend bool operator><T>(const Vec<T> &sv1, const Vec<T> &sv2);
public:
	Vec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}        //默认初始化
	Vec(initializer_list<T> il);								//14.23
	Vec(const Vec<T>&);                                                  //拷贝构造函数
	~Vec();                                                              //析构函数
	Vec &operator=(const Vec<T>&);                                       //拷贝赋值运算符
	T &operator[](size_t n);
	const T &operator[](size_t n) const;
	void push_back(const T&);                                          //拷贝元素
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	T *begin() const { return elements; }
	T *end() const { return first_free; }

private:
	allocator<T> alloc;                                            //分配元素
                                                                    //被添加元素的函数使用
	void chk_n_alloc();
	// 工具函数，被拷贝构造函数、赋值运算符和析构函数所使用
	pair<T*, T*> alloc_n_copy(const T*, const T*);                          //拷贝元素，返回元素首尾地址
	void Vec<T>::range_initialize(const T* first, const T* last);	//初始化StrVec
	void free();                                                            //销毁元素并释放内存
	void reallocate();                                                      //获得更多内存并拷贝已有元素
	T *elements;                                                       //指向数组首元素的指针
	T *first_free;                                                     //指向数组第一个空闲元素的指针
	T *cap;                                                            //指向数组尾后指针的位置
};

template <typename T>
inline void chk_n_alloc()
{
    if (size() == capacity())
        reallocate();
}


template <typename T>
inline T & Vec<T>::operator[](size_t n)
{
	if (size() > n)
		return elements[n];
	else
		throw runtime_error("out of range");
}

template <typename T>
inline const T & Vec<T>::operator[](size_t n) const
{
	if (size() > n)
		return elements[n];
	else
		throw runtime_error("out of range");
}

template <typename T>
void Vec<T>::push_back(const T &s)
{
	chk_n_alloc();          //确保有空间容纳元素
	alloc.construct(first_free++, s);						// 在first_free指向的元素中构造s的副本
}

template <typename T>
void Vec<T>::range_initialize(const T* first, const T* last)
{
	auto newdata = alloc_n_copy(first, last);
	elements = newdata.first;
	first_free = cap = newdata.second;
	cap = newdata.second;
}

template <typename T>
Vec<T>::Vec(const Vec<T> &s)
{
	//调用alloc_n_copy分配空间以容纳与s中一样多的元素
	range_initialize(s.begin(), s.end());
}

template <typename T>
Vec<T>::Vec(std::initializer_list<T> il)
{
	range_initialize(il.begin(), il.end());
}

template <typename T>
pair<T*, T*> Vec<T>::alloc_n_copy(const T *b, const T*e)
{
	//分配空间保存给定范围内的元素
	auto data = alloc.allocate(e - b);
	//初始化并返回一个pair，该pair由data和uninitialized_copy的返回值构成
	return { data, uninitialized_copy(b,e,data) };
}

template <typename T>
void Vec<T>::free()
{
	//不能传递给deallocate一个空指针，如果ellement为0，函数什么也不做
	if (elements)
	{
		for (auto p = first_free; p != elements;)
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}


template <typename T>
Vec<T>::~Vec()
{
	free();
}

template <typename T>
Vec<T> &Vec<T>::operator=(const Vec<T> &rhs)
{
	//释放原内存
	free();
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	elements = newdata.first;
	first_free = newdata.second;
	cap = newdata.second;
	return *this;
}

template <typename T>
void Vec<T>::reallocate()
{
	//我们将分配当前大小两倍的空间
	auto newcapacity = size() ? 2 * size() : 1;
	//分配新内存
	auto newdata = alloc.allocate(newcapacity);
	//将数据从旧内存移到新内存中
	auto dest = newdata;            //指向新数组中下一个空闲位置
	auto elem = elements;           //指向旧数组中下一个元素
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, move(*elem++));
	//释放旧内存空间
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

template <typename T>
bool operator==(const Vec<T> &sv1, const Vec<T> &sv2)
{
	return(sv1.size() == sv2.size() && equal(sv1.begin(), sv1.end(), sv2.begin()));
}
template <typename T>
bool operator!=(const Vec<T> &sv1, const Vec<T> &sv2)
{
	return !(sv1 == sv2);
}
template <typename T>
bool operator< (const Vec<T> &sv1, const Vec<T> &sv2)
{
	return sv1.size() < sv2.size();
}
template <typename T>
bool operator>(const Vec<T> &sv1, const Vec<T> &sv2)
{
	return sv1.size() > sv2.size();
}

typedef Vec<string> StrVec;

