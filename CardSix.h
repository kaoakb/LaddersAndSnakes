#pragma once
#include "Card.h"

/* [ CardSix ] Summary:
Its Apply() Function: Move the player to the cell he choosed in design mode
Its Parameters: Cell to move to -> Read by  ReadCardParameters()
*/

class CardSix : public Card
{
	CellPosition tocell;
public:
	CardSix(const CellPosition& pos);
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	void Save(ofstream& OutFile, int type, string file);
	void Load(ifstream& infile, int type, string file);
	virtual ~CardSix();
};

