#pragma once
#include <iostream>
#include <string>

class Module {
protected:
	std::string bookData[25][8];
public:
	Module();
	virtual ~Module() { std::cout << "This is a flag to show module has been destroyed\n";  }
	enum field { INDEX, ISBN = 0, TITLE, AUTHOR, PUBLISHER, DATE, WHOLESALE, RETAIL, QUANTITY };
	void createBookArray();
	int bookSearch(); //(booklist [i][j]
	virtual void cashierMenu();
	virtual void inventoryMenu();
	virtual void reportMenu();
};
class Cashier : public::Module
{
	double total;
	double subtotal;
	double taxRate;
	double tax;
	std::string checkoutBooks[25][8];
public:
	Cashier();
	~Cashier() { std::cout << "This is a flag to show a cashier has been destroyed\n";  }
	void cashierMenu();
	void setTotal(double);
	void setSubTotal(int);
};
class Inventory : public::Module
{
	friend class Report;
public:
	Inventory();
	~Inventory() { std::cout << "This is a flag to show an Inventory has been destroyed.\n"; }
	void inventoryMenu();
	//std::string bookListing(std::string choice);
	//void addBook(std::string **bookData);
	//void deleteBook(std::string **bookData);
	//void editBook(std::string **bookData, std::string bookChoice);
	//void initialInventory(std::string **bookData);
};
class Report : public::Module
{
public:
	Report();
	~Report() { std::cout << "This is a flag to show a Report has been destroyed.\n"; }
	void reportMenu();
	void invenList();
	void wholesaleVal();
	void retailVal();
	void quantitylist();
	void wholeCostList();
	void dateList();
	void swapV(double *x, double *y);
	void swapV(int *x, int *y);
};