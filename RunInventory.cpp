#define_CRT_SECURE_NO_WARNINGS
#include "Inventory.h"

using namespace std;

int main()
{
	//Not sure if this is really needed
	struct Book
	{
		string isbn;
		string title;
		string author;
		string publisher;
		string date;
		string wholesale;
		string retail;
		string quantity;
	};

	 //First index is just a spot for the index of the book in the big list of books, second index value is equivalent to the info of the book
	int newSize = 1;
	std::string **bookData = new std::string*[newSize];
	for (int i = 0; i < newSize; i++)
	{
		bookData[i] = new std::string[8];
	}

	return 0;
}
