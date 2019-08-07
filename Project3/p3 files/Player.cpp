#include "Player.h"
#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*bool canShipsFit(const Board& b, const Game& g){
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
}*/

//*********************************************************************
//  AwfulPlayer
//*********************************************************************

class AwfulPlayer : public Player
{
  public:
    AwfulPlayer(string nm, const Game& g);
    virtual bool placeShips(Board& b);
    virtual Point recommendAttack();
    virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
                                                bool shipDestroyed, int shipId);
    virtual void recordAttackByOpponent(Point p);
  private:
    Point m_lastCellAttacked;
};

AwfulPlayer::AwfulPlayer(string nm, const Game& g)
 : Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool AwfulPlayer::placeShips(Board& b)
{
      // Clustering ships is bad strategy
    for (int k = 0; k < game().nShips(); k++)
        if ( ! b.placeShip(Point(k,0), k, HORIZONTAL))
            return false;
    return true;
}

Point AwfulPlayer::recommendAttack()
{
    if (m_lastCellAttacked.c > 0)
        m_lastCellAttacked.c--;
    else
    {
        m_lastCellAttacked.c = game().cols() - 1;
        if (m_lastCellAttacked.r > 0)
            m_lastCellAttacked.r--;
        else
            m_lastCellAttacked.r = game().rows() - 1;
    }
    return m_lastCellAttacked;
}

void AwfulPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
                                     bool /* shotHit */, bool /* shipDestroyed */,
                                     int /* shipId */)
{
      // AwfulPlayer completely ignores the result of any attack
}

void AwfulPlayer::recordAttackByOpponent(Point /* p */)
{
      // AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  HumanPlayer
//*********************************************************************
class HumanPlayer : public Player
{
public:
	HumanPlayer(string nm, const Game& g);
	virtual bool placeShips(Board& b);
	virtual Point recommendAttack();
	virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
		bool shipDestroyed, int shipId);
	virtual void recordAttackByOpponent(Point p);
	virtual bool isHuman() const;
private:
	Point m_lastCellAttacked;
};


bool getLineWithTwoIntegers(int& r, int& c)
{
	bool result(cin >> r >> c);
	if (!result)
		cin.clear();  // clear error state so can do more input operations
	cin.ignore(10000, '\n');
	return result;
}

bool HumanPlayer::isHuman() const
{ return true; }


HumanPlayer::HumanPlayer(string nm, const Game& g)
	: Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool HumanPlayer::placeShips(Board& b)
{
	cout << name() << " must place " << game().nShips() << " ships." << endl;
	int repeater = 0;
	int r;
	int c;
	string dir = "x";
	for (int i = 0; i < game().nShips(); i++){
		if (repeater == 0)
			b.display(false);
		if (repeater < 2){
			cout << "Enter h or v for direction of " << game().shipName(i) << " (length " << game().shipLength(i) << "): ";
			getline(cin, dir);
		}
		repeater = 0;
		if (dir == "h") {
			cout << "Enter row and column of leftmost cell (e.g. 3 5): ";
			if (!getLineWithTwoIntegers(r, c)) {
				repeater = 2;
				i--;
				cout << "You must enter two integers." << endl;
			}
			Point start(r, c);
			if (repeater != 2 && !b.placeShip(start, i, HORIZONTAL)){
				repeater = 2;
				i--;
				cout << "The ship cannot be placed there." << endl;
			}
		}
		else if (dir == "v"){
			cout << "Enter row and column of topmost cell (e.g. 3 5): ";
			if (!getLineWithTwoIntegers(r, c)) {
				repeater = 2;
				i--;
				cout << "You must enter two integers." << endl;
			}
			Point start(r, c);
			if (repeater != 2 && !b.placeShip(start, i, VERTICAL)) {
				repeater = 2;
				i--;
				cout << "The ship cannot be placed there." << endl;
			}
		}
		else {
			cout << "Direction must be h or v." << endl;
			i--;
			repeater = 1;
		}
	}
	return true;
}

