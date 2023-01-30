#pragma once
#include "Card.h"

/* [ CardFour ] Summary:
	Its Apply() Function: Prevent the player from playing for one turn
	Its Parameters: It has no parameters/data members
*/


class CardFour : public Card
{
public:
	CardFour(const CellPosition& pos);
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	void Save(ofstream& OutFile, int type, string file);
	void Load(ifstream& infile, int type, string file);
	virtual ~CardFour();
};

