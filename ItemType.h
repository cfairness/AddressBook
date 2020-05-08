#pragma once
#include <fstream>
#include <string>

using namespace std;		//itemType class, slightly modified to contain first name, last name, and birthday
const int MAX_ITEMS = 5;
enum RelationType { LESS, GREATER, EQUAL };

class ItemType
{
public:
	ItemType();
	RelationType ComparedTo(ItemType) const;
	void Print(std::ofstream&) const;
	void Initialize(string lastNm, string firstNm, string birth, string anniv);
	string getLastName();
	string getFirstName();
	string getBday();
	string getAnniv();
private:
	string iString;  //Last name, used to alphabetize list
	string firstName;
	string bDay;
	string anniversary;
};