#include <allocators>
#include <memory>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>


using namespace std;


// ��vector���ڴ������Եļ�ʵ��
template <typename T>
class Vec
{
	friend bool operator==<T>(const Vec<T> &sv1, const Vec<T> &sv2);
	friend bool operator!=<T>(const Vec<T> &sv1, const Vec<T> &sv2);
	friend bool operator< <T>(const Vec<T> &sv1, const Vec<T> &sv2);
	friend bool operator><T>(const Vec<T> &sv1, const Vec<T> &sv2);
public:
	Vec() :elements(nullptr), first_free(nullptr), cap(nullptr) {}        //Ĭ�ϳ�ʼ��
	Vec(initializer_list<T> il);								//14.23
	Vec(const Vec<T>&);                                                  //�������캯��
	~Vec();                                                              //��������
	Vec &operator=(const Vec<T>&);                                       //������ֵ�����
	T &operator[](size_t n);
	const T &operator[](size_t n) const;
	void push_back(const T&);                                          //����Ԫ��
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	T *begin() const { return elements; }
	T *end() const { return first_free; }

private:
	allocator<T> alloc;                                            //����Ԫ��
                                                                    //�����Ԫ�صĺ���ʹ��
	void chk_n_alloc();
	// ���ߺ��������������캯������ֵ�����������������ʹ��
	pair<T*, T*> alloc_n_copy(const T*, const T*);                          //����Ԫ�أ�����Ԫ����β��ַ
	void Vec<T>::range_initialize(const T* first, const T* last);	//��ʼ��StrVec
	void free();                                                            //����Ԫ�ز��ͷ��ڴ�
	void reallocate();                                                      //��ø����ڴ沢��������Ԫ��
	T *elements;                                                       //ָ��������Ԫ�ص�ָ��
	T *first_free;                                                     //ָ�������һ������Ԫ�ص�ָ��
	T *cap;                                                            //ָ������β��ָ���λ��
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
	chk_n_alloc();          //ȷ���пռ�����Ԫ��
	alloc.construct(first_free++, s);						// ��first_freeָ���Ԫ���й���s�ĸ���
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
	//����alloc_n_copy����ռ���������s��һ�����Ԫ��
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
	//����ռ䱣�������Χ�ڵ�Ԫ��
	auto data = alloc.allocate(e - b);
	//��ʼ��������һ��pair����pair��data��uninitialized_copy�ķ���ֵ����
	return { data, uninitialized_copy(b,e,data) };
}

template <typename T>
void Vec<T>::free()
{
	//���ܴ��ݸ�deallocateһ����ָ�룬���ellementΪ0������ʲôҲ����
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
	//�ͷ�ԭ�ڴ�
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
	//���ǽ����䵱ǰ��С�����Ŀռ�
	auto newcapacity = size() ? 2 * size() : 1;
	//�������ڴ�
	auto newdata = alloc.allocate(newcapacity);
	//�����ݴӾ��ڴ��Ƶ����ڴ���
	auto dest = newdata;            //ָ������������һ������λ��
	auto elem = elements;           //ָ�����������һ��Ԫ��
	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, move(*elem++));
	//�ͷž��ڴ�ռ�
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

