#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>

using namespace std;

class BoardImpl
{
  public:
    BoardImpl(const Game& g);
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;
  private:
	char m_contents[MAXROWS][MAXCOLS];
	const Game& m_game;
};

BoardImpl::BoardImpl(const Game& g)
 : m_game(g)
{
	for (int i = 0; i < g.rows(); i++)
		for (int j = 0; j < g.cols(); j++)
			m_contents[i][j] = '.';
	// This compiles, but may not be correct
}

void BoardImpl::clear()
{
	for (int i = 0; i < m_game.rows(); i++)
		for (int j = 0; j < m_game.cols(); j++)
			m_contents[i][j] = '.';
    // This compiles, but may not be correct
}

void BoardImpl::block()
{
      // Block cells with 50% probability
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
            if (randInt(2) == 0)
            {
                m_contents[r][c] = 'N'; // TODO:  Replace this with code to block cell (r,c)
            }
}

void BoardImpl::unblock()
{
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
        {	
			if (m_contents[r][c] == 'N')
				m_contents[r][c] = '.'; // TODO:  Replace this with code to unblock cell (r,c) if blocked
        }
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{
	if (!m_game.isValid(topOrLeft))
		return false;
	if (m_game.nShips() - 1 < shipId || shipId < 0)
		return false;

	if (dir == HORIZONTAL) {
		if (topOrLeft.c + m_game.shipLength(shipId) > m_game.cols())
			return false;
		for (int i = 0; i < m_game.shipLength(shipId); i++)
			if (m_contents[topOrLeft.r][topOrLeft.c + i] != '.')
				return false;
		for (int i = 0; i < m_game.shipLength(shipId); i++)
			m_contents[topOrLeft.r][topOrLeft.c + i] = m_game.shipSymbol(shipId);
	}
	if (dir == VERTICAL) {
		if (topOrLeft.r + m_game.shipLength(shipId) > m_game.rows())
			return false;
		for (int i = 0; i < m_game.shipLength(shipId); i++)
			if (m_contents[topOrLeft.r + i][topOrLeft.c] != '.')
				return false;
		for (int i = 0; i < m_game.shipLength(shipId); i++)
			m_contents[topOrLeft.r + i][topOrLeft.c] = m_game.shipSymbol(shipId);
	}
    return true; // This compiles, but may not be correct
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
	if (!m_game.isValid(topOrLeft))
		return false;
	if (m_game.nShips() - 1 < shipId || shipId < 0)
		return false;

	if (dir == HORIZONTAL) {
		if (topOrLeft.c + m_game.shipLength(shipId) > m_game.cols())
			return false;
		for (int i = 0; i < m_game.shipLength(shipId); i++)
			if (m_contents[topOrLeft.r + i][topOrLeft.c] != m_game.shipSymbol(shipId))
				return false;
		for (int i = 0; i < m_game.shipLength(shipId); i++)
			m_contents[topOrLeft.r][topOrLeft.c + i] = '.';
	}
	if (dir == VERTICAL) {
		if (topOrLeft.r + m_game.shipLength(shipId) > m_game.rows())
			return false;
		for (int i = 0; i < m_game.shipLength(shipId); i++)
			if (m_contents[topOrLeft.r + i][topOrLeft.c] != m_game.shipSymbol(shipId))
				return false;
		for (int i = 0; i < m_game.shipLength(shipId); i++)
			m_contents[topOrLeft.r + i][topOrLeft.c] = '.';
	}
	return true; // This compiles, but may not be correct
}

void BoardImpl::display(bool shotsOnly) const
{
	cout << "  ";
	for (int i = 0; i < m_game.cols(); i++)
		cout << i;
	cout << endl;
	for (int i = 0; i < m_game.rows(); i++)
	{
		cout << i << ' ';
		for (int j = 0; j < m_game.cols(); j++)
		{
			if (shotsOnly)
				if (m_contents[i][j] == 'o' || m_contents[i][j] == 'X')
					cout << m_contents[i][j];
				else
					cout << '.';
			if (!shotsOnly)
				cout << m_contents[i][j];
		}
		cout << endl;
	}
	// This compiles, but may not be correct
}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    if (!m_game.isValid(p))
		return false;
	if (m_contents[p.r][p.c] == 'o' || m_contents[p.r][p.c] == 'X')
		return false;
	if (m_contents[p.r][p.c] == '.') {
		m_contents[p.r][p.c] = 'o';
		shotHit = false;
		return true;
	}
	shotHit = true;
	for (int i = 0; i < m_game.nShips(); i++)
		if (m_contents[p.r][p.c] == m_game.shipSymbol(i))
			shipId = i;
	m_contents[p.r][p.c] = 'X';
	shipDestroyed = true;
	for (int i = 0; i < m_game.rows(); i++)
		for (int j = 0; j < m_game.cols(); j++)
			if (m_contents[i][j] == m_game.shipSymbol(shipId))
				shipDestroyed = false;
	return true;

	// This compiles, but may not be correct
}

bool BoardImpl::allShipsDestroyed() const
{
	for (int i = 0; i < m_game.rows(); i++)
		for (int j = 0; j < m_game.cols(); j++)
			if (m_contents[i][j] != 'o' && m_contents[i][j] != 'X' && m_contents[i][j] != '.')
				return false; 
	return true;// This compiles, but may not be correct
}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}
