#pragma once
#include <iostream>
#include <string>

class ReportModule : public Module
{
protected:

public:
	ReportModule();
	~ReportModule();

	void getInvList();
	void getWholesaleList();
	void getRetailList();
	void getQuantityList();
	void getCostList();
	void getAgeList();
};
