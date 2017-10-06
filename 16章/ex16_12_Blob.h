#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>

using namespace std;

template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T> bool operator== (const Blob<T> &, const Blob<T> &);
template <typename T> bool operator!= (const Blob<T> &, const Blob<T> &);
template <typename T> bool operator== (const BlobPtr<T> &s1, const BlobPtr<T> &s2);
template <typename T> bool operator!= (const BlobPtr<T> &s1, const BlobPtr<T> &s2);

template <typename T> class Blob
{
	friend class BlobPtr<T>;
	friend bool operator==<T> (const Blob<T> &, const Blob<T> &);
	friend bool operator!=<T> (const Blob<T> &, const Blob<T> &);
public:
	//返回一个ptr
	BlobPtr<T> begin();
	BlobPtr<T> end();
	typedef T value_type;
	typedef typename vector<T>::size_type size_type;
	//构造函数
	Blob() :data(make_shared<vector<T>>()) {}
	Blob(initializer_list<T> il):data(make_shared<vector<T>>(il)) {};
	Blob(T il);
	// 元素数目
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	// 添加和删除元素
	void push_back(const T &t) { data->push_back(t); }
	void push_back(T &&t) { data->push_back(move(t)); }
	void pop_back();
	//元素访问
	T& back();		//最后元素
	T& front();		//访问首元素
	T& operator[](size_t);
	const T& operator[](size_t) const;
private:
	shared_ptr<vector<T>> data;
	void check(size_t i, const string &msg) const;
};

template <typename T>
inline T& Blob<T>::operator[](size_t n)
{
	check(n, "out of range");
	return data->at(n);
}

template <typename T>
inline const T& Blob<T>::operator[](size_t n) const
{
	check(n, "out of range");
	return data->at(n);
}

template <typename T>
class BlobPtr
{
public:
	friend bool operator==<T> (const BlobPtr<T> &s1, const BlobPtr<T> &s2);
	friend bool operator!=<T> (const BlobPtr<T> &s1, const BlobPtr<T> &s2);

	BlobPtr() : curr(0) {}
	BlobPtr(Blob<T> &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	T& operator[](size_t n);
	const T& operator[](size_t n) const;
	T& deref() const;
	BlobPtr& icur();		//前缀增加
private:
	//若检验成功，check返回一个指向vector的shared_ptr
	shared_ptr<vector<T>> check(size_t i, const T& msg) const;
	//保存一个weak_ptr，意味着底层vector可能被销毁
	weak_ptr<vector<T>> wptr;
	size_t curr;
};

template <typename T>
T& BlobPtr<T>::operator[] (size_t n)
{
	auto p = check(n, "out of range");
	return p->at(n);
}

template <typename T>
const T& BlobPtr<T>::operator[] (size_t n) const
{
	auto p = check(n, "out of range");
	return p->at(n);
}



template<typename T>
inline T & BlobPtr<T>::deref() const
{
	auto p = check(curr, "deference past end");
	return (*p)[curr];
}

template <typename T>
inline BlobPtr<T>& BlobPtr<T>::icur()
{
	auto p = check(curr, "deference past end");
	++curr;
	return *this;
}

template <typename T>
inline shared_ptr<vector<T>> BlobPtr<T>::check(size_t i, const T& msg) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw runtime_error("unbound StrBolbPtr");
	if (i >= ret->size())
	{
		throw out_of_range(msg);
	}
	return ret;
}







