#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

template <typename T, typename U> T m_find( T it1,  T it2, const U &val)
{
	for (auto it = it1; it != it2; it++)
	{
		if (*it == val)
			return it;
	}
	cout << "no found" << endl;
	throw runtime_error("no val");
}

int main() 
{
	vector<int> vec = { 1,2,3,4,5 };
	cout << *m_find(vec.begin(), vec.end(), 3) << endl;
	list<string> lst = { "a","b","c" };
	cout << *m_find(lst.begin(), lst.end(), "b") << endl;
	system("pause");
	return 0;
}