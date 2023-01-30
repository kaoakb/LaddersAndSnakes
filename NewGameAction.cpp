#include "NewGameAction.h"
#include"Action.h"
#include"Player.h"
#include"Grid.h"
#include"CardEleven.h"
#include"CardNine.h"
#include"CardTen.h"
#include"DeleteGameObject.h"
#include"Player.h"
#include"Grid.h"
#include"Cell.h"
NewGameAction::NewGameAction(ApplicationManager* pApp):Action(pApp)
{
}

void NewGameAction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	pin->GetCellClicked();
	pout->ClearStatusBar();
}

void NewGameAction::Execute()
{
	// here i will make players owner donot have the station 
	ReadActionParameters();
	CardNine::Pplayer1 = NULL;
	CardEleven::Pplayer1 = NULL;
	CardTen::Pplayer1 = NULL; 
	// here i will make the player return to cell 1 and make turncount = 0 
	Grid* pGrid = pManager->GetGrid();
	Input* inp = pGrid->GetInput();
	Output* out = pGrid->GetOutput();
	CellPosition StartCell(1);
	for (size_t i = 0; i < MaxPlayerCount; i++)
	{
		Player *p = pGrid->GetCurrentPlayer();
		pGrid->UpdatePlayerCell(p, StartCell);
		p->setturncount(0);
		p->SetWallet(100);
		pGrid->AdvanceCurrentPlayer();

	}
	pGrid->SetCurrentplayer(0);
}

NewGameAction::~NewGameAction()
{
}
