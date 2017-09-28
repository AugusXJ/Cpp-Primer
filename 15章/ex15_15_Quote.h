#pragma once
#include <string>
#include<iostream>

using namespace std;
/*
Quote��
���ܣ��鼮���࣬����ISBN��źͼ۸�
*/
class Quote
{
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price):
		bookNo(book),price(sales_price){}
	const std::string isbn() const { return bookNo; }
	//�麯��
	virtual double net_price(std::size_t n) const { return n*price; }
	virtual ~Quote() = default;
	virtual void debug() const { cout << "data member: \n" << "\tbookNo:  " << bookNo << "\tprice:  " << price << endl; }
private:
	std::string bookNo;								//�鼮��ISBN���
protected:
	double price = 0.0;
};

/*
������ࣺDisc_quote
���ܣ����湺������ֵ���ۿ�ֵ
*/
class Disc_quote :public Quote
{
public:
	Disc_quote() = default;
	Disc_quote(const string &book, double sales_price, std::size_t qty, double disc):
		Quote(book, sales_price),quantity(qty),discount(disc){}
 	double net_price(std::size_t n) const = 0;			//���麯��
	void debug() const { Quote::debug(); cout << "\tmin_qty: " << quantity << "\tdiscount:  " << discount << endl; }
protected:
	std::size_t quantity = 0;			//�ۿ����õĹ�����
	double discount = 0.0;				//��ʾ�ۿ۵�С��ֵ
};

/*
Bulk_quote��
���ܣ��ۿ��鼮���鼮���۱���Ϊdiscount
*/
class Bulk_quote :public Disc_quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &book, double sales_price, std::size_t qty, double disc):
		Disc_quote(book,sales_price,qty,disc){}
	//���ǻ���ĺ���
	virtual double net_price(std::size_t n) const override;
	void debug() const override { Disc_quote::debug(); }
};

inline double Bulk_quote::net_price(std::size_t n) const 
{
	return n > quantity ? n*price*(1 - discount) : n*price;
}

/*
limit_Bulk_quote�ࣺDisc_count������
���ܣ��ۿ۵��鼮���������ƣ�С��limit_num���鼮�ۿ�Ϊdiscount
*/
class Limit_Bulk_quote : public Disc_quote
{
public:
	Limit_Bulk_quote() = default;
	Limit_Bulk_quote(const std::string &book, double sales_price, std::size_t qty, double disc, std::size_t ln) :
		Disc_quote(book, sales_price, qty, disc) {}
	double net_price(std::size_t n) const override;
	void debug() const { Disc_quote::debug(); cout << "\tlimit_num:  " << limit_num << endl; }
private:
	std::size_t limit_num;
};

inline double Limit_Bulk_quote::net_price(std::size_t n) const
{
	if (n < quantity)
		return n*price;
	else if (n <= limit_num)
		return n*price*(1 - discount);
	else
		return price*(limit_num*(1 - discount) + (n - limit_num));
}