#include "ItemType.h"
#include <fstream>


ItemType::ItemType()
{
	iString = "";
}

RelationType ItemType::ComparedTo(ItemType otherItem) const
{
	if (iString < otherItem.iString)
		return LESS;
	else if (iString > otherItem.iString)
		return GREATER;
	else return EQUAL;
}

void ItemType::Initialize(string lastNm, string firstNm, string birth, string anniv)
{
	iString = lastNm;
	firstName = firstNm;
	bDay = birth;
	anniversary = anniv;

}

void ItemType::Print(std::ofstream& out) const
{
	out << iString << " ";
}

string ItemType::getLastName() { return iString; }
string ItemType::getFirstName() { return firstName; }
string ItemType::getBday() { return bDay; }
string ItemType::getAnniv() { return anniversary; }
