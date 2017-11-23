#pragma once
#include <iostream>
#include <string>

class Module {
public:
	Module();
	~Module() { std::cout << "This is a flag to show module has been destroyed\n";  }
	std::string bookSearch(struct book *x);
	std::string titleCompare(struct book *x);
};
class Cashier : public::Module
{
	double total;
	double subtotal;
public:
	double priceCalculation(double);
};