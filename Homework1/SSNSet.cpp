#include "SSNSet.h"
#include <iostream>
using namespace std;

SSNSet::SSNSet() {
	Set ssnset;
}          // Create an empty SSN set.

bool SSNSet::add(unsigned long ssn) {
	if (ssnset.insert(ssn))
		return true;
	return false;
}
// Add an SSN to the SSNSet.  Return true if and only if the SSN
// was actually added.

int SSNSet::size() const {
	return ssnset.size();
}  // Return the number of SSNs in the SSNSet.

void SSNSet::print() const {
	for (int i = 0; i < ssnset.size(); i++) {
		ItemType x;
		ssnset.get(i, x);
		cout << x << endl;
	}
}
// Write every SSN in the SSNSet to cout exactly once, one per
// line.  Write no other text.