Point HumanPlayer::recommendAttack()
{
	int r;
	int c;
	bool integers = true;
	while (integers) { 
		cout << "Enter the row and column to attack (e.g. 3 5): ";
		integers = !getLineWithTwoIntegers(r, c);
	}
	Point recommendation(r, c);
	return recommendation;
}

void HumanPlayer::recordAttackResult(Point /* p */, bool /* validShot */,
	bool /* shotHit */, bool /* shipDestroyed */,
	int /* shipId */)
{
	// AwfulPlayer completely ignores the result of any attack
}

void HumanPlayer::recordAttackByOpponent(Point /* p */)
{
	// AwfulPlayer completely ignores what the opponent does
}




//*********************************************************************
//  MediocrePlayer
//*********************************************************************

class MediocrePlayer : public Player
{
public:
	MediocrePlayer(string nm, const Game& g);
	virtual bool placeShips(Board& b);
	virtual Point recommendAttack();
	virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
		bool shipDestroyed, int shipId);
	virtual void recordAttackByOpponent(Point p);
private:
	Point m_lastCellAttacked;
	int state = 1;
	vector<int> aps;
	bool lastShotValid = false;
	bool didShotHit = false;
	bool wasShipDestroyed = false;
	Point hitPoint;
};

/*bool shipPlacer(Board& b, Game& g, int shipId, Point P) {
	if (shipId == g.nShips() - 1) { //if we're on the last ship
		bool result = false;
		for (int i = 0; i < g.rows(); i++)
			for (int j = 0; j < g.cols(); j++) {
				Point p(i, j);
				if (b.placeShip(p, shipId, HORIZONTAL)) {
					result = true;
				}	
				if (b.placeShip(p, shipId, VERTICAL)) {
					result = true;
				}//check to see if it can fit
			}
		return result; //otherwise report that it cant
	}
	for (int i = 0; i < g.rows(); i++)
		for (int j = 0; j < g.cols(); j++) {
			Point p(i, j);
			if (b.placeShip(p, shipId, HORIZONTAL)) {
				b.unplaceShip(p, shipId, HORIZONTAL);
				v.push_back(p);
			}
			if (b.placeShip(p, shipId, VERTICAL)) {
				b.unplaceShip(p, shipId, VERTICAL);
				v.push_back(p);
			}//check to see if it can fit
		}
	vector<Point>::iterator x = v.begin();
	//for ()
	if (shipPlacer(b, g, shipId - 1, v))
		for (int i = 0; i < g.rows(); i++)
			for (int j = 0; j < g.cols(); j++) {
				Point p(i, j);
				if (b.placeShip(p, shipId, HORIZONTAL))
					return true;
				if (b.placeShip(p, shipId, VERTICAL))
					return true;
			}
	else {
		v.pop_back();
		shipPlacer(b, g, shipId - 1, v);
	}
}

bool shipFitter(Board& b, const Game& g) {
	int tries = 0;
	b.block();
	while (tries < 50) {
		if (shipPlacer(b,game(), ))
			return true;
		b.unblock();
		b.block();
		tries++;
	}
	return false;

}*/

MediocrePlayer::MediocrePlayer(string nm, const Game& g)
	: Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool MediocrePlayer::placeShips(Board& b)
{
	int totalshipsize = 0;
	for (int i = 0; i < game().nShips(); i++)
		totalshipsize += game().shipLength(i);
	if (totalshipsize > game().rows()*game().cols())
		return false;
	Point AC(0, 2);
	Point sub(7, 8);
	Point BS(2, 9);
	Point PB(9, 2);
	Point Dest(6, 1);
	for (int i = 0; i < game().nShips(); i++) {
		if (game().shipName(i) == "aircraft carrier")
			b.placeShip(AC, i, HORIZONTAL);
		else if (game().shipName(i) == "submarine")
			b.placeShip(sub, i, VERTICAL);
		else if (game().shipName(i) == "battleship")
			b.placeShip(BS, i, VERTICAL);
		else if (game().shipName(i) == "destroyer")
			b.placeShip(Dest, i, VERTICAL);
		else if (game().shipName(i) == "patrol boat")
			b.placeShip(PB, i, HORIZONTAL);
		else
		{
			if (!b.placeShip(Point(i, 0), i, HORIZONTAL))
				return false;
		}
	}
	return true;
}

