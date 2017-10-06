#include "ex16_12_Blob.h"
#include "ex16_12_Blob.cpp"

using namespace std;
int main()
{
	Blob<int> str1;
	Blob<int> str2({ 1,2,3 });
	cout << str2[1] << endl;
	BlobPtr<int> ptr1 = BlobPtr<int>(str1);
	BlobPtr<int> ptr2 = BlobPtr<int>(str1);



	system("pause");
	return 0;
}