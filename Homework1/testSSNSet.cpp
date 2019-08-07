#include "SSNSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{	
	SSNSet ss;
	ss.add(10000);
	ss.add(20000);
	ss.add(30000);
	ss.add(10000);
	ss.add(40000);
	assert(ss.size() == 4);
	ss.print();
	cout << "Passed all tests" << endl;
}