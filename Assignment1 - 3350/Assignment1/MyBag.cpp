#include "MyBag.h"
#include "pch.h"
#include <iostream>
using namespace std;

template <class ItemType>
void MyBag<ItemType>::removeAll(const ItemType &entry)
{
	// init
	bool flag = false;

	// check bag contents
	if (this->isEmpty())
	{
		cout << "Bag is Empty" << endl;
		return;
	}

	// see if item is present
	if (!this->contains(entry))
	{
		cout << "Item not in Bag" << endl;
		return;
	}

	// remove item(s) from bag
	for (int i = 0; i < this->getFrequencyOf(entry); i++)
		flag = this->remove(entry);
	
	if (flag)
		return;
	else
	{
		cout << "removal failed";
		return;
	}
}
