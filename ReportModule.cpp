#define_CRT_SECURE_NO_WARNINGS
#include "ReportModule.h"

ReportModule::ReportModule() {}

ReportModule::~ReportModule() {}

void ReportModule::getInvList() {
	//retrieve the original listing's 2D array
	//traverse it with a for loop, output each book
}

void ReportModule::getWholesaleList() {
	//retrieve the unsorted information array
	//traverse and output the title and wholesale cost of each book only
	//use a for loop to add all the wholesale costs and output the total
}

void ReportModule::getRetailList() {
	//retrieve unsorted book array
	//traverse and output the title and retail value of each book only
	//traverse the array to add and display total retail value of all books
}

void ReportModule::getQuantityList() {
	//retrieve unsorted book array
	//use sort function to sort by quantity, greatest to least
	//traverse and output all book info sorted by quantity
}

void ReportModule::getCostList() {
	//retrieve unsorted book array
	//use sort function to sort by wholesale cost, greatest to least
	//traverse and output the sorted books
}

void ReportModule::getAgeList() {
	//execute sort function to sort the dates of each book from oldest to newest
	//traverse the sorted array and display books from oldest to newest
}
