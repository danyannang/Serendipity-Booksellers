#include "Inventory.h"

InventoryModule::InventoryModule()
{
	std::cout << "Welcome to the Inventory Module." << std::endl;
}

InventoryModule::~InventoryModule()
{
	std::cout << "Exiting the Inventory Module" << std::endl;
}

std::string InventoryModule::menu()
{
	std::cout << "1. Add a book" << std::endl;
	std::cout << "2. Delete a book" << std::endl;
	std::cout << "3. Edit book info" << std::endl;
	std::cout << "4. Back to Module menu" << std::endl;

	std::string choice;
	std::cin >> choice;

	return choice; 
}

std::string InventoryModule::bookListing(std::string choice, std::string **bookData, int invenSize) //Should have a default organization, but after a report is done, this should reflect that. Returns 
{
	//Print out categories first(This all needs to be formatted / put into a template later)
	std::cout << "# " << "ISBN " << "TITLE " << "AUTHOR " << "PUBLISHER " << "ADD_DATE " << "WHOLESALE_PRICE " << "RETAIL_PRICE " << "QUANTITY " << std::endl;

	//Print out contents of array created by initialInventory, perhaps changed by other methods

	for (int bookNum = 0; bookNum < invenSize-2; bookNum++)
	{
		std::cout << bookNum << " "; 
		for (int attr = 0; attr < 8; attr++)
		{
			std::cout << bookData[bookNum][attr] << " ";
			if (attr == 7)
			{
				std::cout << std::endl;
			}
		}
	}


	std::string bookChoice;
	if (choice == "3")//If user wanted to edit a book's info, ask them which one, and return it to use an an argument for the editBook method
	{
		std::cout << "Which book's info to edit? Or \"Q\" to go back ";
		std::cin >> bookChoice;
		return bookChoice;
	}
	return bookChoice;
}

void InventoryModule::initialInventory(std::string **&bookData, int &invenSize) //Should only be ran once during first run of inventory module in a new initialization of program, a new file will be created after. This will create the 2d array of books.
{
	//REPLACE WITH CODE FROM FATHER MODULE?
	std::string unsplit;
	std::ifstream iniBooks("BookStock.txt");

	//std::cout << "Text file for initial inventory?" << std::endl;
	//std::cin >> initialBooks; 
	//iniBooks.open("BookStock.txt");

	//std::string bookString;
	//std::getline(iniBooks, bookString, '\n');
	
	/* check for open if (iniBooks)
	{
		std::cout << "I'm open" << std::endl;
	}
	if (!iniBooks)
	{
		std::cout << "Error" << std::endl;
	}
	system("Pause"); */

	int nthBook = 0;
	while (std::getline(iniBooks, unsplit, '\t'))
	{
		bool exists = false;//To be set to true if the current book already exists in the data

		for (int attr = 0; attr < 8; attr++)//Cycle through the attributes for the book, will just keep reading if exists == true
		{
			if (attr == 0)//If it's the first attribute of a book, check if one already exists in the system
			{
				if (nthBook != 0)
				{
					for (int i = 0; i < nthBook + 1; i++)
					{
						if (unsplit == bookData[i][0])//If the read in ISBN is the exact same as another, then increment the quantity attribute by one
						{
							int addOneTo = stoi(bookData[i][QUANTITY]);
							std::cout << addOneTo << std::endl;
							bookData[i][QUANTITY] = std::to_string(addOneTo++);
							exists = true;
						}
					}
				}
				if (exists == false)
				{
					bookData[nthBook][ISBN] = unsplit;
				}
			}
			else if (exists == false)//If the index isn't ISBN and the book doesn't already exist in the system
			{
				bookData[nthBook][attr] = unsplit;
			}
			if (attr != 7)
			{
				std::getline(iniBooks, unsplit, '\t');
			}

		}

		if (exists == false)
		{
			int newSize = nthBook + 2;
			//Dynamically allocate a new 2d array with one extra space for a book, then copy the contents of the original array over. (Like how a vector keeps increasing in size)
			std::string **nBookData = new std::string*[newSize];
			for (int i = 0; i < newSize; i++)
			{
				nBookData[i] = new std::string[8];
			}
			for (int i = 0; i < newSize - 1; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					nBookData[i][j] = bookData[i][j];
				}
			}


			for (int i = 0; i < invenSize - 1; i++)
			{
				delete[] bookData[i];
			}
			delete[] bookData;
			bookData = nBookData;

			nthBook += 1;
			invenSize += 1; 
		}
	}

	iniBooks.close();
	std::cout << "Inventory Created" << std::endl;
	return;
}

