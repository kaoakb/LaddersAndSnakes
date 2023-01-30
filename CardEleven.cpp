#include"CardEleven.h"

CardEleven::CardEleven(const CellPosition& pos) : Card(pos)
{
	cardNumber = 11;

}
int CardEleven::fees = 0;
int CardEleven::cardprice = 0;
bool CardEleven::counter = true;
Player* CardEleven::Pplayer1 = NULL;
bool CardEleven::first = true;

void CardEleven::ReadCardParameters(Grid* pGrid)
{
	if (getpriceandfees(cardprice, fees, cardNumber, counter, pGrid) && counter)
	{
		Output* pOut = pGrid->GetOutput();
		pOut->PrintMessage("the card parameters are read");
		counter = false;
	}
}
int CardEleven::getcardprice()
{
	return cardprice;
}

void CardEleven::setowner(Player* player)
{
	Pplayer1 = player;
}

Player* CardEleven::getowner()
{
	return Pplayer1;
}
void CardEleven::Apply(Grid* pGrid, Player* pPlayer)
{
	apply9to11(pGrid, pPlayer, Pplayer1, cardprice, fees);
} 
void CardEleven::Save(ofstream& OutFile, int type, string file)
{
	if (type == 2)
	{
		OutFile << cardNumber << "    " << position.GetCellNum() << "   ";
		if (!first)
		{
			OutFile << endl;

		}
		if (first)
		{
			OutFile << cardprice << "   " << fees << "    " << endl;
			first = false;
		}

	}
	else
		return;
}

void CardEleven::Load(ifstream& infile, int type, string file)
{
	if (type == 2)
	{
		int cellnum;
		infile >> cellnum >> cardprice >> fees;
		position = CellPosition::GetCellPositionFromNum(cellnum);
	}
	else
		return;
}

CardEleven::~CardEleven()
{
}

