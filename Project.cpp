#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Project.h"

Module::Module() //Add creation of book array.
{
	std::cout << "This is a flag to show that a Module has been created.\n";
	invenSize = 2;
	newSize = 2;
	backUpBookFile = "This is the backup data: ";
}
void Module::createBookArray(std::string **&bookData)
{
	std::cout << "Creating array.\n";
	std::string unsplit;
	std::ifstream iniBooks;
	iniBooks.open("booklist.txt");
	if (!iniBooks)
		std::cout << "Error Opening file.\n";
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
			nBookData = nullptr;

			nthBook += 1;
			invenSize += 1;
		}
	}
	iniBooks.close();
}
Module operator+(const Module &user, std::string tempstring)
{
	return Module(user.backUpBookFile + tempstring);
}
void Module::cashierMenu(std::string **&bookData)
{
	std::cout << "Check the child class.\n";
}
void Module::inventoryMenu(std::string **&bookData)
{
	std::cout << "Check the child class.\n";
}
void Module::reportMenu(std::string **&bookData)
{
	std::cout << "Check the child class.\n";
}
int Module::bookSearch(std::string **&bookData) //booksearch, for looking up books within the array.
{
	std::string choice;
	std::string searchChoice;
	int attrchoice = 0;
	std::cout << "What specification will you search for?\n\n\n1. ISBN\n2. Title\n3. Author\n4. Publisher\n5. Date Added\n6. Store Price\n\nEnter your Choice: ";
	std::getline(std::cin, choice);
	if (choice == "1")
		attrchoice = 0;
	else if (choice == "2")
		attrchoice = 1;
	else if (choice == "3")
		attrchoice = 2;
	else if (choice == "4")
		attrchoice = 3;
	else if (choice == "5")
		attrchoice = 4;
	else if (choice == "6")
		attrchoice = 6;
	else
		std::cout << "Not a valid entry, defaulting to ISBN search.\n";

	std::cout << std::endl << std::endl;
	std::cout << "Now enter what you want to search based on the previous specification: ";
	std::getline(std::cin, searchChoice);
	
	//linear search to find isbn;
	int index = 0;
	int position = -1;
	bool found = false;
	while (index < invenSize - 1 && !found) //100 is fake size declarator for the array
	{
		if (bookData[index][attrchoice] == searchChoice)
		{
			found = true;
			position = index;
		}
		index++;
	}
	if (found == true)
		return position;
	else
		throw "Error Book not found.\n";
}
void Module::deleteBookData(std::string **&bookData)
{
	for (int i = 0; i < invenSize - 1; i++)
	{
		delete[] bookData[i];
	}
	delete[] bookData;
	bookData = nullptr;
	std::cout << "This is a flag to show the array has been destroyed.\n";
}
//This is the start of the cashier module functions.
Cashier::Cashier()
{
	std::cout << "This is a flag to show that a Cashier has been created.\n";
	total = 0;
	subtotal = 0;
	tax = 0;
	taxRate = .0875;
}
void Cashier::cashierMenu(std::string **&bookData) //note for outpitting things neatly books neatly. store books in array.
{
	int arrayposition;
	int purchasenumber = 0;
	std::string choice;
	std::cout << "Serendipity BookSellers\n";
	std::cout << "Date: " << std::endl;
	do {
		std::cout << "Purchase a book? (y/n): ";
		std::getline(std::cin, choice);
		if (choice == "y" || choice == "Y")
		{
			try
			{
				arrayposition = bookSearch(bookData);//booklist[i][j]);
				if (arrayposition != -1)//output line for the added book
				{
					std::string tempstring;
					int count;
					setSubTotal(arrayposition, bookData);//Adds to total
					if (bookData[arrayposition][QUANTITY] != "0")
					{
						std::cout << "Qty\tISBN\t\tTitle\t\t\t\t\tPrice\tTotal\n" << std::endl;
						std::cout << bookData[arrayposition][QUANTITY] << "\t" << bookData[arrayposition][ISBN] << " \t" << bookData[arrayposition][TITLE].substr(0, 30) << " \t\t$" << bookData[arrayposition][RETAIL] << " $" << subtotal << std::endl;
						for (int j = 0; j < 8; j++) //stores all the purchased books in a new array.
						{
							checkoutBooks[purchasenumber][j] = bookData[arrayposition][j];
						}
						purchasenumber++;
						tempstring = bookData[arrayposition][QUANTITY];
						count = std::stoi(tempstring);
						count -= 1;
						tempstring = std::to_string(count);
						bookData[arrayposition][QUANTITY] = tempstring;
					}
					else if (bookData[arrayposition][QUANTITY] == "0")
					{
						std::cout << "That book is out of stock.\n";
					}
				}
				else if (arrayposition == -1)
					std::cout << "Book not found.\n";
			}
			catch (char *msg)
			{
				std::cout << msg;
			}
			catch (...)
			{
				std::cout << "Generic catch error message.\n";
			}
		}
	} while (arrayposition = -1 && choice == "y" || choice == "Y");
	std::cout << "Qty\tISBN\t\tTitle\t\t\t\t\tPrice\n" << std::endl;
	for (int i = 0; i < purchasenumber; i++)
	{
		std::cout << checkoutBooks[i][QUANTITY] << "\t" << checkoutBooks[i][ISBN] << " \t" << checkoutBooks[i][TITLE].substr(0, 30) << " \t\t$" << checkoutBooks[i][RETAIL] << std::endl;
	}
	setTotal();
	std::cout << "\tSubtotal: " << std::setw(4) << "$" << std::setprecision(2) << std::fixed << subtotal << std::endl;
	std::cout << "\tTax: " << std::setw(9) << "$" << std::setprecision(2) << std::fixed << tax << std::endl;
	std::cout << "\tTotal: " << std::setw(7) << "$" << std::setprecision(2) << std::fixed << total << std::endl;
}
void Cashier::setTotal()
{
	tax = (subtotal*taxRate);
	total = subtotal + tax;
}
void Cashier::setSubTotal(int x, std::string **&bookData)
{
	double temp = std::stod(bookData[x][RETAIL]);
	subtotal += temp;
}
//This is the start of the inventory module functions.
Inventory::Inventory() //changed all invensizes in code to just be size of base array, and changed **bookdata to normal bookdata.
{
	std::cout << "This is a flag to show an inventory has been created.\n";
}
void invenFile(std::string **&bookData, int inventorySize)
{
	std::ofstream finBooks;
	finBooks.open("BookStock2.txt");

	for (int i = 0; i < inventorySize - 1; i++)
	{
		for (int attr = 0; attr < 8; attr++)
		{
			finBooks << bookData[i][attr] << '\t';
		}
	}
	std::cout << "New Inventory File Created" << std::endl;
	finBooks.close();
}
void Inventory::inventoryMenu(std::string **&bookData)
{
	std::string choice;
	do {
		std::cout << "1. Add a book" << std::endl;
		std::cout << "2. Delete a book" << std::endl;
		std::cout << "3. Edit book info" << std::endl;
		std::cout << "4. Back to Module menu" << std::endl;
		std::cout << "Enter choice: ";
		std::getline(std::cin, choice);
		if (choice == "1")
		{
			addBook(bookData);
			invenFile(bookData, invenSize);
		}
		else if (choice == "2")
		{
			bookListing(choice, bookData);
			int toDelete;
			try
			{
				std::cout << "Which # book to remove?" << std::endl;
				std::cin >> toDelete;
				deleteBook(bookData, toDelete);
			}
			catch (char *msg)
			{
				std::cout << msg << std::endl;
			}
			invenFile(bookData, invenSize);
		}
		else if (choice == "3")
		{
			std::string bookchoice;
			bookchoice = bookListing(choice, bookData);
			if (bookchoice != "Q") // Why q?
			{
				try
				{
					editBook(bookchoice, bookData);
				}
				catch (char *msg)
				{
					std::cout << msg << std::endl;
				}
			}
		}
	} while (choice != "4");
}
void Inventory::addBook(std::string **&bookData) //fix nBookdata
{
	std::string newBook[8];
	std::cout << "Enter info for new book: " << std::endl;
	std::cout << "ISBN: ";
	std::getline(std::cin, newBook[ISBN]);
	std::cout << "TITLE: ";
	std::getline(std::cin, newBook[TITLE]);
	std::cout << "AUTHOR: ";
	std::getline(std::cin, newBook[AUTHOR]);
	std::cout << "PUBLISHER: ";
	std::getline(std::cin, newBook[PUBLISHER]);
	std::cout << "DATE: ";
	std::getline(std::cin, newBook[DATE]);
	std::cout << "WHOLESALE: $";
	std::getline(std::cin, newBook[WHOLESALE]);
	std::cout << "RETAIL: $";
	std::getline(std::cin, newBook[RETAIL]);
	std::cout << "QUANTITY: ";
	std::getline(std::cin, newBook[QUANTITY]);

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
		nBookData = nullptr;
		invenSize += 1;
	}
}
void Inventory::deleteBook(std::string **&bookData, int toDelete)//fix nbookdata
{
	int deleteThis = toDelete;
	if ((deleteThis < 0) || (deleteThis > invenSize - 3))
	{
		throw "No book at specified index";
	}
	int newSize = invenSize - 1;

	std::string **nBookData = new std::string*[newSize];
	for (int i = 0; i < newSize; i++)
	{
		nBookData[i] = new std::string[8];
	}

	bool shift = false;

	for (int i = 0; i < newSize; i++)
	{
		if (i == deleteThis)
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
					nBookData[i - 1][j] = bookData[i][j];
				}
			}
		}
	}

	std::cout << bookData[deleteThis][TITLE] << " has been removed from the inventory" << std::endl;

	for (int i = 0; i < invenSize - 1; i++)
	{
		delete[] bookData[i];
	}

	delete[] bookData;
	bookData = nBookData;
	nBookData = nullptr;
	invenSize -= 1;

}
std::string Inventory::bookListing(std::string choice, std::string **&bookData)
{
	//Print out categories first(This all needs to be formatted / put into a template later)
	std::cout << "# " << "ISBN " << "TITLE " << "AUTHOR " << "PUBLISHER " << "ADD_DATE " << "WHOLESALE_PRICE " << "RETAIL_PRICE " << "QUANTITY " << std::endl;

	//Print out contents of array created by initialInventory, perhaps changed by other methods

	for (int bookNum = 0; bookNum < invenSize - 2; bookNum++)
	{
		std::cout << bookNum << " ";
		for (int attr = 0; attr < 8; attr++)
		{
			std::cout << bookData[bookNum][attr].substr(0, 40) << " ";
			if (attr == 7)
			{
				std::cout << std::endl;
			}
		}
	}


	std::string bookChoice;
	if (choice == "3")//If user wanted to edit a book's info, ask them which one, and return it to use an an argument for the editBook method
	{
		std::cout << "Which book's info to edit? (Or \"Q\" to go back): ";
		std::getline(std::cin, bookChoice);
		return bookChoice;
	}
	return bookChoice;
}
void Inventory::editBook(std::string bookChoice, std::string **&bookData)
{
	std::string toEdit = bookChoice;
	if ((stoi(toEdit) < 0) || (stoi(toEdit) > invenSize - 3))
	{
		throw "No book at specified index";
	}
	std::cout << "1. ISBN" << std::endl;
	std::cout << "2. TITLE" << std::endl;
	std::cout << "3. AUTHOR" << std::endl;
	std::cout << "4. PUBLISHER" << std::endl;
	std::cout << "5. ADD DATE" << std::endl;
	std::cout << "6. WHOLESALE PRICE" << std::endl;
	std::cout << "7. RETAIL PRICE" << std::endl;
	std::cout << "8. QUANTITY" << std::endl;
	std::cout << "What to edit: ";

	std::string toChange;
	std::getline(std::cin, toChange);

	std::cout << "Current: " << bookData[stoi(bookChoice)][stoi(toChange) - 1] << std::endl;

	std::string changeTo;
	std::cout << "Change to: ";
	std::getline(std::cin, changeTo);

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
}
//This is the start of the report modules functions.
Report::Report()
{
	std::cout << "This is a flag to show that a report has been created.\n";
}
void Report::reportMenu(std::string **&bookData)
{
	std::string choice;
	do {
		std::cout << "1. Inventory Listing\n2. Inventory Wholesale Value\n3. Inventory Retail Value\n4. Listing by Quantity\n5. Listing by Cost\n6. Listing by Age\n7. Return to menu\n";
		std::cout << "Enter your choice: ";
		std::getline(std::cin, choice);
		if (choice == "1")
			invenList(bookData);
		else if (choice == "2")
			wholesaleVal(bookData);
		else if (choice == "3")
			retailVal(bookData);
		else if (choice == "4")
			quantitylist(bookData);
		else if (choice == "5")
			wholeCostList(bookData);
		else if (choice == "6")
			dateList(bookData);
		if (choice != "7")
		{
			std::cout << "Would you like to select another report module function? (y/n): ";
			std::getline(std::cin, choice);
		}
	} while (choice != "7" || choice == "Y" || choice == "y");
}
void Report::invenList(std::string **&bookData)
{
	std::cout << std::left << std::setw(12) << "ISBN" << std::setw(78) << "TITLE" << std::setw(25) << "AUTHOR" << std::setw(26) << "PUBLISHER" << std::setw(15) << "DATE" << std::setw(8) << "WHOLE" << std::setw(12) << "RETAIL" << std::setw(5) << "#" << std::endl;
	for (int i = 0; i < invenSize - 2; i++)
	{

		std::cout << std::endl;

		for (int k = 0; k < 8; k++)
		{
			switch (k)
			{

			case 0:
				std::cout << std::fixed << std::flush << std::left << std::setw(12) << bookData[i][k];
				break;
			case 1:
				std::cout << std::fixed << std::left << std::setw(78) << bookData[i][k].substr(0, 75);
				break;
			case 2:
				std::cout << std::fixed << std::left << std::setw(25) << bookData[i][k];
				break;
			case 3:
				std::cout << std::fixed << std::left << std::setw(26) << bookData[i][k];
				break;
			case 4:
				std::cout << std::fixed << std::left << std::setw(15) << bookData[i][k];
				break;
			case 5:
				std::cout << std::fixed << std::left << std::setw(8) << bookData[i][k];
				break;
			case 6:
				std::cout << std::fixed << std::left << std::setw(12) << bookData[i][k];
				break;
			case 7:
				std::cout << std::fixed << std::left << std::setw(5) << bookData[i][k];
				break;
			}
		}
		std::cout << std::endl;
	}
}
void Report::wholesaleVal(std::string **&bookData)
{
	std::cout << std::endl;
	double total = 0.0;
	std::cout << "***WHOLESALE COSTS*** " << std::endl << std::endl;
	for (int i = 0; i < invenSize - 2; i++)
	{
		std::cout << std::left << std::setw(86) << bookData[i][TITLE].substr(0, 78) << std::setw(6) << "$" + bookData[i][WHOLESALE] << std::endl;
		double isample = std::stod(bookData[i][WHOLESALE]);
		total += isample;
	}
	std::cout << std::endl << "TOTAL WHOLESALE COST: " << total << " $" << std::endl << std::endl;
}
void Report::retailVal(std::string **&bookData)
{
	std::cout << std::endl;
	double  total = 0.0;
	std::cout << "***RETAIL COSTS***" << std::endl << std::endl;
	for (int i = 0; i < invenSize - 2; i++)
	{
		std::cout << std::left << std::setw(86) << bookData[i][TITLE].substr(0, 78) << std::setw(6) << "$" + bookData[i][RETAIL] << std::endl;
		double isample = std::stod(bookData[i][6]);
		total += isample;
	}
	std::cout << std::endl << "TOTAL RETAIL COST: " << "$" << total << std::endl << std::endl;
}
void Report::swapV(double *x, double *y) //Need to check and update
{
	double temp = *x;
	*x = *y;
	*y = temp;
}
void Report::swapV(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
void Report::quantitylist(std::string **&bookData)//need to check and update //UPDATE AND REWRITE FOR NEW BOOKDATA ITEMP NEEDS TO BE EDITED, right now only used arbtitrary value
{
	std::cout << std::setw(10) << "ISBN" << std::setw(30) << "TITLE" << std::setw(15) << "AUTHOR" << std::setw(15) << "PUBLISHER" << std::setw(15) << "DATE" << std::setw(5) << "#" << std::setw(15) << "WHOLESALECOST" << std::setw(15) << "RETAIL PRICE" << std::endl;
	int itemp[100][2];
	int swap1 = 0;
	int swap2 = 0;
	for (int i = 0; i < invenSize - 2; i++)
	{
		itemp[i][0] = i;
		itemp[i][1] = std::stoi(bookData[i][7]);
	}
	for (int k = 0; k < invenSize - 2; k++)
	{

		for (int i = 0; i < invenSize - 2; i++)
		{

			if (itemp[i][1] > itemp[k][1])
			{

				swapV(&itemp[i][1], &itemp[k][1]);

				swapV(&itemp[k][0], &itemp[i][0]);
				k = i;
			}
		}

	}
	for (int i = 0; i < invenSize - 2; i++)
	{
		for (int y = 0; y < 8; y++)
		{
			switch (y)
			{
			case 0:
				std::cout << std::setw(10) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 1:
				std::cout << std::setw(30) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 2:
				std::cout << std::setw(15) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 3:
				std::cout << std::setw(15) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 4:
				std::cout << std::setw(15) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 5:
				std::cout << std::setw(5) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 6:
				std::cout << std::setw(15) << bookData[itemp[i][0]][y] << std::endl;
				break;
			case 7:
				std::cout << std::setw(15) << bookData[itemp[i][0]][y] << std::endl;
				break;
			}
		}
	}

}
void Report::wholeCostList(std::string **&bookData) //ITEMP ONCE AGAIN USE ARBITRARY VALUE //ALSO THIS FUNCTION JUST REPEATS THE SAME VALUE MULTIPLE TIMES.
{
	std::cout << std::setw(10) << "ISBN" << std::setw(30) << "TITLE" << std::setw(15) << "AUTHOR" << std::setw(15) << "PUBLISHER" << std::setw(15) << "DATE" << std::setw(5) << "#" << std::setw(15) << "WHOLESALECOST" << std::setw(15) << "RETAIL PRICE" << std::endl;
	double itemp[100][2] = {};
	int swap1 = 0;
	int swap2 = 0;

	for (int i = 0; i < 9; i++)
	{
		itemp[i][0] = i;
		itemp[i][1] = std::stod(bookData[i][5]);
	}
	for (int k = 0; k < invenSize - 2; k++)
	{

		for (int i = 0; i < invenSize - 1; i++)
		{

			if (itemp[i][1] > itemp[k][1])
			{

				swapV(&itemp[i][1], &itemp[k][1]);

				swapV(&itemp[k][0], &itemp[i][0]);
				k = i;
			}
		}

	}

	for (int i = 0; i < invenSize - 2; i++)
	{
		for (int y = 0; y < 8; y++)
		{
			int x = itemp[i][0]; //Is the base array supposed to be what is outputted here? or the temparray?
			switch (y)
			{
			case 1:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 2:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 3:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 4:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 5:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 6:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			case 7:
				std::cout << std::setw(15) << bookData[x][y] << std::endl;
				break;
			}
		}
	}
}
void Report::dateList(std::string **&bookData)
{
	int itemp[9][2] = {}, days = 0;
	std::string tempdate = "";

	std::cout << std::setw(10) << "ISBN" << std::setw(30) << "TITLE" <<std:: setw(15) << "AUTHOR" << std::setw(15) << "PUBLISHER" << std::setw(15) << "DATE" << std::setw(5) << "#" << std::setw(15) << "WHOLESALECOST" << std::setw(15) << "RETAIL PRICE" << std::endl;

	int swap1 = 0;
	int swap2 = 0;

	for (int i = 0; i < 9; i++)
	{
		itemp[i][0] = i;
		tempdate = bookData[i][4];
		days += stoi(tempdate.substr(1, 4), nullptr) * 364; //year
		days += stoi(tempdate.substr(6, 2), nullptr) * 31; //month
		days += stoi(tempdate.substr(9, 2), nullptr); //day
		itemp[i][1] = days;
		days = 0;
	}
	for (int k = 0; k < 9; k++)
	{

		for (int i = 0; i < 9; i++)
		{

			if (itemp[i][1] > itemp[k][1])
			{
				swapV(&itemp[i][1], &itemp[k][1]);
				swapV(&itemp[k][0], &itemp[i][0]);
				k = i;
			}
		}

	}

	for (int i = 0; i<9; i++)
	{
		for (int y = 0; y < 8; y++)
		{
			switch (y)
			{
			case 0:
				std::cout << std::setw(10) << bookData[itemp[i][0]][y];
				break;
			case 1:
				std::cout << std::setw(10) << bookData[itemp[i][0]][y];
				break;
			case 2:
				std::cout << std::setw(10) << bookData[itemp[i][0]][y];
				break;
			case 3:
				std::cout << std::setw(10) << bookData[itemp[i][0]][y];
				break;
			case 4:
				std::cout << std::setw(10) << bookData[itemp[i][0]][y];
				break;
			case 5:
				std::cout << std::setw(10) << bookData[itemp[i][0]][y];
				break;
			case 6:
				std::cout << std::setw(10) << bookData[itemp[i][0]][y];
				break;
			case 7:
				std::cout << std::setw(15) << bookData[itemp[i][0]][y] << std::endl;
				break;
			}
		}
	}
}
