#include "CardTwo.h"
#include"Ladder.h"

CardTwo::CardTwo(const CellPosition& pos):Card(pos)  // set the cell position of the card
{
	cardNumber = 2;  // set the inherited cardNumber data member with the card number (2 here)
}

void CardTwo::ReadCardParameters(Grid* pGrid)
{
	/*
		This card's class has no data members
		so we don't need any input from the user
	*/
}

void CardTwo::Apply(Grid* pGrid, Player* pPlayer)
{
	pPlayer = pGrid->GetCurrentPlayer();
	Ladder* pLadder= pGrid->GetNextLadder(position);   //Searching for the next ladder postion in the grid
	if (pLadder == NULL)   
	{
		Output* pOut = pGrid->GetOutput();
		pOut->PrintMessage("No ladders found ahead");
		return;   //As no ladders found ahead, so we won't change the postion of the player
	}
	else
	{
		Card::Apply(pGrid, pPlayer);  //Calling Apply() of the base class Card to print a message that you reached this card number
		CellPosition NewPos = pLadder->GetPosition();  //Setting the new postion of the player to be the postion of the next ladder
		pGrid->UpdatePlayerCell(pPlayer, NewPos); //Moving the player to the new postion (start cell of the next ladder) 

		GameObject* pGameObject = pPlayer->GetCell()->GetGameObject();  //Checking if the new cell has a game object to apply?
		if (pGameObject)
		{

			pGameObject->Apply(pGrid, pPlayer);
		}
	}

}

void CardTwo::Save(ofstream& OutFile, int type, string file)
{
	if (type == 2)
	{
		OutFile << cardNumber << "  " << position.GetCellNum() << "  " << endl;

	}
	else
		return;
}

void CardTwo::Load(ifstream& infile, int type, string file)
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

CardTwo::~CardTwo()
{
}
