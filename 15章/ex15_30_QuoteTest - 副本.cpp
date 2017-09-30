#include "ex15_30_Quote.h"
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<memory>

using namespace std;


int main()
{
	Basket bas;
	for (int i = 0; i < 10; i++)
	{
		bas.add_item(Bulk_quote("a", 10, 5, 0.1));
		//bas.add_item(make_shared<Bulk_quote>("b", 12, 5, 0.2));
		//bas.add_item(make_shared<Bulk_quote>("c", 8, 5, 0.1));
	}
	bas.total_receipt(cout);
	system("pause");
	return 0;
}