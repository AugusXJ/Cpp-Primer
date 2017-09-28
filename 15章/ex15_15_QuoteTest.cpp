#include "ex15_15_Quote.h"
#include<iostream>
#include<stdlib.h>

using namespace std;

double print_total(ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN:  " << item.isbn() << "  sold:  " << n << "  total due:  " << ret << endl;
	return ret;
}

int main()
{
	//Disc_quote w("a", 10, 5, 0.1);
	Bulk_quote q1("a",10,5,0.1);
	q1.debug();
	print_total(cout, q1, 10);
	Limit_Bulk_quote q2("b", 10, 5, 0.1, 7);
	print_total(cout, q2, 10);
	system("pause");
	return 0;
}