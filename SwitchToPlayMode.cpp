#include "SwitchToPlayMode.h"
#include "Input.h"
#include "Output.h"
#include "Grid.h"
#include "Player.h"
SwitchToPlayMode::SwitchToPlayMode(ApplicationManager* pApp) :Action(pApp)
{
	// The constructor initializes the ApplicationManager pointer data member
}

SwitchToPlayMode::~SwitchToPlayMode()
{
}

void SwitchToPlayMode::ReadActionParameters() // Reads parameters required for action to execute 
{
	/*
	there are no parameters to read
	*/

}

void SwitchToPlayMode::Execute()
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		Player* player = pGrid->GetCurrentPlayer();
		player->SetWallet(100);
		player->setturncount(0);
		pGrid->AdvanceCurrentPlayer();

	}
	pGrid->SetCurrentplayer(0);
	pOut->CreatePlayModeToolBar();
	/*
	when switching to playmood the toolbar is updated and the wallet of each player is set 100 and the count of their turns to 0
	*/
}