#include "inputDiceValueAction.h"
#include"Grid.h"
#include"Player.h"
inputDiceValueAction::inputDiceValueAction(ApplicationManager* pApp):Action(pApp)
{

}

void inputDiceValueAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	if (pGrid->GetEndGame())
	{
		pout->PrintMessage("game finish");
		pin->GetCellClicked();
		return ;
	}
	pout->PrintMessage("please enter a dice value between 1-6");
	dicenum = pin->GetInteger(pout);
	pout->ClearStatusBar();

}

void inputDiceValueAction::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (pGrid->GetEndGame())
	{
		return;
	}

	if (dicenum>0&&dicenum<=6)
	{

		//check player reach to cell greater than 99  

		Player* play = pGrid->GetCurrentPlayer();
		Input* pin = pGrid->GetInput();
		Output* pout = pGrid->GetOutput();
		if (play->GetStepCount() + dicenum > 99)
		{
			if (play->GetTurnCount() == 3)
			{
				play->SetWallet(play->GetWallet() + 10 * dicenum);
			}
			play->incresetuncount();
			pout->PrintMessage("you must be exactly Click to continue ...");
			pin->GetCellClicked();
			pout->ClearStatusBar();
			pGrid->AdvanceCurrentPlayer();
			return;
		}
		Player* pl = pGrid->GetCurrentPlayer();
		pl->Move(pGrid, dicenum);
		pGrid->AdvanceCurrentPlayer();
	}
	else
	{
		pGrid->PrintErrorMessage("Invalid dice number, operation cancelled");
		return;
	}


}

inputDiceValueAction::~inputDiceValueAction()
{
}
