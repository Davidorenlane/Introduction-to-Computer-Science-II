/*
void removeBad(list<Movie*>& li)
{
	list<Movie*>::iterator b = li.begin();
	
	while (b != li.end()) {
		if ((*b)->rating() < 50) {
			Movie* deleter = *b;
			b = li.erase(b);
			delete deleter;	
		}
		else {
			b++;
		}	
	}
}
*/