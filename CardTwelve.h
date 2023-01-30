#pragma once
#include "Card.h"
#include "CardNine.h"
#include "CardTen.h"
#include "CardEleven.h"

/* [ CardTwelve ] Summary:
	Its Apply() Function: Get the stations that the player owns then compare between their prices
						 then set the ownership of the most expensive station to the poorest palyer
	Its Parameters: It has no parameters/data members
*/

class CardTwelve : public Card
{

public:
	CardTwelve(const CellPosition& pos);
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	void Save(ofstream& OutFile, int type, string file);
	void Load(ifstream& infile, int type, string file);
	virtual ~CardTwelve();
};

