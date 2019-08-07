#include "newSet.h"

Set::Set(int maxSize) {
	ptr = new ItemType[maxSize];
	numItems = 0;
	maxItems = maxSize;
}         // Create an empty set.

Set::Set(ItemType* x) {
	ptr = x;
}

Set::~Set() {
	delete[] ptr;
}

bool Set::empty() const {
	if (numItems == 0)
		return true;
	return false;
}  // Return true if the set is empty, otherwise false.

int Set::size() const {
	return numItems;
}    // Return the number of items in the set.

bool Set::insert(const ItemType& value) {
	if (numItems == maxItems)
		return false;
	for (int i = 0; i < numItems; i++)
		if (*(ptr + i) == value)
			return false;
	*(ptr + numItems) = value;
	numItems++;
	return true;
}
// Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// is already in the set or because the set has a fixed capacity and
// is full).

bool Set::erase(const ItemType& value) {
	for (int i = 0; i < numItems; i++)
		if (*(ptr + i) == value) {
			if (i < numItems - 1)
				for (i; i < numItems - 1; i++)
					*(ptr + i) = *(ptr + i + 1);
			numItems--;
			return true;
		}
	return false;
}
// Remove the value from the set if present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.

bool Set::contains(const ItemType& value) const {
	if (numItems == 0)
		return false;
	for (int i = 0; i < numItems; i++)
		if (*(ptr + i) == value)
			return true;
	return false;
}
// Return true if the value is in the set, otherwise false.

bool Set::get(int i, ItemType& value) const {
	int x;
	if (0 <= i && i < numItems)
		for (int j = 0; j < numItems; j++) {
			x = 0;
			for (int k = 0; k < numItems; k++) {
				if (*(ptr + k) < *(ptr + j))
					x++;
			}
			if (x == i) {
				value = *(ptr + j);
				return true;
			}
		}
	return false;
}
// If 0 <= i < size(), copy into value the item in the set that is
// greater than exactly i items in the set and return true.  Otherwise,
// leave value unchanged and return false.

void Set::swap(Set& other) {
	int x;
	ItemType* temp;
	temp = other.ptr;
	other.ptr = ptr;
	ptr = temp;
	x = other.numItems;
	other.numItems = numItems;
	numItems = x;
	x = other.maxItems;
	other.maxItems = maxItems;
	maxItems = x;
}
// Exchange the contents of this set with the other one.
//Change the implementation of the swap function so that the number of statement executions when swapping two sets 
//is the same no matter how many items are in the sets. (You would not satisfy this requirement if, for example, 
//your swap function caused a loop to visit each item in the set, 
//since the number of statements executed by all the iterations of the loop would depend on the number of items in the set.)