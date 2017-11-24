#pragma once
#include <iostream>
#include <string>

class Module {
	std::string bookData[100][8];
public:
	Module();
	virtual ~Module() { std::cout << "This is a flag to show module has been destroyed\n";  }
	enum field { INDEX, ISBN = 0, TITLE, AUTHOR, PUBLISHER, DATE, WHOLESALE, RETAIL, QUANTITY };
	void createBookArray();
	int bookSearch(); //(booklist [i][j]
	virtual void cashierMenu();
	virtual void inventoryMenu();
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
class Inventory : public::Module
{
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
