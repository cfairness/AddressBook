#include "SortedType.h"
#include <iostream>
using namespace std;
//the nuts and bolts of this program

SortedType::SortedType()
{
	length = 0;
}

void SortedType::MakeEmpty()
{
	nodeType* tempPtr;
	while (listData != NULL)
	{
		tempPtr = listData;
		listData = listData->next;
		delete tempPtr;
	}
	length = 0;
}


bool SortedType::isFull() const
{
	nodeType* location;
	try
	{
		location = new nodeType;
		delete location;
		return false;
	}
	catch(std::bad_alloc exception)
	{
		return true;
	}
}

int SortedType::GetLength() const
{
	return length;
}

ItemType SortedType::GetItem(ItemType item, bool& found)
{
	bool moreToSearch;
	nodeType* location;

	location = listData;
	found = false;
	moreToSearch = (location != NULL);

	while (moreToSearch && !found)
	{
		switch (item.ComparedTo(location->info))
		{
		case GREATER: location = location->next;
			moreToSearch = (location != NULL);
			break;

		case EQUAL: found = true;
			item = location->info;
			break;

		case LESS: moreToSearch = false;
			break;
		}
	}
	return item;
}

void SortedType::DeleteItem(ItemType item)
{
	nodeType* location = listData;
	nodeType* tempLocation;

	if (item.ComparedTo(listData->info) == EQUAL)
	{
		tempLocation = location;
		listData = listData->next;
	}
	else
	{
		while ((item.ComparedTo((location->next)->info) != EQUAL))
			location = location->next;
			
		tempLocation = location->next;
		location->next = (location->next)->next;
	}
	delete tempLocation;
	length--;
}

void SortedType::DeleteName()		//function added to delete items from list by name
{
	if (listData == NULL)
	{
		cout << "The list is already empty!!" << endl;
	}
	else
	{
		string nameFirst, nameLast;

		cout << "Delete a user." << endl;
		cout << "Enter the user's first name: ";
		cin >> nameFirst;
		cout << "Enter the user's last name: ";
		cin >> nameLast;

		ItemType item;
		item.Initialize(nameLast, nameFirst, "000", "000");
		nodeType* location = listData;
		nodeType* curr = listData;
		nodeType* tempLocation = NULL;
		bool inList = false;

		while (curr != NULL)
		{
			if ((item.getFirstName() == curr->info.getFirstName()) &&
				item.getLastName() == curr->info.getLastName()) {
				inList = true;
			}
			curr = curr->next;
		}

		if (inList)
		{
			if (item.getFirstName() == listData->info.getFirstName()
				&& item.getLastName() == listData->info.getLastName())
			{
				tempLocation = location;
				listData = listData->next;
			}
			else
			{
				while ((item.getFirstName() != location->next->info.getFirstName())
					|| (item.getLastName() != location->next->info.getLastName()))
				{
					location = location->next;
				}
				tempLocation = location->next;
				location->next = (location->next)->next;
			}
			delete tempLocation;
			length--;
		}
		else
		{
			cout << nameFirst << " " << nameLast << " " << "was not found in the list!!"
				<< endl;
		}
	}
}

void SortedType::PutItem(ItemType item)
{		//putItem is pretty standard, though checks are added for no duplicate last names
	nodeType* newNode;
	nodeType* predLoc;
	nodeType* location;
	bool moreToSearch;
	location = listData;
	predLoc = NULL;
	moreToSearch = (location != NULL);

	nodeType* curr = listData;
	bool inList = false;

	while (curr != NULL)
	{
		if (item.getLastName() == curr->info.getLastName()) {
			inList = true;
		}
		curr = curr->next;
	}

	if (!inList) {

		while (moreToSearch)
		{
			switch (item.ComparedTo(location->info))
			{
			case GREATER: predLoc = location;
				location = location->next;
				moreToSearch = (location != NULL);
				break;
			case LESS: moreToSearch = false;
				break;
			}
		}

		newNode = new nodeType;
		newNode->info = item;

		if (predLoc == NULL)
		{
			newNode->next = listData;
			listData = newNode;
		}
		else
		{
			newNode->next = location;
			predLoc->next = newNode;
		}
		length++;
	}
	else {
		cout << "Last name already in list!!" << endl;
	}
}

void SortedType::ResetList()
{
	currentPos = NULL;
}

SortedType::~SortedType()
{
	nodeType* tempPtr;

	while (listData != NULL)
	{
		tempPtr = listData;
		listData = listData->next;
		delete tempPtr;
	}
}

void SortedType::printList()	//print function, vital for testing and display at many points
{
	cout << "Printing current list: " << endl;

	nodeType* curr;
	curr = new nodeType;

	curr = listData;
	int j = 1;
	while (curr != NULL)
	{
		cout << j << ": " << curr->info.getLastName() << ", "
			<< curr->info.getFirstName() << " - "
			<< curr->info.getBday() << " - " << curr->info.getAnniv() << endl;
		j++;
		curr = curr->next;
	}
	cout << endl;
}

