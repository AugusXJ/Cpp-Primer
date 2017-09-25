#include "ex14_16_StrBlob.h"

using namespace std;
int main()
{
	StrBlob str1 = { "first", "second", "third" };
	StrBlob str2 = { "first", "second", "third" };
	cout << str1[1] << endl;
	StrBlobPtr ptr1 = StrBlobPtr(str1);
	StrBlobPtr ptr2 = StrBlobPtr(str1);
	cout << ptr2[1] << endl;
	ptr2.icur();
	cout << ptr2[1] << endl;


	system("pause");
	return 0;
}