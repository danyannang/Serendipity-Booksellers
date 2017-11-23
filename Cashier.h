#pragma once
#include <iostream>
#include <string>

class Module {
public:
	Module();
	virtual ~Module() { std::cout << "This is a flag to show module has been destroyed\n";  }
	int bookSearch(); //(booklist [i][j]
	std::string titleCompare();
	virtual void cashierMenu();
};
class Cashier : public::Module
{
	double total;
	double subtotal;
	double taxRate;
	double tax;
public:
	Cashier();
	~Cashier() { std::cout << "This is a flag to show a cashier has been destroyed\n";  }
	void cashierMenu();
	void setTotal(double);
	void setTaxRate();
	void setSubTotal(int);
};
