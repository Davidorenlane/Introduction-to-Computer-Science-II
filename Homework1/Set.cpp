#include "Set.h"

Set::Set() {
	numItems = 0;
}         // Create an empty set.

bool Set::empty() const {
	if (numItems == 0)
		return true;
	return false;
}  // Return true if the set is empty, otherwise false.

int Set::size() const {
	return numItems;
}    // Return the number of items in the set.

bool Set::insert(const ItemType& value) {
	if (numItems == DEFAULT_MAX_ITEMS)
		return false;
	for (int i = 0; i < numItems; i++)
		if (set[i] == value)
			return false;
	set[numItems] = value;
	numItems++;
	return true;
}
// Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// is already in the set or because the set has a fixed capacity and
// is full).

bool Set::erase(const ItemType& value) {
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
		if (set[i] == value) {
			for (i; i < DEFAULT_MAX_ITEMS - 1; i++)
				set[i] = set[i + 1];
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
		if (set[i] == value)
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
				if (set[k] < set[j])
					x++;	
			}
			if (x == i) {
				value = set[j];
				return true;
			}
		}
	return false;
}
// If 0 <= i < size(), copy into value the item in the set that is
// greater than exactly i items in the set and return true.  Otherwise,
// leave value unchanged and return false.

void Set::swap(Set& other) {
	ItemType temp[DEFAULT_MAX_ITEMS];
	int x;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++){
		temp[i] = set[i];
		}
	for (int j = 0; j < DEFAULT_MAX_ITEMS; j++)
		set[j] = other.set[j];
	for (int k = 0; k < DEFAULT_MAX_ITEMS; k++) {
		other.set[k] = temp[k];
	}
	x = other.numItems;
	other.numItems = numItems;
	numItems = x;
}
// Exchange the contents of this set with the other one.  
