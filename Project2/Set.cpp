#include "Set.h"
#include <cassert>
#include <iostream>
using namespace std;


Set::Set() {
	ptr = new Node;		//dynamically allocates first node
	ptr->m_next = nullptr; //sets pointers in that node both directions to null
	ptr->m_prev = nullptr;
	head = ptr; //sets head and tail both to the new node
	tail = ptr;
	numItems = 0; //set the item counter to 0
}         // Create an empty set.

Set::Set(const Set& n) {
	//if (n.numItems != 0) {
		head = new Node; //same as above 
		ptr = head;
		if (n.numItems != 0)
			head->m_data = n.head->m_data; //only this time add the data member from n's head (being copied) to this set's head
		ptr->m_prev = nullptr;
		ptr->m_next = nullptr;
		tail = ptr;
		if (n.head->m_next != nullptr) //run through the linked list n and 
			for (Node* p = n.head->m_next; p != nullptr; p = p->m_next) {
				Node* x = new Node; //allocate new nodes
				tail = x;
				ptr->m_next = tail; //adjusting pointers as necessary
				tail->m_prev = ptr;
				tail->m_data = p->m_data; //and copy n's data members
				tail->m_next = nullptr;
				ptr = tail;
			}
		numItems = n.numItems; //set numitems in this set = to num items in n
	//}
}

Set::~Set() {
	Node* p = head; //p points to head
	for (p; p != nullptr; p = head) { //set p to head once again
		head = head->m_next; //move head 
		delete p; //deletes all dynamically allocated nodes
	}
}

Set& Set::operator=(const Set& n) {
	if (this != &n) { //if the two arent already at the same address
		Set j(n); //copy construct a temporary Set j equivalent to n (so we can call swap (a non constant function)
		swap(j); //sets this to j 
	}
	return *this;
}

bool Set::empty() const {
	if (numItems == 0) //pretty self explanatory, checks if the item counter is 0 or not
		return true;
	return false;
}  // Return true if the set is empty, otherwise false.

int Set::size() const {
	return numItems; //returns the number of items
}    // Return the number of items in the set.

bool Set::insert(const ItemType& value) {
	if (numItems == 0) { //if nothing is in the list yet we can just allocate the value to the data member of the node created at construction
		head->m_data = value; //this check could be avoided if I used a dummy node
		numItems = 1;
		return true;
	}
	for (ptr = head; ptr != nullptr && ptr->m_data != value; ptr = ptr->m_next) //move to the end of the list or to the instance of the value
		;
	if (ptr == nullptr) { //if we didnt find the value and are at the end of the list...
		ptr = new Node; //allocate a new node
		ptr->m_data = value; //add the value into that nodes data
		ptr->m_prev = tail; //change the new nodes backwards pointer to the former last item in the set 
		tail = ptr; // change the tail to point to the new last node
		ptr->m_next = nullptr; //the last items next pointer now must point to null
		ptr->m_prev->m_next = ptr; //the second to last items next ptr must point to the last item
		numItems++; //one more item in the list
		return true; //item was added
	}
	return false; //if we found the value already, just return false
}
// Insert value into the set if it is not already present.  Return
// true if the value was actually inserted.  Leave the set unchanged
// and return false if the value was not inserted (perhaps because it
// is already in the set or because the set has a fixed capacity and
// is full).

bool Set::erase(const ItemType& value) {
	if (numItems == 0) //if theres nothing to erase...
		return false;
	if (head->m_data == value) {
		ptr = head;

		if (numItems == 1) {//this is a slightly annoying workaround to delete and then create an empty node again when the list had only one item
			delete ptr;
			ptr = new Node;		//dynamically allocates first node
			ptr->m_next = nullptr; //sets pointers in that node both directions to null
			ptr->m_prev = nullptr;
			numItems--;
			head = ptr;
			tail = ptr;
			return true;
		}
		
		head = ptr->m_next; //sets head to the next item
		head->m_prev = nullptr; //sets the backwards pointer of the new first item to null

		delete ptr; //deletes the old first item
		numItems--; //decreases the number of items in the set
		ptr = head;
		return true;
	}
	if (tail->m_data == value) { //same thing as for head but for the other end of the list
		ptr = tail;

		tail = ptr->m_prev;
		tail->m_next = nullptr;

		delete ptr;
		numItems--;
		ptr = tail;
		return true;
	}
	for (ptr = head; ptr != nullptr && ptr->m_data != value; ptr = ptr->m_next) //if the item is not on either end of the list we run throught the list until we find it
		;
	if (ptr != nullptr) { //if we find it we remove it same way we removed the item if its at an end of the list
		ptr->m_prev->m_next = ptr->m_next; //by adjusting 2 ptrs and then 
		ptr->m_next->m_prev = ptr->m_prev;
		delete ptr; // deleting the allocated node
		numItems--;
		return true;
	}
	return false; //if we didnt find value just return false and do nothing
}
// Remove the value from the set if present.  Return true if the
// value was removed; otherwise, leave the set unchanged and
// return false.

