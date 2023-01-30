#pragma once
#include "Card.h"

/* [ CardSeven ] Summary:
Its Apply() Function: Call the function GetNextPlayer in grid class to get the player next in the grid then sets his cellnum to 1 (Restart the game for him)
					  but if no player found it do nothing
Its Parameters: It has no parameters/data members
*/

class CardSeven : public Card
{

public:
	CardSeven(const CellPosition& pos);
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	void Save(ofstream& OutFile, int type, string file);
	void Load(ifstream& infile, int type, string file);
	virtual ~CardSeven();

};