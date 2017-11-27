#include "Inventory.h"

using namespace std;

int main()
{

	//To track array length
	int invenSize = 2;

	//First index is just a spot for the index of the book in the big list of books, second index value is equivalent to the info of the book
	int newSize = 2;
	std::string **bookData = new std::string*[newSize];
	for (int i = 0; i < newSize; i++)
	{
		bookData[i] = new std::string[8];
	}

	InventoryModule inven; 
	inven.initialInventory(bookData, invenSize);

	string choice = inven.menu(); 

	if (choice != "4")
	{
		while (choice != "4")
		{
			if (choice == "1")
			{
				inven.addBook(bookData, invenSize);

				choice = inven.menu();
			}
			else if (choice == "2")
			{
				inven.bookListing(choice, bookData, invenSize);
				inven.deleteBook(bookData, invenSize);

				choice = inven.menu();
			}
			else if (choice == "3")
			{
				string bookChoice = inven.bookListing(choice, bookData, invenSize);
				if (bookChoice != "Q")
				{
					inven.editBook(bookData, bookChoice);
				}

				choice = inven.menu();
			}
		}
	}
	else if (choice == "4")
	{
		//Code to go back to main Module's menu method
	}

	system("Pause");
	return 0;
}
