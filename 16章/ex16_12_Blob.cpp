#include "ex16_12_Blob.h"

template <typename T>
void Blob<T>::check(size_t i, const string &msg) const
{
	if (i >= size())
		throw std::out_of_range(msg);
}

template <typename T>
T& Blob<T>::back()
{
	check(0, "back on empty Blob");
	return data->back();
}


template <typename T>
T& Blob<T>::front()
{
	check(0, "front on empty Blob");
	return data->front();
}

template <typename T>
void Blob<T>::pop_back()
{
	check(0, "pop_back on empty Blob");
	return data->pop_back();
}



template <typename T>
Blob<T>::Blob(T il)
{
	data = make_shared<vector<T>>(vector<T>{il});
}

template <typename T>
bool operator==(const Blob<T> & b1, const Blob<T> &b2)
{
	return *(b1.data) == *(b2.data);
}

template <typename T>
bool operator!=(const Blob<T> & b1, const Blob<T> &b2)
{
	return !(b1 == b2);
}





template <typename T>
BlobPtr<T> Blob<T>::begin()
{
	return BlobPtr(*this);
}

template <typename T>
BlobPtr<T> Blob<T>::end()
{
	return BlobPtr(*this, data->size());
}

//==运算符
template <typename T>
bool operator==(const BlobPtr<T> &s1, const BlobPtr<T> &s2)
{
	return s1.curr == s2.curr;
}
template <typename T>
bool operator!=(const BlobPtr<T> &s1, const BlobPtr<T> &s2)
{
	return !(s1 == s2);
}

//关系运算符


template <typename T>
bool operator> (const BlobPtr<T> &s1, const BlobPtr<T> &s2)
{
	return s1.curr > s2.curr;
}


template <typename T> 
bool operator< (const BlobPtr<T> &s1, const BlobPtr<T> &s2)
{
	return s1.curr < s2.curr;
}



