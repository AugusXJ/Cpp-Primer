#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <typename T, unsigned N> constexpr int sizeOfArray( const T (&arr)[N])
{
	return N;
}

int main() 
{
	int a[3] = { 1,2,3 };
	cout << sizeOfArray(a) << endl;
	system("pause");
	return 0;
}