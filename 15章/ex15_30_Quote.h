#pragma once
#include <string>
#include<iostream>
#include<memory>
#include<set>

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
	Quote(const Quote &q) :bookNo(q.bookNo), price(q.price) { cout << "Quote 拷贝构造" << endl; }
	Quote& operator=(const Quote &q);
	const std::string isbn() const { return bookNo; }
	//虚函数
	virtual double net_price(std::size_t n) const { return n*price; }
	virtual ~Quote() = default;
	virtual void debug() const { cout << "data member: \n" << "\tbookNo:  " << bookNo << "\tprice:  " << price << endl; }
	virtual Quote* clone() const & { return new Quote(*this); }
	virtual Quote* clone() const && { return new Quote(move(*this) ); }
private:
	std::string bookNo;								//书籍的ISBN编号
protected:
	double price = 0.0;
};
inline Quote & Quote::operator=(const Quote & q)
{
	bookNo = q.bookNo;
	price = q.price;
	cout << "Quote 拷贝赋值" << endl;
	return *this;
}

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
	Disc_quote(const Disc_quote &q):Quote(q),quantity(q.quantity),discount(q.discount){ cout << "Disc_quote 拷贝构造" << endl; }
	Disc_quote &operator=(const Disc_quote &q);

 	double net_price(std::size_t n) const = 0;			//纯虚函数
	void debug() const { Quote::debug(); cout << "\tmin_qty: " << quantity << "\tdiscount:  " << discount << endl; }
protected:
	std::size_t quantity = 0;			//折扣适用的购买量
	double discount = 0.0;				//表示折扣的小数值
};
inline Disc_quote & Disc_quote::operator=(const Disc_quote & q)
{
	Quote::operator=(q);
	quantity = q.quantity;
	discount = q.discount;
	cout << "Disc_quote 拷贝赋值" << endl;
	return *this;
}

/*
Bulk_quote类
功能：折扣书籍，书籍打折比例为discount
*/
class Bulk_quote :public Disc_quote
{
public:
	Bulk_quote() = default;
	using Disc_quote::Disc_quote;
	Bulk_quote(const Bulk_quote &q):Disc_quote(q){ cout << "Bulk_quote 拷贝构造" << endl; }
	Bulk_quote& operator=(const Bulk_quote &q);
	//覆盖基类的函数
	virtual double net_price(std::size_t n) const override;
	virtual Bulk_quote* clone() const & { return new Bulk_quote(*this); }
	virtual Bulk_quote* clone() const && { return new Bulk_quote(move(*this)); }
	void debug() const override { Disc_quote::debug(); }
};

inline Bulk_quote & Bulk_quote::operator=(const Bulk_quote & q)
{
	Disc_quote::operator=(q);
	cout << "Bulk_quote 拷贝赋值" << endl;
	return *this;
}

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
	using Disc_quote::Disc_quote;
	Limit_Bulk_quote(const Limit_Bulk_quote &q):Disc_quote(q){ cout << "Limit_Bulk_quote 拷贝构造" << endl; }
	Limit_Bulk_quote& operator=(const Limit_Bulk_quote &rhs);
	double net_price(std::size_t n) const override;
	void debug() const { Disc_quote::debug(); cout << "\tlimit_num:  " << limit_num << endl; }
	virtual Limit_Bulk_quote* clone() const & { return new Limit_Bulk_quote(*this); cout << "拷贝" << endl; }
	virtual Limit_Bulk_quote* clone() const && { return new Limit_Bulk_quote(move(*this)); cout << "移动" << endl; }
private:
	std::size_t limit_num;
};

inline Limit_Bulk_quote & Limit_Bulk_quote::operator=(const Limit_Bulk_quote & rhs)
{
	Disc_quote::operator=(rhs);
	cout << "Limit_Bulk_quote 拷贝赋值函数" << endl;
	return *this;
}

inline double Limit_Bulk_quote::net_price(std::size_t n) const
{
	if (n < quantity)
		return n*price;
	else if (n <= limit_num)
		return n*price*(1 - discount);
	else
		return price*(limit_num*(1 - discount) + (n - limit_num));
}

/*
篮子类用于存放书籍
*/
class Basket
{
public:
	//添加一本书
	void add_item(const shared_ptr<Quote> &sale) { items.insert(sale); }
	void add_item(const Quote& sale) { items.insert(shared_ptr<Quote>(sale.clone())); cout << "拷贝" << endl; }
	void add_item(const Quote&& sale) { items.insert(shared_ptr<Quote>(move(sale).clone())); cout << "移动" << endl; }
	//打印每本书的总价和购物篮中所有书的总价
	double total_receipt(ostream&) const;
private:
	//比较shared_ptr，给multiset用
	static bool compare(const shared_ptr<Quote> &lhs, const shared_ptr<Quote> &rhs)
	{
		return lhs->isbn() < rhs->isbn();
	}
	//multiset保存多个报价，按照compare成员排序
	multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare };
};
