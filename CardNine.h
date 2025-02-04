#pragma once
#include "Player.h"
#include "Card.h"

// [ CardOne ] Summary:
// Its Apply() Function: Decrements the value of the passing player�s wallet by a value
// Its Parameters: The Wallet Value to decrease --> put it as a "data member" and read it in ReadCardParameters()

class CardNine : public Card
{
	// CardOne Parameters:
	static int cardprice;
	static int fees;
	 static bool counter;
	 static bool first;

public:
	static Player* Pplayer1;
	CardNine(const CellPosition& pos); // A Constructor takes card position
	static int getcardprice();
	static void setowner(Player* player);
	static Player* getowner();
	virtual void ReadCardParameters(Grid* pGrid); // Reads the parameters of CardOne which is: walletAmount

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applies the effect of CardOne on the passed Player
													  // by decrementing the player's wallet by the walletAmount data member
	void Save(ofstream& OutFile, int type, string file);
	void Load(ifstream& infile, int type, string file);
	virtual ~CardNine(); // A Virtual Destructor
};