Point MediocrePlayer::recommendAttack()
{
	if (state == 1 && didShotHit) {
		state = 2;
		hitPoint = m_lastCellAttacked;
	}
	if (wasShipDestroyed)
		state = 1;
	while (state == 1) {
		int x = randInt(game().rows());
		int y = randInt(game().cols());
		int checker = (x * 10) + y;
		if (find(aps.begin(), aps.end(), checker) == aps.end()) {
			aps.push_back(checker);
			return Point(x, y);
		}
	}
	while (state == 2) {
		int iter = 0;
		int arr[18];
		for (int i = 0; i < 9; i++){
			int x = hitPoint.r - 4 + i;
			int y = hitPoint.c;
			int checker = (x * 10) + y;
			if (x >= 0 && y >= 0) {
				arr[iter] = checker;
				iter++;
			}
		}
		for (int i = 0; i < 9; i++) {
			int x = hitPoint.r;
			int y = hitPoint.c - 4 + i;
			int checker = (x * 10) + y;
			if (x >= 0 && y >= 0) {
				arr[iter] = checker;
				iter++;
			}
		}
		int point = arr[randInt(iter + 1)];
		int r = point / 10;
		int c = point % 10;
		if (game().isValid(Point(r, c)))
			if (find(aps.begin(), aps.end(), point) == aps.end()) {
				aps.push_back(point);
				return Point(r, c);
			}
	}
}

void MediocrePlayer::recordAttackResult(Point p, bool validShot,
	bool shotHit, bool shipDestroyed,
	int shipId)
{
	m_lastCellAttacked = p;
	lastShotValid = validShot;
	didShotHit = shotHit;
	wasShipDestroyed = shipDestroyed;
}