bool Set::contains(const ItemType& value) const {
	Node* temp; //probably could have just done this with ptr... im dumb whatever
	if (numItems == 0) //if the list is empty...
		return false;
	for (temp = head; temp != nullptr && temp->m_data != value; temp = temp->m_next)//essentially performs same check we did when trying to find a value to erase but without erasing
		;
	if (temp != nullptr) {
		return true;
	}
	return false;
}
// Return true if the value is in the set, otherwise false.

bool Set::get(int i, ItemType& value) const {
	int x = 0;
	Node* temp;
	Node* temp2;
	if (numItems == 0) //if the list is empty...
		return false;
	if (0 <= i && i < numItems) { //i needs to be within the domain of possible number of data members value could be larger than
		for (temp = head; temp != nullptr; temp = temp->m_next) { //nested for loop, for every member of the set
			for (temp2 = head; temp2 != nullptr; temp2 = temp2->m_next)//checks if that member is greater than the others
				if (temp->m_data > temp2->m_data) //and if so
					x++; //increments the temporary counter
			if (x == i) { //if the counter is equal to i
				value = temp->m_data; //then that means that the data member of temp is greater than exactly i other items
				return true; // so we add it to value and return
			}
			x = 0; //resets x for every member
		}
	}
	return false; 
}
// If 0 <= i < size(), copy into value the item in the set that is
// greater than exactly i items in the set and return true.  Otherwise,


void Set::swap(Set& other) { //simply sawps all the private member pointers/numitems in two sets 
	int x;
	Node* temp;
	temp = other.ptr;
	other.ptr = ptr;
	ptr = temp;
	temp = other.head;
	other.head = head;
	head = temp;
	temp = other.tail;
	other.tail = tail;
	tail = temp;
	x = other.numItems;
	other.numItems = numItems;
	numItems = x;
}
// Exchange the contents of this set with the other one.
//Change the implementation of the swap function so that the number of statement executions when swapping two sets 
//is the same no matter how many items are in the sets. (You would not satisfy this requirement if, for example, 
//your swap function caused a loop to visit each item in the set, 
//since the number of statements executed by all the iterations of the loop would depend on the number of items in the set.

void unite(const Set& s1, const Set& s2, Set& result) { //nonmember functions
	ItemType value1;
	ItemType value2;
	Set* temp = new Set; //allocates a new set to copy into the result
	if (!s1.empty()) { //assumin s1 is not empty...
		for (int i = 0; i < s1.size(); i++) { //goes throught the set
			s1.get(i, value1); //gets every value
			temp->insert(value1); //and adds it to the new set, if it is not already there
		}
	}
	if (!s2.empty()) { //same thing as for s1
		for (int i = 0; i < s2.size(); i++) {
			s2.get(i, value2);
			temp->insert(value2);
		}
	}
	result = *temp; //sets result equal to the temporary set
	delete temp; //delets the dynamically allocated set
}

void subtract(const Set& s1, const Set& s2, Set& result) {
	ItemType value1;
	ItemType value2;
	Set* temp = new Set; 
	if (!s1.empty()) { //same stuff we did in unite
		for (int i = 0; i < s1.size(); i++) {
			s1.get(i, value1);
			temp->insert(value1);
		}
	}
	if (!s2.empty()) { //only this time
		for (int i = 0; i < s2.size(); i++) {
			s2.get(i, value2);
			temp->erase(value2); // we try to erase everything in s2 from s1 instead of inserting it
		}
	}
	result = *temp;
	delete temp;
}