#include"CardNine.h"

CardNine::CardNine(const CellPosition& pos): Card(pos)
{ 
	cardNumber = 9;
	
}

int CardNine::fees = 0;
int CardNine::cardprice = 0;
bool CardNine::counter = true;
Player* CardNine::Pplayer1 = NULL;
bool CardNine::first = true;

void CardNine::ReadCardParameters(Grid* pGrid)
{
if (getpriceandfees(cardprice, fees, cardNumber, counter, pGrid)&&counter)
{
	Output* pOut = pGrid->GetOutput();
	pOut->PrintMessage("the card parameters are read");
	counter = false;
	}
	
}
int CardNine::getcardprice()
{
	return cardprice;
}

void CardNine::setowner(Player* player)
{
	Pplayer1 = player;
}

Player* CardNine::getowner()
{
	return Pplayer1;
}
void CardNine::Apply(Grid* pGrid, Player* pPlayer)
{
	apply9to11(pGrid, pPlayer,  Pplayer1, cardprice, fees);	
}
void CardNine::Save(ofstream& OutFile, int type, string file)
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
void CardNine::Load(ifstream& infile, int type, string file)
{
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
}
CardNine::~CardNine()
{
}

