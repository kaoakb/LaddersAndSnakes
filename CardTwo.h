#pragma once
#include "Card.h"

/* [ CardTwo ] Summary:
	Its Apply() Function: Search for the postion of the next ladder and move the current player to it's start cell but if there is no ladder ahead it do nothing 
	Its Parameters: It has no parameters/data members 
*/
class CardTwo : public Card
{
public:
	CardTwo(const CellPosition& pos);
	virtual void CardTwo::ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	void Save(ofstream& OutFile, int type, string file);
	void Load(ifstream& infile, int type, string file);
	virtual ~CardTwo();
};
