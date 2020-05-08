#pragma once
#include "ItemType.h"
#include "nodeType.h"

class SortedType
{	//SortedType class used from earlier in the chapter, heavily modified with extra functions to fit program requirements
public:
	SortedType();
	~SortedType();
	void MakeEmpty();		//empties list
	bool isFull() const;	//checks for full list
	int GetLength() const;	//returns length of current list
	ItemType GetItem(ItemType item, bool& found); //search for item
	void PutItem(ItemType item); //put new item in list
	void DeleteItem(ItemType item); //delete item from list
	void DeleteName(); //prompt for first and last name, then delete
	void ResetList();
	void printList();	//print current list
	nodeType* getListData();	//returns head node of list
	ItemType getNewEntry();	//prompt user for new entry for list
	void editLast(SortedType& eList, string refVal, string newVal, int cField); //function for editing existing entries
	void printCard(string refVal, string sender, int cardType);	//function for printing bday and anniversary cards

private:
	int length;
	nodeType* listData;
	nodeType* currentPos;
};

