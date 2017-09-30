#include "ex15_28_Quote.h"
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<memory>

using namespace std;

double print_total(ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN:  " << item.isbn() << "  sold:  " << n << "  total due:  " << ret << endl;
	return ret;
}

int main()
{
	vector<shared_ptr<Quote>> vec1;
	vec1.push_back(make_shared<Bulk_quote>("a", 10, 5, 0.1));
	vec1.push_back(make_shared<Bulk_quote>("b", 12, 5, 0.2));
	vec1.push_back(make_shared<Bulk_quote>("c", 8, 5, 0.1));
	size_t num = 10; double sum = 0.0;
	for (auto it = vec1.begin(); it != vec1.end(); it++)
		sum += (*it)->net_price(num);
	cout << sum << endl;			//258
	system("pause");
	return 0;
}