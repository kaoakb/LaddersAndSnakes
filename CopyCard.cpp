#include "CopyCard.h"
#include"Grid.h"

CopyCard::CopyCard(ApplicationManager* pApp) : Action(pApp) // A Constructor
{

}
void CopyCard::ReadActionParameters() // Reads AddCardAction action parameters (cardPosition) It sets the cardcell with the clicked cell by the user
{                                   
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("click on the cell");
	cardcell=pIn->GetCellClicked(); //Choosing the cell
	if(!cardcell.IsValidCell()) //Check if the cell is valid?
	{
		pOut->PrintMessage("the clicked card cell is invalid");
		return;
	}
	pOut->ClearStatusBar();
 }
void CopyCard::Execute() //Sets the clipboard with the clicked cell after checking that this cell contains a card
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (pGrid->GetCard(cardcell) != NULL)
		pGrid->SetClipboard(pGrid->GetCard(cardcell));
	else
		pGrid->PrintErrorMessage("the selected cell has no card object");

 }

CopyCard:: ~CopyCard()
{

}