void InventoryModule::addBook(std::string **&bookData, int &invenSize)//Adds the info for a new book at the end of the inventory(add condition if book equals exist to just add one to quantity)
{
	std::string newBook[8];
	std::cout << "Enter info for new book: " << std::endl;
	std::cout << "ISBN: ";
	std::cin >> newBook[ISBN];
	std::cout << "TITLE: ";
	std::cin >> newBook[TITLE];
	std::cout << "AUTHOR ";
	std::cin >> newBook[AUTHOR];
	std::cout << "PUBLISHER: ";
	std::cin >> newBook[PUBLISHER];
	std::cout << "DATE: ";
	std::cin >> newBook[DATE];
	std::cout << "WHOLESALE: ";
	std::cin >> newBook[WHOLESALE];
	std::cout << "RETAIL: ";
	std::cin >> newBook[RETAIL];
	std::cout << "QUANTITY: ";
	std::cin >> newBook[QUANTITY];

	//If book exists, just add quantity to existing
	bool exists = false;
	int foundIndex;
	for (int i = 0; i < invenSize - 2; i++)
	{
		if (newBook[ISBN] == bookData[i][ISBN])
		{
			foundIndex = i;
			exists = true;
			break;
		}
	}
	if (exists == true)
	{
		bookData[foundIndex][QUANTITY] += newBook[QUANTITY];
	}
	else//Read in the book data, expand size of array 
	{
		int insertAt = invenSize - 2;
		int newSize = invenSize + 1;

		std::string **nBookData = new std::string*[newSize];
		for (int i = 0; i < newSize; i++)
		{
			nBookData[i] = new std::string[8];
		}

		for (int i = 0; i < newSize - 2; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				nBookData[i][j] = bookData[i][j];
			}
		}

		for (int i = 0; i < invenSize - 1; i++)
		{
			delete[] bookData[i];
		}

		delete[] bookData;
		bookData = nBookData;
		for (int i = 0; i < 8; i++)
		{
			bookData[insertAt][i] = newBook[i];
		}
		invenSize += 1;
	}
	
	return;
}

void InventoryModule::deleteBook(std::string **&bookData, int &invenSize)//Deletes all info for a particular book, deletes the space for it and shrinks array
{
	int toDelete;
	std::cout << "Which # book to remove?" << std::endl;
	std::cin >> toDelete;

	int newSize = invenSize - 1;

	std::string **nBookData = new std::string*[newSize];
	for (int i = 0; i < newSize; i++)
	{
		nBookData[i] = new std::string[8];
	}

	bool shift = false; 

	for (int i = 0; i < newSize; i++)
	{
		if (i == toDelete)
		{
			shift = true; 
		}
		else
		{
			if (shift == false)
			{
				for (int j = 0; j < 8; j++)
				{
					nBookData[i][j] = bookData[i][j];
				}
			}
			else
			{
				for (int j = 0; j < 8; j++)
				{
					nBookData[i-1][j] = bookData[i][j];
				}
			}
		}
	}

	std::cout << bookData[toDelete][TITLE] << " has been removed from the inventory" << std::endl;

	for (int i = 0; i < invenSize - 1; i++)
	{
		delete[] bookData[i];
	}

	delete[] bookData;
	bookData = nBookData;
	invenSize -= 1;

	return; 
}

void InventoryModule::editBook(std::string **&bookData, std::string bookChoice)//Allows user to change attribute of a particular book(add option for user to go back/cancel the change, go back to previous menu after making the change)
{
	std::cout << "What to edit:" << std::endl;
	std::cout << "1. ISBN" << std::endl;
	std::cout << "2. TITLE" << std::endl;
	std::cout << "3. AUTHOR" << std::endl;
	std::cout << "4. PUBLISHER" << std::endl;
	std::cout << "5. ADD DATE" << std::endl;
	std::cout << "6. WHOLESALE PRICE" << std::endl;
	std::cout << "7. RETAIL PRICE" << std::endl;
	std::cout << "8. QUANTITY" << std::endl;

	std::string toChange;
	std::cin >> toChange;

	std::cout << "Current: " << bookData[stoi(bookChoice)][stoi(toChange) - 1] << std::endl;

	std::string changeTo;
	std::cout << "Change to: ";
	std::cin >> changeTo;

	bookData[stoi(bookChoice)][stoi(toChange) - 1] = changeTo;

	switch (stoi(toChange)) {
	case 1:
		std::cout << "ISBN successfully changed to " << changeTo << std::endl;
		break;
	case 2:
		std::cout << "Title successfully changed to " << changeTo << std::endl;
		break;
	case 3:
		std::cout << "Author successfully changed to " << changeTo << std::endl;
		break;
	case 4:
		std::cout << "Publisher successfully changed to " << changeTo << std::endl;
		break;
	case 5:
		std::cout << "Add date successfully changed to " << changeTo << std::endl;
		break;
	case 6:
		std::cout << "Wholesale price successfully changed to " << changeTo << std::endl;
		break;
	case 7:
		std::cout << "Retail price successfully changed to " << changeTo << std::endl;
		break;
	case 8:
		std::cout << "Quantity successfully changed to " << changeTo << std::endl;
		break;
	}

	return;
}
