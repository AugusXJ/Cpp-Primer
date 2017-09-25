#pragma once
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>

using namespace std;


class StrBlob
{
	friend class StrBlobPtr;
	friend bool operator==(const StrBlob &, const StrBlob &);
	friend bool operator!=(const StrBlob &s1, const StrBlob &s2);
	StrBlobPtr begin();
	StrBlobPtr end();
public:
	typedef vector<string>::size_type size_type;
	StrBlob() : data(make_shared<vector<string>>()) {}
	StrBlob(initializer_list<string> il);
	StrBlob(string il);

	string& operator[](size_t n);
	const string& operator[](size_t n) const;

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	//添加和删除元素
	void push_back(const string &t) { data->push_back(t); }
	void pop_back();
	//元素访问
	string& front() const;
	string& back() const;
private:
	shared_ptr<vector<string>> data;
	//如果data[i]不合法，抛出一个异常
	void check(size_type i, const string &msg) const;
};


inline string & StrBlob::operator[](size_t n)
{
	check(n, "out of range");
	return data->at(n);
}
inline const string& StrBlob::operator[](size_t n) const
{
	check(n, "out of range");
	return data->at(n);
}


class StrBlobPtr
{
public:
	friend bool operator==(const StrBlobPtr &s1, const StrBlobPtr &s2);
	friend bool operator!=(const StrBlobPtr &s1, const StrBlobPtr &s2);
	friend bool operator>(const StrBlobPtr &s1, const StrBlobPtr &s2);
	friend bool operator<(const StrBlobPtr &s1, const StrBlobPtr &s2);
	StrBlobPtr() : curr(0) {}
	StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	string& operator[](size_t n);
	const string& operator[](size_t n) const;
	string& deref() const
	{
		auto p = check(curr, "deference past end");
		return (*p)[curr];
	}
	StrBlobPtr& icur()			//前缀增加
	{
		auto p = check(curr, "deference past end");
		++curr;
		return *this;
	}
private:
	//若检验成功，check返回一个指向vector的shared_ptr
	shared_ptr<vector<string>> check(size_t i, const string& msg) const
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
	//保存一个weak_ptr，意味着底层vector可能被销毁
	weak_ptr<vector<string>> wptr;
	size_t curr;
};

inline string & StrBlobPtr::operator[](size_t n)
{
	auto p = check(n, "out of range");
	return (*p)[n];
}

inline const string & StrBlobPtr::operator[](size_t n) const
{
	auto p = check(n, "out of range");
	return (*p)[n];
}
