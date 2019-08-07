#include <queue>
#include <iostream>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
	queue<Coord> x;
	Coord start(sr, sc);
	Coord location(sr, sc);
	x.push(start);
	maze[sr][sc] = 'P';
	while (!x.empty()) {
		location = x.front();
		x.pop();
		if (location.r() == er && location.c() == ec)
			return true;
		if (maze[location.r() - 1][location.c()] == '.') {
			Coord n(location.r() - 1, location.c());
			x.push(n);
			maze[location.r() - 1][location.c()] = 'P';
		}
		if (maze[location.r()][location.c() + 1] == '.') {
			Coord e(location.r(), location.c() + 1);
			x.push(e);
			maze[location.r()][location.c() + 1] = 'P';
		}
		if (maze[location.r() + 1][location.c()] == '.') {
			Coord s(location.r() + 1, location.c());
			x.push(s);
			maze[location.r() + 1][location.c()] = 'P';
		}
		if (maze[location.r()][location.c() - 1] == '.') {
			Coord w(location.r(), location.c() - 1);
			x.push(w);
			maze[location.r()][location.c() - 1] = 'P';
		}
	}
	return false;
}
int main()
{
}