#include <vector>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main()
{
	vector<int> vec = { 1,2,3,4,5,6,7,8,9,0 };
	for (vector<int>::size_type i = 0; i < vec.size(); i++)
		cout << vec[i] << endl;
	system("pause");
	return 0;
}