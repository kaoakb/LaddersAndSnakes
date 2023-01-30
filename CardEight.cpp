#include "CardEight.h"

CardEight::CardEight(const CellPosition& pos) :Card(pos) // set the cell position of the card
{
	cardNumber = 8;  // set the inherited cardNumber data member with the card number (8 here)
}

int CardEight::GetOutCoins = 0;

void CardEight::ReadCardParameters(Grid* pGrid)
{
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();

	pOut->PrintMessage("New Card Eight: Enter the amount of coins to get out from the prison"); // Printing to a descriptive message to the user
	GetOutCoins = pIn->GetInteger(pOut);
	pOut->ClearStatusBar();  //Clearing status bar
}

void CardEight::Apply(Grid* pGrid, Player* pPlayer)
{
	int choice;
	Card::Apply(pGrid, pPlayer);  //Call Apply() of the base class Card to print the message that you reached this card number
	Input* pIn = pGrid->GetInput();
	Output* pOut = pGrid->GetOutput();
	pPlayer = pGrid->GetCurrentPlayer();
	pOut->PrintMessage("If you want to stay in prison press 0, if you want to pay coins to get out press 1"); //Making the player choose between staying in prison or pay from his wallet
	choice = pIn->GetInteger(pOut);

	if (choice == 1) //The player want to pay and get out from prison
	{
		if (pPlayer->GetWallet() > GetOutCoins) //Checking if the player has enough money in his wallet
		{
			pPlayer->SetWallet(pPlayer->GetWallet() - GetOutCoins); //The player has enough money
			return;
		}
		else //The player doesn't have enough money
		{
			pOut->PrintMessage("You don't have enough money to get out from prison");
		}
	}
	pOut->PrintMessage("You will stay in prison for 3 turns"); //The player will stay in prison by choice or because he doesn't have enough money
	pPlayer->setgame(3); //Preventing the player from playing 3 turns
}

void CardEight::Save(ofstream& OutFile, int type, string file)
{
	if (type == 2)
	{
		OutFile << cardNumber << "  " << position.GetCellNum() << "  " << endl;

	}
	else
		return;
}

void CardEight::Load(ifstream& infile, int type, string file)
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

CardEight::~CardEight()
{
}

