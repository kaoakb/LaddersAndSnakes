#pragma once
#include "Card.h"

/* [ CardEight ] Summary:
	Its Apply() Function: Ask the player if he wants to stay in prison (preventing him from playing for 3 turns)
						   or pay the GetOutCoins from his wallet to play normally but it check first if he has enough money or he will be prisoned
	Its Parameters: The amount of coins needed to go out of the prison -> Read by  ReadCardParameters()
*/

class CardEight : public Card
{
	static int GetOutCoins;

public:
	CardEight(const CellPosition& pos);
	virtual void ReadCardParameters(Grid* pGrid);
	virtual void Apply(Grid* pGrid, Player* pPlayer);
	void Save(ofstream& OutFile, int type, string file);
	void Load(ifstream& infile, int type, string file);
	virtual ~CardEight();
};

