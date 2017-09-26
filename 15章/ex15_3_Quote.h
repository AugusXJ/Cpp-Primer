#pragma once
#include <string>

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
private:
	std::string bookNo;								//书籍的ISBN编号
protected:
	double price = 0.0;
};

/*
Bulk_quote类
功能：折扣书籍
*/
class Bulk_quote :public Quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &book, double sales_price, std::size_t qty, double disc):
		Quote(book,sales_price),min_qty(qty),discount(disc){}
	//覆盖基类的函数
	virtual double net_price(std::size_t n) const override;
protected:
	std::size_t min_qty = 0;			//适用折扣政策的最低购买量
	double discount = 0.0;
};

inline double Bulk_quote::net_price(std::size_t n) const 
{
	return n > min_qty ? n*price*(1 - discount) : n*price;
}

/*
limit_Bulk_quote类：Bulk_quote的子类
功能：在Bulk_quote类的功能上，折扣的书籍有数量限制
*/
class Limit_Bulk_quote : public Bulk_quote
{
public:
	Limit_Bulk_quote() = default;
	Limit_Bulk_quote(const std::string &book, double sales_price, std::size_t qty, double disc, std::size_t ln) :
		Bulk_quote(book,sales_price,qty,disc),limit_num(ln){}
	double net_price(std::size_t n) const override;
private:
	std::size_t limit_num;
};

inline double Limit_Bulk_quote::net_price(std::size_t n) const
{
	if (n < min_qty)
		return n*price;
	else if (n <= limit_num)
		return n*price*(1 - discount);
	else
		return price*(limit_num*(1 - discount) + (n - limit_num));
}