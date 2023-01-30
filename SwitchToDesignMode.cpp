#include "SwitchToDesignMode.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "CardEleven.h"
#include "CardNine.h"
#include "CardTen.h"
SwitchToDesignMode::SwitchToDesignMode(ApplicationManager* pApp) :Action(pApp)
{
	// The constructor initializes the ApplicationManager pointer data member
}

SwitchToDesignMode::~SwitchToDesignMode()
{
}

void SwitchToDesignMode::ReadActionParameters() // Reads parameters required for action to execute 
{

	/*
	no parameters to read
	*/
}

void SwitchToDesignMode::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	pOut->ClearStatusBar();
	pOut->CreateDesignModeToolBar();
	CardTen::Pplayer1 = NULL;
	CardEleven::Pplayer1 = NULL;
	CardNine::Pplayer1 = NULL;

	CellPosition StartCell(1);
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		Player* player = pGrid->GetCurrentPlayer();
		pGrid->UpdatePlayerCell(player, StartCell);
		player->setturncount(0);
		pGrid->AdvanceCurrentPlayer();

	}
	/*
	when switching to design mode the owners of the stations are set to null
	as the design toolbar is created
	all the players are back to the starting cell
	*/
}