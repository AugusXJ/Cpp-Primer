#pragma once
#include <string>
#include<iostream>

using namespace std;
/*
Quote类
功能：书籍基类，包含ISBN编号和价格
*/
class Quote
{
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price):
		bookNo(book),price(sales_price){}
	const std::string isbn() const { return bookNo; }
	//虚函数
	virtual double net_price(std::size_t n) const { return n*price; }
	virtual ~Quote() = default;
	virtual void debug() const { cout << "data member: \n" << "\tbookNo:  " << bookNo << "\tprice:  " << price << endl; }
private:
	std::string bookNo;								//书籍的ISBN编号
protected:
	double price = 0.0;
};

/*
抽象基类：Disc_quote
功能：保存购买量的值和折扣值
*/
class Disc_quote :public Quote
{
public:
	Disc_quote() = default;
	Disc_quote(const string &book, double sales_price, std::size_t qty, double disc):
		Quote(book, sales_price),quantity(qty),discount(disc){}
 	double net_price(std::size_t n) const = 0;			//纯虚函数
	void debug() const { Quote::debug(); cout << "\tmin_qty: " << quantity << "\tdiscount:  " << discount << endl; }
protected:
	std::size_t quantity = 0;			//折扣适用的购买量
	double discount = 0.0;				//表示折扣的小数值
};

/*
Bulk_quote类
功能：折扣书籍，书籍打折比例为discount
*/
class Bulk_quote :public Disc_quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &book, double sales_price, std::size_t qty, double disc):
		Disc_quote(book,sales_price,qty,disc){}
	//覆盖基类的函数
	virtual double net_price(std::size_t n) const override;
	void debug() const override { Disc_quote::debug(); }
};

inline double Bulk_quote::net_price(std::size_t n) const 
{
	return n > quantity ? n*price*(1 - discount) : n*price;
}

/*
limit_Bulk_quote类：Disc_count的子类
功能：折扣的书籍有数量限制，小于limit_num的书籍折扣为discount
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