//implement MyBag. h here
#ifndef My_Bag_
#define My_Bag_


#include "ArrayBag.h"

template<class ItemType>
class MyBag : public ArrayBag<ItemType>
{
public:
	void removeAll(const ItemType& anEntry);
};

#include "MyBag.cpp"
#endif