nodeType* SortedType::getListData() { return listData; }

ItemType SortedType::getNewEntry()
{	//get new entry, initialize it and return item ready to add to list
	ItemType newItem;
	string nameFirst, nameLast, dayBirth, dayAnniv;

	cout << "Enter the user's first name: ";
	cin >> nameFirst;
	cout << "Enter the user's last name: ";
	cin >> nameLast;
	cout << "Enter the user's date of birth: ";
	cin >> dayBirth;
	cout << "Enter the user's anniversary:";
	cin >> dayAnniv;
	cout << "Gracias!!" << endl;

	newItem.Initialize(nameLast, nameFirst, dayBirth, dayAnniv);
	return newItem;
}

void SortedType::editLast(SortedType& eList, string refVal, string editVal, int cField)
{	//probably the most complex new function, handles editing all three fields
	if (listData == NULL)
	{	//check for empty list
		cout << "The list is already empty!!" << endl;
	}
	else if (cField < 1 || cField > 4)
	{	//check for invalid field selection
		cout << "INVALID FIELD SELECTION" << endl;
	}
	else
	{
		ItemType item;
		nodeType* location = listData;
		nodeType* curr = listData;
		nodeType* tempLocation = NULL;
		bool inList = false;

		while (curr != NULL)
		{
			if (refVal == curr->info.getLastName()) {
				inList = true;
			}
			curr = curr->next;
		}

		if (inList)
		{	//finds item, puts updated copy in original's place, then deletes original
			if (refVal == listData->info.getLastName())
			{
				if(cField == 1)
					item.Initialize(editVal, listData->info.getFirstName(),
					listData->info.getBday(), listData->info.getAnniv());
				else if(cField == 2)
					item.Initialize(refVal, editVal,
						listData->info.getBday(), listData->info.getAnniv());
				else if (cField == 3)
					item.Initialize(refVal, listData->info.getFirstName(),
						editVal, listData->info.getAnniv());
				else if (cField == 4)
					item.Initialize(refVal, listData->info.getFirstName(),
						listData->info.getBday(), editVal);
				tempLocation = location;
				listData = listData->next;
				eList.PutItem(item);
			}
			else
			{
				while ((refVal != location->next->info.getLastName()))
				{
					location = location->next;
				}
				
				if (cField == 1)
					item.Initialize(editVal, location->next->info.getFirstName(),
						location->next->info.getBday(), location->next->info.getAnniv());
				else if (cField == 2)
					item.Initialize(refVal, editVal,
						location->next->info.getBday(), location->next->info.getAnniv());
				else if (cField == 3)
					item.Initialize(refVal, location->next->info.getFirstName(),
						editVal, location->next->info.getAnniv());
				else if (cField == 4)
					item.Initialize(refVal, location->next->info.getFirstName(),
						location->next->info.getBday(), editVal);
				tempLocation = location->next;
				location->next = (location->next)->next;
				eList.PutItem(item);
			}
			delete tempLocation;
			length--;
			printList();
		}
		else
		{
			cout << refVal << " " << "was not found in the list!!"
				<< endl;
		}
	}
}

void SortedType::printCard(string refVal, string sender, int cardType)
{	//function for card generation
	nodeType* curr = listData;
	nodeType* location = listData;
	bool RefInList = false;
	ItemType item;


	while (curr != NULL)
	{
		if (refVal == curr->info.getLastName()) {
			RefInList = true;
		}
		curr = curr->next;
	}

	if (RefInList)
	{
		if (refVal == listData->info.getLastName())
		{
			item = listData->info;
		}
		else
		{
			while ((refVal != location->next->info.getLastName()))
			{
				location = location->next;
			}
			item = location->next->info;
		}

		if (cardType == 1)
		{
			cout << endl << "************************************************" << endl
				<< endl << endl;
			cout << "Dear " << item.getFirstName() << " " << item.getLastName()
				<< "," << endl << endl;

			cout << "Hope your birthday was a great one and wishing you all the best!" << endl
				<< endl;

			cout << "Best regards," << endl << endl;

			cout << sender << endl << endl << endl;

			cout << "************************************************" << endl << endl;

		}
		else
		{
			cout << endl << "************************************************" << endl
				<< endl << endl;

			cout << "Dearest " << item.getFirstName() << " " << item.getLastName()
				<< "," << endl << endl;

			cout << "Just sending this note along to congratulate you on your anniversary!!"
				<< endl << endl;

			cout << "Sincerely," << endl << endl;

			cout << sender << endl << endl << endl;
			cout << "************************************************" << endl << endl;
		}
	}
	else
	{
		cout << refVal << " " << "was not found in the list!!"
			<< endl;
	}

}