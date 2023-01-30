#include "AddLadderAction.h"

#include "Input.h"
#include "Output.h"
#include "Ladder.h"

AddLadderAction::AddLadderAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddLadderAction::~AddLadderAction()
{
}

void AddLadderAction::ReadActionParameters()
{

	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Ladder: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	if (startPos.IsValidCell() == false)//check if the clicked cell is valid
	{
		pGrid->PrintErrorMessage("Error: The Clicked Start Cell is Invalid! Click to continue ...");
		return;
	}

	// Read the endPos parameter
	pOut->PrintMessage("New Ladder: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	if (endPos.IsValidCell() == false)//check if the clicked cell is valid
	{
		pGrid->PrintErrorMessage("Error: The Clicked End Cell is Invalid! Click to continue ...");
		return;
	}

	///TODO: Make the needed validations on the read parameters
	if (startPos.GetCellNumFromPosition(startPos) >= endPos.GetCellNumFromPosition(endPos)) //check that start cell is under the end cell
	{
		pGrid->PrintErrorMessage("Error:the start cell can not be above end cell! Click to continue ...");
		return;
	}

	if (startPos.VCell() == 0)//the start cell of a ladder cant be in the first row
	{
		pGrid->PrintErrorMessage("Error:the start cell can not be in the Last Row! Click to continue ...");
		return;
	}
	if (startPos.HCell() != endPos.HCell())//the ladder must be vertical
	{
		pGrid->PrintErrorMessage("Error:the ladder cells must be in the same coulomn! Click to continue ...");
		return;
	}


	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddLadderAction::Execute()
{
	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();

	// Create a Ladder object with the parameters read from the user
	Ladder* pLadder = new Ladder(startPos, endPos);

	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager
	if (startPos.GetCellNum() == 1)// cell one cant contain an object 
	{
		startPos.SetHCell(-1);
		startPos.SetVCell(-1);
		endPos.SetHCell(-1);
		endPos.SetVCell(-1);
		pGrid->PrintErrorMessage("Error:the start cell of a ladder cant be the begining cell 1! Click to continue ...");
		return;
	}
	/* it check if the ladder is overlapping with other ladder
	if is its end cell is the start cell of other ladder or snake*/
	if (pGrid->overlapping(pLadder) || pGrid->getcellsnakeorladder(endPos) || pGrid->getcellobject(startPos))
	{//if new ladder is overlapping it will set the cellposition to -1 to prevent it from drawing 
		startPos.SetHCell(-1);
		startPos.SetVCell(-1);
		endPos.SetHCell(-1);
		endPos.SetVCell(-1);
		pGrid->PrintErrorMessage("Error: The ladder should not be overlapped with other ladder or snake! Click to continue ...");
		return;
	}
	// Add the  object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pLadder);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
