#pragma once
#include <iostream>
#include <string>

class Module {
protected:
	//std::string **bookData;
	int invenSize;
	int newSize;
public:
	Module();
	virtual ~Module() { std::cout << "This is a flag to show module has been destroyed\n"; }
	enum field { INDEX, ISBN = 0, TITLE, AUTHOR, PUBLISHER, DATE, WHOLESALE, RETAIL, QUANTITY };
	void createBookArray(std::string **&bookData);
	int bookSearch(std::string **&bookData); //(booklist [i][j]
	int getinvenSize() { return invenSize; }
	void setInvenSize(int maininvensize) { invenSize = maininvensize; };
	void deleteBookData(std::string **&bookData);
	virtual void cashierMenu(std::string **&bookData);
	virtual void inventoryMenu(std::string **&bookData);
	virtual void reportMenu(std::string **&bookData);
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
	~Cashier() { std::cout << "This is a flag to show a cashier has been destroyed\n"; }
	void cashierMenu(std::string **&bookData);
	void setTotal(double);
	void setSubTotal(int, std::string **&bookData);
};
class Inventory : public::Module
{
	friend class Report;
	std::string initialbooks;
public:
	Inventory();
	~Inventory() { std::cout << "This is a flag to show an Inventory has been destroyed.\n"; }
	void inventoryMenu(std::string **&bookData);
	std::string bookListing(std::string, std::string **&bookData);
	void addBook(std::string **&bookData);
	void invenFile(std::string **&bookData);
	void deleteBook(std::string **&bookData, int toDelete);
	void editBook(std::string bookChoice, std::string **&bookData);
};
class Report : public::Module
{
public:
	Report();
	~Report() { std::cout << "This is a flag to show a Report has been destroyed.\n"; }
	void reportMenu(std::string **&bookData);
	void invenList(std::string **&bookData);
	void wholesaleVal(std::string **&bookData);
	void retailVal(std::string **&bookData);
	void quantitylist(std::string **&bookData);
	void wholeCostList(std::string **&bookData);
	void dateList(std::string **&bookData);
	void swapV(double *x, double *y);
	void swapV(int *x, int *y);
};
