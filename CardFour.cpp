#include "CardFour.h"

CardFour::CardFour(const CellPosition& pos) :Card(pos)  // set the cell position of the card
{
	cardNumber = 4;  // set the inherited cardNumber data member with the card number (4 here)

}

void CardFour::ReadCardParameters(Grid* pGrid)
{
	/*
		This card's class has no data members
		so we don't need any input from the user
	*/
}

void CardFour::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);  //Calling Apply() of the base class Card to print a message that you reached this card number
	pPlayer = pGrid->GetCurrentPlayer();
	pPlayer->setgame(1); //preventing the player from playing for one turn 
}

void CardFour::Save(ofstream& OutFile, int type, string file)
{
	if (type == 2)
	{
		OutFile << cardNumber << "  " << position.GetCellNum() << "  " << endl;

	}
	else
		return;
}

void CardFour::Load(ifstream& infile, int type, string file)
{
	if (type == 2)
	{
		int cellnum;
		infile >> cellnum;
		position = CellPosition::GetCellPositionFromNum(cellnum);

	}
	else
		return;
}

CardFour::~CardFour()
{
}