void MediocrePlayer::recordAttackByOpponent(Point /* p */)
{
	// AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  GoodPlayer
//*********************************************************************

class GoodPlayer : public Player
{
public:
	GoodPlayer(string nm, const Game& g);
	virtual bool placeShips(Board& b);
	virtual Point recommendAttack();
	virtual void recordAttackResult(Point p, bool validShot, bool shotHit,
		bool shipDestroyed, int shipId);
	virtual void recordAttackByOpponent(Point p);
private:
	Point m_lastCellAttacked;
	int state = 1;
	vector<int> aps;
	vector<int> hits;
	vector<int> pops;
	bool lastShotValid = false;
	bool didShotHit = false;
	bool didPrevHit = false;
	bool didPrevPrevHit = false;
	bool wasShipDestroyed = false;
	Point hitPoint;
	int shipSunk = 4;
	int longestShip = 5;
	bool checkered = false;
};

GoodPlayer::GoodPlayer(string nm, const Game& g)
	: Player(nm, g), m_lastCellAttacked(0, 0)
{}

bool GoodPlayer::placeShips(Board& b)
{
	int totalshipsize = 0;
	for (int i = 0; i < game().nShips(); i++)
		totalshipsize += game().shipLength(i);
	if (totalshipsize > game().rows()*game().cols())
		return false;
	Point AC(0, 2);
	Point sub(7, 8);
	Point BS(2, 9);
	Point PB(9, 2);
	Point Dest(6, 1);
	for (int i = 0; i < game().nShips(); i++) {
		if (game().shipName(i) == "aircraft carrier")
			b.placeShip(AC, i, HORIZONTAL);
		else if (game().shipName(i) == "submarine")
			b.placeShip(sub, i, VERTICAL);
		else if (game().shipName(i) == "battleship")
			b.placeShip(BS, i, VERTICAL);
		else if (game().shipName(i) == "destroyer")
			b.placeShip(Dest, i, VERTICAL);
		else if (game().shipName(i) == "patrol boat")
			b.placeShip(PB, i, HORIZONTAL);
		else
		{
			if (!b.placeShip(Point(i, 0), i, HORIZONTAL))
				return false;
		}
	}
	return true;
}

Point GoodPlayer::recommendAttack()
{
	if (game().shipLength(shipSunk) == 5)
		longestShip = 4;
	//if (longestShip == 4 && game().shipLength(shipSunk) == 4)
	//	longestShip = 3;*/
	if (wasShipDestroyed)
		pops.push_back(m_lastCellAttacked.r * 10 + m_lastCellAttacked.c);
	if (didShotHit == true)
		hits.push_back(m_lastCellAttacked.r * 10 + m_lastCellAttacked.c);
	if ((state == 1 || state == 3) && didShotHit) {
		state = 2;
		hitPoint = m_lastCellAttacked;
	}
if (wasShipDestroyed)
{
	state = 1;
}
	while (state == 1) {
		if (checkered == true)
		{
			state = 3;
			break;
		}
		int x = randInt(game().rows());
		int y = randInt(game().cols());
		int checker = (x * 10) + y;
		if (y % 2 != x % 2)
			if (find(aps.begin(), aps.end(), checker) == aps.end()) {
				aps.push_back(checker);
				return Point(x, y);
			}
		checkered = true;
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				if (i % 2 != j % 2 && find(aps.begin(), aps.end(), (i * 10) + j) == aps.end())
				{
					checkered = false;
				}
	}
	while (state == 2){
		int iter = 0;
		int arr[18];
		for (int i = 0; i < 2*longestShip - 1; i++) {
			int x = hitPoint.r - (longestShip - 1) + i;
			int y = hitPoint.c;
			int checker = (x * 10) + y; 
			if (x >= 0 && y >= 0) {
				arr[iter] = checker;
				iter++;
			}
		}
		for (int i = 0; i < 2 * longestShip - 1; i++) {
			int x = hitPoint.r;
			int y = hitPoint.c - (longestShip - 1) + i;
			int checker = (x * 10) + y;
			if (x >= 0 && y >= 0) {
				arr[iter] = checker;
				iter++;
			}
		}
		int point = arr[randInt(iter + 1)];
		int r = point / 10;
		int c = point % 10;
		if (game().isValid(Point(r, c)))
			if (find(aps.begin(), aps.end(), point) == aps.end()) {
				aps.push_back(point);
				return Point(r, c);
			}
	}
	while (state == 3) {
		int point = hits.at(randInt(hits.size()));
		int y = randInt(4);
		switch (y) {
		case 0:
			point -= 10;
			break;
		case 1:
			point += 10;
			break;
		case 2:
			point -= 1;
			break;
		case 3:
			point += 1;
			break;
		}
		int r = point / 10;
		int c = point % 10;

		if (game().isValid(Point(r, c)))
			if (find(aps.begin(), aps.end(), point) == aps.end()) {
				aps.push_back(point);
				return Point(r, c);
			}
	}
}

void GoodPlayer::recordAttackResult(Point p, bool validShot,
	bool shotHit, bool shipDestroyed,
	int shipId)
{
	m_lastCellAttacked = p;
	lastShotValid = validShot;
	didPrevPrevHit = didPrevHit;
	didPrevHit = didShotHit;
	didShotHit = shotHit;
	wasShipDestroyed = shipDestroyed;
	shipSunk = shipId;
}

void GoodPlayer::recordAttackByOpponent(Point /* p */)
{
	// AwfulPlayer completely ignores what the opponent does
}

//*********************************************************************
//  createPlayer
//*********************************************************************

Player* createPlayer(string type, string nm, const Game& g)
{
    static string types[] = {
        "human", "awful", "mediocre", "good"
    };
    
    int pos;
    for (pos = 0; pos != sizeof(types)/sizeof(types[0])  &&
                                                     type != types[pos]; pos++)
        ;
    switch (pos)
    {
      case 0:  return new HumanPlayer(nm, g);
      case 1:  return new AwfulPlayer(nm, g);
      case 2:  return new MediocrePlayer(nm, g);
      case 3:  return new GoodPlayer(nm, g);
      default: return nullptr;
    }
}
