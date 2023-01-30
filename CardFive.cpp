#include "CardFive.h"

CardFive::CardFive(const CellPosition& pos) : Card(pos)   // set the cell position of the card
{
	cardNumber = 5;   // set the inherited cardNumber data member with the card number
}

void CardFive::ReadCardParameters(Grid* pGrid)
{
	/*
		This card's class has no data members
		so we don't need any input from the user
	*/
}

void CardFive::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);   //Calling Apply() of the base class Card to print a message that you reached this card number

	int tocell = position.GetCellNumFromPosition(position) - pPlayer->getjustRolledDiceNum();  //Calculating the new cellnumber of the player
	CellPosition topostion = position.GetCellPositionFromNum(tocell);  //getting the postion of the new cell number
	pGrid->UpdatePlayerCell(pPlayer, topostion); //moving the player to the new postion

	GameObject* pGameObject = pPlayer->GetCell()->GetGameObject();  //Checking if the new cell has a game object to apply?
	if (pGameObject)
	{
		pGameObject->Apply(pGrid, pPlayer);
	}
}

void CardFive::Save(ofstream& OutFile, int type, string file)
{
	if (type == 2)
	{
		OutFile << cardNumber << "  " << position.GetCellNum() << "  " << endl;

	}
	else
		return;
}

void CardFive::Load(ifstream& infile, int type, string file)
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

CardFive::~CardFive()
{
}
