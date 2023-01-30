#include "PasteCard.h"
#include"Grid.h"
#include "Card.h"
#include "Cell.h"
PasteCard::PasteCard(ApplicationManager* pApp) : Action(pApp) // A Constructor
{

}

void PasteCard::ReadActionParameters() // Reads AddCardAction action parameters ( cardPosition)
{
	/*to read the cellposition to paste in it and check if its valid*/
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut->PrintMessage("click on the destination cell");
	cardcell = pIn->GetCellClicked();
	if (!cardcell.IsValidCell())
	{
		pOut->PrintMessage("the clicked card cell is invalid");
		return;
	}
	pOut->ClearStatusBar();
}

void PasteCard::Execute()
{
	ReadActionParameters();
	Grid* pGrid = pManager->GetGrid();
	if (pGrid->CellHasObject(cardcell))//if the cell doest contain an object it will return false
	{//the card cant be pasted if the cell already contain another object
		pGrid->PrintErrorMessage("Error: the card cant be added ! Click TO Continue");

		return;
	}
	if ((cardcell.GetCellNum() < 99 && cardcell.GetCellNum() > 1))// to check if the card cell is not cell 1 or 99
	{

		
			Card* pcard = pGrid->GetClipboard();
			if (!pcard)
			{
				pGrid->PrintErrorMessage("Error: the cell already include a card and the paste command in ignored! Click TO Continue");
					return;
			}
			pcard->SetPosition(cardcell);
		bool addded=pGrid->AddObjectToCell(pcard);
		if (!addded)
		{
			
			pGrid->PrintErrorMessage("Error: the card cant be added ! Click TO Continue");
			
			return;
		}
		

	}
	else
	{
		pGrid->PrintErrorMessage("Error:the starting and the ending cell cant include cards! Click TO Continue");
	}
	/*
	* the function check if the cell has an object or is the start or the end cell if yes it terminates 
	* if no it add the cell position to the card to be drawn and adds it to the celllist usign addogjectto cell
	*/
}

PasteCard:: ~PasteCard()
{

}