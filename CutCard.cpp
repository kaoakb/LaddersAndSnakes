#include "CutCard.h"
#include"Grid.h"
CutCard::CutCard(ApplicationManager* pApp) : Action(pApp) // A Constructor
{

}

void CutCard::ReadActionParameters() // Reads AddCardAction action parameters (cardPosition) It sets the cardcell with the clicked cell by the user
{
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("click on the cell");
	cardcell = pIn->GetCellClicked();
	if (!cardcell.IsValidCell())
	{
		pOut->PrintMessage("the clicked card cell is invalid");
		return;
	}
	pOut->ClearStatusBar();
}

void CutCard::Execute() //Sets the clipboard with the clicked cell after checking that this cell contains a card and earse the card from this cell
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (pGrid->GetCard(cardcell) != NULL)
	{
		pGrid->SetClipboard(pGrid->GetCard(cardcell));
		pGrid->RemoveObjectFromCell(cardcell);
	}

	else
		pGrid->PrintErrorMessage("the selected cell has no card object");

}

CutCard:: ~CutCard()
{

}