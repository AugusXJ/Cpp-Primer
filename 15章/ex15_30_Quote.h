#pragma once
#include <string>
#include<iostream>
#include<memory>
#include<set>

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
	Quote(const Quote &q) :bookNo(q.bookNo), price(q.price) { cout << "Quote ��������" << endl; }
	Quote& operator=(const Quote &q);
	const std::string isbn() const { return bookNo; }
	//�麯��
	virtual double net_price(std::size_t n) const { return n*price; }
	virtual ~Quote() = default;
	virtual void debug() const { cout << "data member: \n" << "\tbookNo:  " << bookNo << "\tprice:  " << price << endl; }
	virtual Quote* clone() const & { return new Quote(*this); }
	virtual Quote* clone() const && { return new Quote(move(*this) ); }
private:
	std::string bookNo;								//�鼮��ISBN���
protected:
	double price = 0.0;
};
inline Quote & Quote::operator=(const Quote & q)
{
	bookNo = q.bookNo;
	price = q.price;
	cout << "Quote ������ֵ" << endl;
	return *this;
}

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
	Disc_quote(const Disc_quote &q):Quote(q),quantity(q.quantity),discount(q.discount){ cout << "Disc_quote ��������" << endl; }
	Disc_quote &operator=(const Disc_quote &q);

 	double net_price(std::size_t n) const = 0;			//���麯��
	void debug() const { Quote::debug(); cout << "\tmin_qty: " << quantity << "\tdiscount:  " << discount << endl; }
protected:
	std::size_t quantity = 0;			//�ۿ����õĹ�����
	double discount = 0.0;				//��ʾ�ۿ۵�С��ֵ
};
inline Disc_quote & Disc_quote::operator=(const Disc_quote & q)
{
	Quote::operator=(q);
	quantity = q.quantity;
	discount = q.discount;
	cout << "Disc_quote ������ֵ" << endl;
	return *this;
}

/*
Bulk_quote��
���ܣ��ۿ��鼮���鼮���۱���Ϊdiscount
*/
class Bulk_quote :public Disc_quote
{
public:
	Bulk_quote() = default;
	using Disc_quote::Disc_quote;
	Bulk_quote(const Bulk_quote &q):Disc_quote(q){ cout << "Bulk_quote ��������" << endl; }
	Bulk_quote& operator=(const Bulk_quote &q);
	//���ǻ���ĺ���
	virtual double net_price(std::size_t n) const override;
	virtual Bulk_quote* clone() const & { return new Bulk_quote(*this); }
	virtual Bulk_quote* clone() const && { return new Bulk_quote(move(*this)); }
	void debug() const override { Disc_quote::debug(); }
};

inline Bulk_quote & Bulk_quote::operator=(const Bulk_quote & q)
{
	Disc_quote::operator=(q);
	cout << "Bulk_quote ������ֵ" << endl;
	return *this;
}

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
	using Disc_quote::Disc_quote;
	Limit_Bulk_quote(const Limit_Bulk_quote &q):Disc_quote(q){ cout << "Limit_Bulk_quote ��������" << endl; }
	Limit_Bulk_quote& operator=(const Limit_Bulk_quote &rhs);
	double net_price(std::size_t n) const override;
	void debug() const { Disc_quote::debug(); cout << "\tlimit_num:  " << limit_num << endl; }
	virtual Limit_Bulk_quote* clone() const & { return new Limit_Bulk_quote(*this); cout << "����" << endl; }
	virtual Limit_Bulk_quote* clone() const && { return new Limit_Bulk_quote(move(*this)); cout << "�ƶ�" << endl; }
private:
	std::size_t limit_num;
};

inline Limit_Bulk_quote & Limit_Bulk_quote::operator=(const Limit_Bulk_quote & rhs)
{
	Disc_quote::operator=(rhs);
	cout << "Limit_Bulk_quote ������ֵ����" << endl;
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
���������ڴ���鼮
*/
class Basket
{
public:
	//���һ����
	void add_item(const shared_ptr<Quote> &sale) { items.insert(sale); }
	void add_item(const Quote& sale) { items.insert(shared_ptr<Quote>(sale.clone())); cout << "����" << endl; }
	void add_item(const Quote&& sale) { items.insert(shared_ptr<Quote>(move(sale).clone())); cout << "�ƶ�" << endl; }
	//��ӡÿ������ܼۺ͹���������������ܼ�
	double total_receipt(ostream&) const;
private:
	//�Ƚ�shared_ptr����multiset��
	static bool compare(const shared_ptr<Quote> &lhs, const shared_ptr<Quote> &rhs)
	{
		return lhs->isbn() < rhs->isbn();
	}
	//multiset���������ۣ�����compare��Ա����
	multiset<shared_ptr<Quote>, decltype(compare)*> items{ compare };
};
