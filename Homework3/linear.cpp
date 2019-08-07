bool allTrue(const string a[], int n) {
	if (n == 1) return (somePredicate(a));

	return (somePredicate(a) && allTrue(a + 1, n - 1));
}

int countFalse(const string a[], int n) {
	
	int jeff = 0;
	if (!somePredicate(a))
		jeff++;
	if (n == 1) return jeff;

	return (jeff + countFalse(a + 1, n - 1));
}

int firstFalse(const string a[], int n)
{

	if (n < 1) return -1;

	if (n == 1)
		if (!somePredicate(a))
			return 0;
		else
			return -1;
	a = a + n - 1;
	if (!somePredicate(a) && firstFalse (a - n + 1, n - 1) == -1)
		return n - 1;
	else
		return firstFalse(a - n + 1, n - 1);

}

int indexOfLeast(const string a[], int n)
{
	if (n < 1) return -1;

	if (n == 1)
		return 0;
	a = a + n - 1;
	if (*a < *(a - n + 1 + indexOfLeast(a - n + 1, n - 1)))
		return n - 1;
	else
		return indexOfLeast(a - n + 1, n - 1);

	//return -999;  // This is incorrect.
}

bool includes(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 1)
		return false;
	if (n2 > n1)
		return false;
	
	if (n2 == 1)
		if (*a1 == *a2)
			return true;
		else
			return (includes(a1 + 1, n1 - 1, a2, n2));

	if (*a1 == *a2)
		return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
	else
		return includes(a1 + 1, n1 - 1, a2, n2);


	
	// This is not always correct.
}
