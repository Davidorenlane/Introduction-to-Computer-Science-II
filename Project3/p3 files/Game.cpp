#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>

using namespace std;


class Ship
{
public:
	Ship(int length, char symbol, string name) : length(length), symbol(symbol), name(name) {};
	int length;
	char symbol;
	string name; //id is the position in the vector
}; 

class GameImpl
{
  public:
    GameImpl(int nRows, int nCols);
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const;
    Player* play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);
private:
	int m_rows;
	int m_cols;
	int m_ships = 0;
	vector<Ship*> sv;
	//Board b1;
	//Board b2;

};


void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

GameImpl::GameImpl(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
}

int GameImpl::rows() const
{
    return m_rows;  
}

int GameImpl::cols() const
{
    return m_cols; 
}

bool GameImpl::isValid(Point p) const
{
    return p.r >= 0  &&  p.r < rows()  &&  p.c >= 0  &&  p.c < cols();
}

Point GameImpl::randomPoint() const
{
    return Point(randInt(rows()), randInt(cols()));
}

bool GameImpl::addShip(int length, char symbol, string name)
{
	Ship* oneShip = new Ship(length, symbol, name);
	sv.push_back(oneShip);
	m_ships++;
    return true;  // This compiles but may not be correct
}

int GameImpl::nShips() const
{
    return m_ships;  
}

int GameImpl::shipLength(int shipId) const
{
	
    return sv.at(shipId)->length;  // This compiles but may not be correct
}

char GameImpl::shipSymbol(int shipId) const
{
	
    return sv.at(shipId)->symbol;  // This compiles but may not be correct
}

string GameImpl::shipName(int shipId) const
{
	
	return sv.at(shipId)->name;  // This compiles but may not be correct
}

Player* GameImpl::play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause)
{
	bool validShot = true;
	bool shotHit = false;
	bool shipDestroyed = false;
	int idHit = 0;
    if (!(p1->placeShips(b1) && p2->placeShips(b2))) return nullptr; 
	while (!(b1.allShipsDestroyed() && b2.allShipsDestroyed())) {
		cout << p1->name() << "'s turn.  Board for " << p2->name() << ":" << endl;
		b2.display(p1->isHuman());
		Point p = p1->recommendAttack();
		validShot = true;
		shipDestroyed = false;
		shotHit = false;
		if (!b2.attack(p, shotHit, shipDestroyed, idHit)) {
			cout << p1->name() << " wasted a shot at (" << p.r << "," << p.c << ")." << endl;
			validShot = false;
		}
		else if (shipDestroyed) {
			cout << p1->name() << " attacked (" << p.r << "," << p.c << ") and destroyed the " << p2->game().shipName(idHit) << ", resulting in:" << endl;
			b2.display(p1->isHuman());
		}
		else if (shotHit) {
			cout << p1->name() << " attacked (" << p.r << "," << p.c << ") and hit something, resulting in:" << endl;
			b2.display(p1->isHuman());
		}
		else {
			cout << p1->name() << " attacked (" << p.r << "," << p.c << ") and missed, resulting in:" << endl;
			b2.display(p1->isHuman());
		}
		p1->recordAttackResult(p, validShot, shotHit, shipDestroyed, idHit);
		p2->recordAttackByOpponent(p);
		if (b2.allShipsDestroyed()) {
			cout << p1->name() << " wins!" << endl;
			return p1;
		}
		if (shouldPause){
			cout << "Press enter to continue:";
			cin.ignore(10000, '\n');
		}
		cout << p2->name() << "'s turn.  Board for " << p1->name() << ":" << endl;
		b1.display(p2->isHuman());
		p = p2->recommendAttack();
		validShot = true;
		shipDestroyed = false;
		shotHit = false;
		if (!b1.attack(p, shotHit, shipDestroyed, idHit)) {
			cout << p2->name() << " wasted a shot at (" << p.r << "," << p.c << ")." << endl;
			validShot = false;
		}
		else if (shipDestroyed) {
			cout << p2->name() << " attacked (" << p.r << "," << p.c << ") and destroyed the " << p1->game().shipName(idHit) << ", resulting in:" << endl; 
			b1.display(p2->isHuman());
		}
		else if (shotHit) {
			cout << p2->name() << " attacked (" << p.r << "," << p.c << ") and hit something, resulting in:" << endl;
			b1.display(p2->isHuman());
		}
		else {
			cout << p2->name() << " attacked (" << p.r << "," << p.c << ") and missed, resulting in:" << endl;
			b1.display(p2->isHuman());
		}
		p2->recordAttackResult(p, validShot, shotHit, shipDestroyed, idHit);
		p1->recordAttackByOpponent(p);
		if (b1.allShipsDestroyed()) {
			cout << p2->name() << " wins!" << endl;
			return p2;
		}
		if (shouldPause) {
			cout << "Press enter to continue:";
			cin.ignore(10000, '\n');
		}
	}
	return nullptr; // This compiles but may not be correct
}

//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1  ||  nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1  ||  nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols);
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows()  &&  length > cols())
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
             << endl;
        return false;
    }
    if (!isascii(symbol)  ||  !isprint(symbol))
    {
        cout << "Unprintable character with decimal value " << symbol
             << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X'  ||  symbol == '.'  ||  symbol == 'o')
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
             << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
                 << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0  &&  shipId < nShips());
    return m_impl->shipName(shipId);
}

Player* Game::play(Player* p1, Player* p2, bool shouldPause)
{
    if (p1 == nullptr  ||  p2 == nullptr  ||  nShips() == 0)
        return nullptr;
    Board b1(*this);
    Board b2(*this);
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}

