#include "CardSeven.h"

CardSeven::CardSeven(const CellPosition& pos) :Card(pos) // set the cell position of the card
{
	cardNumber = 7;  // set the inherited cardNumber data member with the card number (7 here)
}

void CardSeven::ReadCardParameters(Grid* pGrid)
{
	/*
		This card's class has no data members
		so we don't need any input from the user
	*/
}

void CardSeven::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer);
	Output* pOut = pGrid->GetOutput();
	pPlayer = pGrid->GetCurrentPlayer();
	Player* NextPlayer = pGrid->GetNextPlayer(pPlayer); //Getting a pointer to the next player in the grid
	if (NextPlayer) //A player found a head
	{
		CellPosition ncell(1);
		pGrid->UpdatePlayerCell(NextPlayer, ncell);  //Restarting the game for next player
	}
	else //No players are next in the grid
	{
		pOut->PrintMessage("No Players found ahead");
		pOut->ClearStatusBar();
	}
}


void CardSeven::Save(ofstream& OutFile, int type, string file)
{
	if (type == 2)
	{
		OutFile << cardNumber << "  " << position.GetCellNum() << "  " << endl;

	}
	else
		return;
}

void CardSeven::Load(ifstream& infile, int type, string file)
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

CardSeven::~CardSeven()
{
}
