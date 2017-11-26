#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


void invenList();
void wholesaleVal();
void retailVal();
void quantitylist();
void wholeCostList();
void dateList();

string sample[8][8] = {};	// IM ONLY USEING THIS AS A GLOBAL VARIABLE TO SIMULATE THE IDEA THAT IT IS A ARRAY FROM A FATHER CLASS BEING USED BY A CHILD CLASS



int main()
{
	//			0	1		2		3			4	5			6				7
	//order: ISBN, TITLE, AUTHOR, PUBLISHER, DATE, QUANTITY, WHOLESALECOST, RETAIL PRICE

	
	
	for (int i = 0; i < 9; i++)
	{								//sets isbn for all sample books
		sample[i][0] = " 123";
	}
	
	sample[8][0] = " 345";
	for (int i = 0; i < 9; i++)
	{
		sample[i][1] = (" The Book");
		if (i == 5)					//sets names for all sample books
		{
			sample[i][1] = (" Dif Book");
		}
	}

	
	for (int i = 0; i < 9; i++)
	{								//set author for all sample books
		sample[i][2] = " Dan";
	}
	for (int i = 0; i < 9; i++)
	{								//set publisher for all sample books
		sample[i][3] = " book people";
	}
	for (int i = 0; i < 9; i++)
	{								//set date for all sample books
		sample[i][4] = " 2017/5/22";
		if (i == 3)
		{
			sample[i][4] = " 2016/5/21";
		}
	}
	for (int i = 0; i < 9; i++)
	{							//set quantity for all sample books
		sample[i][5] = " 2";
		if (i == 6)
		{
			sample[i][5] = " 3";
		}

	}
	cout << endl;
	for (int i = 0; i < 9; i++)
	{							//set wholesail cost for all sample books
		sample[i][6] = " 10.02";

	}
	cout << endl;
	sample[0][7] = " 10.05";
	cout << sample[2][0];
	for (int i = 0; i < 9; i++)
	{
		sample[i][7] = " 11.25";		//retail cose
		
	}
	cout << sample[2][0];
	cout << endl;

	// ALL THE PRIEVIOUS PART OF MAIN IS TO SIMULATE A SAMPLE ARRAY

	quantitylist();

	//order: ISBN, TITLE, AUTHOR, PUBLISHER, DATE, QUANTITY, WHOLESALECOST, RETAIL PRICE
	cout << endl;
	system("pause");

	return 0;
}

void invenList()
{
	cout << setw(10) << "ISBN" << setw(30) << "TITLE" << setw(15) << "AUTHOR" << setw(15) << "PUBLISHER" << setw(15) << "DATE" << setw(5) << "#" << setw(15) << "WHOLESALECOST" << setw(15) << "RETAIL PRICE"<<endl;
	for (int i = 0; i < 9; i++)
	{
		
		cout << endl;
		for (int k = 0; k < 8; k++)
		{
			switch (k) 
			{
			
			case 0:cout << setw(10) << sample[i][k];
				break;
			case 1:cout<<setw(30)<< sample[i][k] ;
				break;
			case 2:cout << setw(15) << sample[i][k] ;
				break;
			case 3:cout << setw(15) << sample[i][k] ;
				break;
			case 4:cout << setw(15) << sample[i][k] ;
				break;
			case 5:cout << setw(5) << sample[i][k] ;
				break;
			case 6:cout << setw(15) << sample[i][k] ;
				break;
			case 7:cout << setw(15) << sample[i][k] << endl;
				break;
			}
		}
		cout << endl;
	}
}
void wholesaleVal()
{
	cout << endl;
	double  total=0.0;
	cout << "Whole Sale Listing: ";
	for (int i = 0; i < 9; i++)
	{
		cout << sample[i][6] << " $" << endl;
		double isample = stod(sample[i][6],nullptr);
		total += isample;
	}
	cout << "total wholesale cost: " << total << " $"<<endl;
}
void retailVal()
{
	cout << endl;
	double  total = 0.0;
	cout << "Retail Listing: ";
	for (int i = 0; i < 9; i++)
	{
		cout << sample[i][7] << " $" << endl;
		double isample = stod(sample[i][7], nullptr);
		total += isample;
	}
	cout << "total retail cost: " << total << " $"<<endl;
}
void quantitylist()
{
	int itemp[9][2] = {};
	int swap1=0;
	int swap2=0;
	for (int i = 0; i < 9; i++)
	{
		itemp[i][0] = i;
		itemp[i][1] = stoi(sample[i][5], nullptr);
	}
	for (int k = 0; k < 9; k++)
	{
		swap1 = itemp[k][0];
		swap2 = itemp[k][1];
		for (int i = 0; i < 9; i++)
		{
			if (itemp[i][1] > swap2)
			{
				itemp[k][1] = itemp[i][1];
				itemp[i][1] = swap2;
				itemp[k][0] = itemp[i][0];
				itemp[i][1] = swap1;
			}
		}
		for (int y = 0; y < 8; y++)
		{
			cout << sample[k][y];
			if (y == 7)
			{
				cout << endl;
			}
		}
	}

}
void wholeCostList()
{

}
void dateList()
{

}