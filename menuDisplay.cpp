#include "menuDisplay.h"

menuDisplay::menuDisplay()
{
	confirmExit = false;
}

void menuDisplay::displayMenu()
{
	SortedType mainList;	//list initialized for use
	
	while (!confirmExit)	//menu displays so long as user does not choose to exit
	{
		cout << "Welcome to the Address Book Program!" << endl
			<< "Please select from the options below:" << endl;
		cout << "1. Enter a new name into the address book." << endl
			<< "2. Delete a name from the address book." << endl
			<< "3. Change a name or date in the address book." << endl
			<< "4. Generate a birthday card." << endl
			<< "5. Generate an anniversary card." << endl
			<< "6. Exit the card program." << endl;

		int selection;

		cin >> selection;

		useInput(selection, mainList);	//user selection passed to useInput function
	}
}

void menuDisplay::useInput(int select1, SortedType& inList)
{
		switch (select1)	//switch statement to facilitate user selection
		{
		case 1:
			inList.PutItem(inList.getNewEntry());	//gets and adds new entry
			inList.printList(); //displays list after entry
			break;
		case 2:	
			inList.DeleteName();	//call function to delete entry
			inList.printList(); //displays list after deletion
			break;
		case 3:
			changeMenu(inList);	//allows for editing list values
			break;
		case 4:
			generateCards(inList, 1);	//passes a 1 to card gen function
			break;
		case 5:
			generateCards(inList, 2);	//passes a 2 to card gen function
			break;
		case 6:
			cout << "Exiting Address Book Program. Thanks!" << endl;
			confirmExit = true;
			break;
		}
}

void menuDisplay::changeMenu(SortedType& inList)
{	//extra menu function in place for handling list change entries
	bool makeChange = true;
	if (inList.getListData() == NULL)
	{
		makeChange = false;
		cout << "No values in this list to edit!!" << endl;
	}
	while (makeChange == true)	//lets user keep making changes if needed
	{
		string editVal, refVal;
		int selection;
		char keepEditing;

		cout << "See current list below for entries to change:" << endl;
		inList.printList();

		cout << "Enter the last name of the user entry you wish to change:" << endl;
		cin >> refVal;

		cout << "Select a field to change: " << endl;
		cout << "1. Last Name" << endl << "2. First Name" << endl
			<< "3. Birthday" << endl << "4. Anniversary" << endl;
		cin >> selection;

		cout << "Enter a new value for the field you selected:" << endl;
		cin >> editVal;

		if (selection == 1 || selection == 2 || selection == 3 || selection == 4)
		inList.editLast(inList, refVal, editVal, selection);

		cout << "Continue making changes to users? Y/N" << endl;
		cin >> keepEditing;

		if (keepEditing == 'Y' || keepEditing == 'y')
			makeChange = true;
		else makeChange = false;
	}
}

void menuDisplay::generateCards(SortedType& inList, int selected)
{
	if (inList.getListData() == NULL)
	{
		cout << "No names in list yet!! Add names before generating cards." << endl;
	}
	else
	{
		string refVal, sig1, sig2;
		cout << "See current list below for entries to print:" << endl;
		inList.printList();

		cout << "Enter the last name of the selected user:" << endl;
		cin >> refVal;

		cout << "Enter the sender's first name:" << endl;
		cin >> sig1;
		cout << "Enter the sender's last name:" << endl;
		cin >> sig2;

		string signature = sig1 + " " + sig2;

		inList.printCard(refVal, signature, selected);
	}
}
