#pragma once

#include <string>
#include <iostream>
#include <fstream>

class InventoryModule
{
private:
	std::string initialBooks;
public:
	InventoryModule();
	~InventoryModule();
	void menu();
	std::string bookListing(std::string choice);
	void initialInventory(std::string **bookData);
	void addBook();
	void deleteBook();
	void editBook(std::string bookChoice);
	enum field { INDEX, ISBN = 0, TITLE, AUTHOR, PUBLISHER, DATE, WHOLESALE, RETAIL, QUANTITY };
};