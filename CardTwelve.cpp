#include "CardTwelve.h"

CardTwelve::CardTwelve(const CellPosition& pos):Card(pos)  // set the cell position of the card
{
	cardNumber = 12;  // set the inherited cardNumber data
}

void CardTwelve::ReadCardParameters(Grid* pGrid)
{
	/*
		This card's class has no data members
		so we don't need any input from the user
	*/
}

void CardTwelve::Apply(Grid* pGrid, Player* pPlayer)
{
	Card::Apply(pGrid, pPlayer); //Calling Apply() of the base class Card to print a message that you reached this card number
	pPlayer=pGrid->GetCurrentPlayer();
	int MostExpensiveStation=-1;
	int y = 0;
	if (CardNine::getowner() == pPlayer) //Check if the player owns card nine
	{
		MostExpensiveStation = CardNine::getcardprice();
	}
	if (CardTen::getowner() == pPlayer)  //Check if the player owns card ten
	{
		if (MostExpensiveStation < CardTen::getcardprice())
		{
			MostExpensiveStation = CardTen::getcardprice();
			y = 1;
		}
	}
	if (CardEleven::getowner() == pPlayer)  //Check if the player owns card eleven
	{
		if (MostExpensiveStation < CardEleven::getcardprice())
		{
			MostExpensiveStation = CardEleven::getcardprice();
			y = 2;
		}
	}
	if (MostExpensiveStation == -1)
	{
		pGrid->PrintErrorMessage("The Player doesn't own any station");
		return;
	}
	switch (y)
	{
		case 0: //The most expensive station is card nine
		{
			CardNine::setowner(pGrid->GetLeastWallet());
			break;
		}
		case 1: //The most expensive station is card ten
		{
			CardTen::setowner(pGrid->GetLeastWallet());
			break;
		}
		case 2: //The most expensive station is card eleven
		{
			CardEleven::setowner(pGrid->GetLeastWallet());
			break;
		}

	}
}

void CardTwelve::Save(ofstream& OutFile, int type, string file)
{
	if (type == 2)
	{
		OutFile << cardNumber << "  " << position.GetCellNum() << "  " << endl;

	}
	else
		return;
}

void CardTwelve::Load(ifstream& infile, int type, string file)
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

CardTwelve::~CardTwelve()
{
}
