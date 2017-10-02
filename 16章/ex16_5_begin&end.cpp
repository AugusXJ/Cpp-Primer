#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <typename T, unsigned N> T* begin(const T(&arr)[N])
{
	return arr;
}
template <typename T, unsigned N> T* end(const T(&arr)[N])
{
	return arr+N;
}

int main() 
{
	int a[3] = { 1,2,3 };
	cout << *begin(a) << endl;
	system("pause");
	return 0;
}