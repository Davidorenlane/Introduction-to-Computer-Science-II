
int countIncludes(const string a1[], int n1, const string a2[], int n2)
{
	if (n2 <= 0)
		return 1;
	if (n1 <= 0)
		return 0;
	if (n2 == 1 && *a1 == *a2)
		return 1;
	if (n2 > n1)
		return 0;
	if (*a1 == *a2) {
		return (countIncludes(a1 + 1, n1 - 1, a2, n2) + countIncludes(a1 + 1, n1 - 1, a2 + 1, n2 - 1));
	}
	else
		return countIncludes(a1 + 1, n1 - 1, a2, n2);
}


// Exchange two strings
void exchange(string& x, string& y)
{
	string t = x;
	x = y;
	y = t;
}

// Rearrange the elements of the array so that all the elements
// whose value is < separator come before all the other elements,
// and all the elements whose value is > separator come after all
// the other elements.  Upon return, firstNotLess is set to the
// index of the first element in the rearranged array that is
// >= separator, or n if there is no such element, and firstGreater is
// set to the index of the first element that is > separator, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotLess, a[i] < separator
//   * for firstNotLess <= i < firstGreater, a[i] == separator
//   * for firstGreater <= i < n, a[i] > separator
// All the elements < separator end up in no particular order.
// All the elements > separator end up in no particular order.
void separate(string a[], int n, string separator,
	int& firstNotLess, int& firstGreater)
{
	if (n < 0)
		n = 0;

	// It will always be the case that just before evaluating the loop
	// condition:
	//  firstNotLess <= firstUnknown and firstUnknown <= firstGreater
	//  Every element earlier than position firstNotLess is < separator
	//  Every element from position firstNotLess to firstUnknown-1 is
	//    == separator
	//  Every element from firstUnknown to firstGreater-1 is not known yet
	//  Every element at position firstGreater or later is > separator

	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
		if (a[firstUnknown] > separator)
		{
			firstGreater--;
			exchange(a[firstUnknown], a[firstGreater]);
		}
		else
		{
			if (a[firstUnknown] < separator)
			{
				exchange(a[firstNotLess], a[firstUnknown]);
				firstNotLess++;
			}
			firstUnknown++;
		}
	}
}

// Rearrange the elements of the array so that
// a[0] <= a[1] <= a[2] <= ... <= a[n-2] <= a[n-1]
// If n <= 1, do nothing.
void order(string a[], int n)
{
	if (n < 0)
		n = 0;
	int notLessIndex = 0;
	int greaterIndex = 0;
	separate(a, n, a[0], notLessIndex, greaterIndex);
	if (notLessIndex > 1)
		order(a, notLessIndex);
	if (greaterIndex < n - 1)
		order(a + notLessIndex, n - notLessIndex);
	return;  // This is not always correct.
}
