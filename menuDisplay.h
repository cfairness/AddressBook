#include <iostream>
#include "SortedType.h"
#include "ItemType.h"
using namespace std;

class menuDisplay
{		//menuDisplay class to facilitate displaying user selection and calling user choices from SortedType class
public:
	menuDisplay();
	void displayMenu();
	void useInput(int select1, SortedType& inList);
	void changeMenu(SortedType& inList);
	void generateCards(SortedType& inList, int selected);

private:
	bool confirmExit;
	int selection;
};

