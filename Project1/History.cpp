#include "History.h"
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

History::History(int nRows, int nCols) {
	hRows = nRows;
	hCols = nCols;

	for (int i = 0; i < hRows; i++) {
		for (int j = 0; j < hCols; j++) {
			hGrid[i][j] = '.';
		}
	}
}
bool History::record(int r, int c) {
	if (r > hRows || c > hCols || r < 1 || c < 1)
		return false;
	if (hGrid[r - 1][c - 1] == '.') {
		hGrid[r - 1][c - 1] = 'A';
		return true;
	}
	if (hGrid[r - 1][c - 1] >= 'A' && hGrid[r - 1][c - 1] < 'Z')
		hGrid[r - 1][c - 1]++;
	
	//string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXY";

	// Fill displayGrid with dots (empty) and stars (poison pellets)
	//for (r = 1; r <= hRows; r++)
	//	for (c = 1; c <= hCols; c++) {
	//		if (hGrid[r - 1][c - 1] > 0 && hGrid[r - 1][c - 1] < 25)
	//			hGrid[r - 1][c - 1] = alphabet[hGrid[r - 1][c - 1] - 1];
	//		if (hGrid[r - 1][c - 1] >= 25)
	//			hGrid[r - 1][c - 1] = 'Z';
	//	}
	return true;
}
void History::display() const {
	clearScreen();
	
	for (int i = 0; i < hRows; i++) {
		for (int j = 0; j < hCols; j++) {
			cout << hGrid[i][j];
		}
		cout << endl;
	}
	cout << endl;

}