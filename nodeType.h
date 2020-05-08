#pragma once
#include "ItemType.h"
	//nodeType struct included to facilitate singly-linked list that is used
struct nodeType {
	ItemType info;
	nodeType* next;
};