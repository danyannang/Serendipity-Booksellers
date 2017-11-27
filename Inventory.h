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
	std::string menu();
	std::string bookListing(std::string choice, std::string **bookData, int invenSize);
	void initialInventory(std::string **&bookData, int &invenSize);
	void addBook(std::string **&bookData, int &invenSize);
	void deleteBook(std::string **&bookData, int &invenSize);
	void editBook(std::string **&bookData, std::string bookChoice);
	enum field { INDEX, ISBN = 0, TITLE, AUTHOR, PUBLISHER, DATE, WHOLESALE, RETAIL, QUANTITY };
};
