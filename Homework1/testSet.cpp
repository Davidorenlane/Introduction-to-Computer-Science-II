#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Set numbers;
	numbers.insert(10000);
	numbers.insert(20000);
	numbers.insert(30000);
	numbers.insert(40000);
	numbers.insert(50000);
	numbers.insert(10000);
	assert(numbers.size() == 5);  // duplicate not added
	numbers.erase(10000);
	assert(numbers.size() == 4);
	ItemType xx;
	numbers.get(0, xx);
	assert(xx == 20000);  // 20000 is greater than 0 numbers
	numbers.get(3, xx);
	assert(xx == 50000);  // 50000 is greater than 3 numbers

/*	Set bob;
	bob.insert("left");
	assert(!bob.contains(""));
	bob.insert("raft");
	bob.insert("");
	bob.insert("flat");
	assert(bob.contains(""));
	bob.erase("left");
	assert(bob.size() == 3) ;
	assert(bob.contains("flat"));
	assert(bob.contains("raft"));
	assert(bob.contains(""));
	string x;
	assert(bob.get(1, x) && x == "flat");
	assert(bob.get(0, x) && x == "");*/

	cout << "Passed all tests" << endl;
}