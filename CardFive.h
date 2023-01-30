#pragma once
#include "Card.h"

/*[ CardFive ] Summary:
 Its Apply() Function: Get the just rolled dice number and subtract it from the current cell number
                       then move the player to the postion of the cell number calculated previously 
 Its Parameters: It has no parameters/data members
 */

class CardFive : public Card
{
public:
	CardFive(const CellPosition& pos);
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	void Save(ofstream& OutFile, int type, string file);
	void Load(ifstream& infile, int type, string file);
	virtual ~CardFive();
};
