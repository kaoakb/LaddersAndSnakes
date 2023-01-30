#include "Card.h"


Card::Card(const CellPosition & pos) : GameObject(pos) // sets the cell position of the GameObject
{
}

bool Card::getpriceandfees(int& price, int& feesnumber, int cardnum, bool count, Grid* pGrid) //Gets the price and fees from the user 
                                                                                              //and set them with price and fees of the card if the are valid
{
	if (cardnum >= 9 || cardnum <= 11)
	{

		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();
		if (count)
		{
			string message = "New Card:please enter card " + to_string(cardnum) + "price";
			pOut->PrintMessage(message);

			price = pIn->GetInteger(pOut);
			if (price <= 0)
			{
				pGrid->PrintErrorMessage("Error:the enetered price is invalid ");
				price = 0;
				return false;
			}
			else
			{
				message = "New Card:please enter card " + to_string(cardnum) + " fees";
				pOut->PrintMessage(message);


				feesnumber = pIn->GetInteger(pOut);
				if (feesnumber <= 0)
				{
					pGrid->PrintErrorMessage("Error: the enetered price is invalid please enter a positive price");
					feesnumber = 0;
					return false;
				}
				else
				{
					return true;
				}
			}
		}
		pOut->ClearStatusBar();
	}
}
void Card::SetCardNumber(int cnum)
{
	cardNumber = (cnum > 0 && cnum < 13 ? cnum : 0); // needs validation
}

int Card::GetCardNumber()
{
	return cardNumber;
}

void Card::apply9to11(Grid* pGrid, Player* pPlayer, Player*& Pplayer1, int cardprice, int fees) //Check if the card is owned, if it's owned by another player it decrease the fees from the wallet
                                                                                                //If the player is the owner it does nothing
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	Card::Apply(pGrid, pPlayer); //Calling Apply() of the base class Card to print a message that you reached this card number
	ReadCardParameters(pGrid);
	if (Pplayer1 == NULL)
	{
		if (pPlayer->GetWallet() < cardprice)
		{
			pOut->PrintMessage("you dont hane enough money to buy the station");
			return;

		}
		if (pPlayer->GetWallet() >= cardprice)
		{
			pOut->PrintMessage("do you want to buy the station if yes please enter 1 if no please enter 0");
			int  reply = pIn->GetInteger(pOut);
			if (reply == 0)
				return;
			if (reply == 1)
			{
				Pplayer1 = pPlayer;
				pPlayer->SetWallet(pPlayer->GetWallet() - cardprice);
			}
		}
	}
	if (Pplayer1 != NULL && Pplayer1 != pPlayer)
	{
		if (pPlayer->GetWallet() >= fees)
		{
			pOut->PrintMessage("you stepped on the station of another player and you have to pay fees");
			int newwallet = pPlayer->GetWallet() - fees;
			pPlayer->SetWallet(newwallet);
		}
		else
		{
			pOut->PrintMessage("your wallet doesnt contain enough money for the fee, So you will prisoned in the cell next round");
			pPlayer->setgame(false);
		}
	}
}

void Card::Draw(Output* pOut) const
{

	///TODO: call the appropriate Ouput function that draws a cell containing the "cardNumber" in "position"
	pOut->DrawCell(position, cardNumber);

}

void Card::ReadCardParameters(Grid * pGrid)
{
	// we should not make it pure virtual because some Cards doesn't have parameters
	// and if we make it pure virtual, that will make those Cards abstract classes
}

void Card::Apply(Grid* pGrid, Player* pPlayer)
{
	// As written below the "Roll Dice" action in the document ==> Check the Project Document
	// "If a player reaches a card of any other type", the following message should be printed then wait mouse click

	pGrid->PrintErrorMessage("You have reached card " + to_string(cardNumber) + ". Click to continue ...");
}

void Card::Save(ofstream& OutFile, int type, string file)
{
}

void Card::Load(ifstream& Infile, int type, string file)
{
}



Card::~Card()
{
}


