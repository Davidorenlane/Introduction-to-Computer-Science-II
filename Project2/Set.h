#ifndef SET_H //header guards
#define SET_H

#include <string>

typedef std::string ItemType;

class Set
{
public:
	Set();
	~Set();
	Set(const Set& n);
	Set& operator=(const Set& n);

	bool empty()const;  
	int size()const;   
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int i, ItemType& value) const;
	void swap(Set& other);
private:
	struct Node { //struct declaration for doubly linked nodes
		ItemType m_data;
		Node* m_next;
		Node* m_prev;
	};
	Node* ptr;
	Node* head;
	Node* tail;
	int numItems;
};

void unite(const Set& s1, const Set& s2, Set& result); //nonmember function declarations outside and after the class declaration
void subtract(const Set& s1, const Set& s2, Set& result);

#endif // !SET_H

