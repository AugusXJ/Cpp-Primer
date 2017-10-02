#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <typename T, unsigned N> void m_print( const T (&arr)[N])
{
	for (const auto &i : arr)
		cout << i << endl;
}

int main() 
{
	int a[3] = { 1,2,3 };
	m_print(a);
	system("pause");
	return 0;
}