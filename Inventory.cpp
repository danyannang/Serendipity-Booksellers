#define_CRT_SECURE_NO_WARNINGS
#include "Inventory.h"

InventoryModule::InventoryModule()
{
	std::cout << "Welcome to the Inventory Module." << std::endl;
}

InventoryModule::~InventoryModule()
{
	std::cout << "Exiting the Inventory Module" << std::endl;
}

void InventoryModule::menu()
{
	std::cout << "1. Add a book" << std::endl;
	std::cout << "2. Delete a book" << std::endl;
	std::cout << "3. Edit book info" << std::endl;
	std::cout << "4. Back to Module menu" << std::endl;

	std::string choice; 
	std::cin >> choice; 
	if (choice == "1")
	{
		//addBook();
	}
	else if (choice == "2")
	{
		//deleteBook();
	}
	else if (choice == "3")
	{
		bookListing(choice);
		//editBook();
	}
	else if (choice == "4")
	{
		//Code to go back to main Module's menu method
	}
}

std::string InventoryModule::bookListing(std::string choice) //Should have a default organization, but after a report is done, this should reflect that. Returns 
{
	//Print out categories first(This all needs to be formatted / put into a template later)
	std::cout << "#" << "ISBN" << "TITLE" << "AUTHOR" << "PUBLISHER" << "ADD_DATE" << "WHOLESALE_PRICE" << "RETAIL_PRICE" << "QUANTITY" << std::endl;

	//Print out contents of array created by initialInventory, perhaps changed by other methods



	std::string bookChoice;
	if (choice == "3")//If user wanted to edit a book's info, ask them which one, and send it ask the argument for the editBook method
	{
		std::cout << "Which book's info to edit? ";
		std::cin >> bookChoice;
		editBook(bookChoice);
	}
}

void InventoryModule::initialInventory(std::string **bookData) //Should only be ran once during first run of inventory module in a new initialization of program, a new file will be created after. This will create the 2d array of books.
{
	std::string unsplit;
	std::ofstream iniBooks;

	std::cout << "Text file for initial inventory?" << std::endl;
	std::cin >> initialBooks; 
	iniBooks.open(initialBooks);

	while (iniBooks.good() == true)
	{
		bool exists = false;//To be set to true if the current book already exists in the data
		int nthBook = 0;

		for (int attr = 0; attr < 8; attr++)//Cycle through the attributes for the book, will just keep reading if exists == true
		{
			std::getline(std::cin, unsplit, ' ');
			if (attr == 0)//If it's the first attribute of a book, check if one already exists in the system
			{
				for (int i = 0; i < 8; i++)
				{
					if (unsplit == bookData[i][1])//If the read in ISBN is the exact same as another, then increment the quantity attribute by one
					{
						int addOneTo = stoi(bookData[i][QUANTITY]);
						bookData[i][QUANTITY] = std::to_string(addOneTo++);
						exists = true; 
					}
				}
				if (exists == false)
				{
					bookData[nthBook][ISBN] = unsplit;
				}
			}
			else if (exists == false)//If the index isn't ISBN and the book doesn't already exist in the system
			{
				if (attr == 7)//If the index is the quantity attribute and the book doesn't already exist in the system, initialize the quantity to 1
				{
					bookData[nthBook][QUANTITY] = 1;
				}
				else
				{
					bookData[nthBook][attr] = unsplit;
				}
			}
		}

		nthBook++; 

		//Dynamically allocate a new 2d array with one extra space for a book, then copy the contents of the original array over. (Like how a vector keeps increasing in size)
		int newSize = nthBook++; 
		std::string **nBookData = new std::string*[newSize];
		for (int i = 0; i < newSize; i++)
		{
			nBookData[i] = new std::string[8];
		}
		for (int i = 0; i < newSize--; i++)
		{
			for (int j = 0; i < 8; j++)
			{
				nBookData[i][j] = bookData[i][j];
			}
		}
		delete[] bookData;
		bookData = nBookData;
	}

	iniBooks.close();

}

void InventoryModule::addBook()//Adds the info for a new book at the end of the inventory
{

}

void InventoryModule::deleteBook()//Deletes all info for a particular book, deletes the space for it and shrinks array
{

}

void InventoryModule::editBook(std::string bookChoice)//Allows user to change attribute of a particular book
{

}
