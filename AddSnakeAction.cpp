#include "AddSnakeAction.h"

#include "Input.h"
#include "Output.h"
#include "Snake.h"

AddSnakeAction::AddSnakeAction(ApplicationManager* pApp) : Action(pApp)
{
	// Initializes the pManager pointer of Action with the passed pointer
}

AddSnakeAction::~AddSnakeAction()
{
}

void AddSnakeAction::ReadActionParameters()
{
	// Get a Pointer to the Input / Output Interfaces
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// Read the startPos parameter
	pOut->PrintMessage("New Snake: Click on its Start Cell ...");
	startPos = pIn->GetCellClicked();
	if (startPos.IsValidCell() == false)//to check if the start cell of snake is valid
	{
		pGrid->PrintErrorMessage("Error: The Clicked Start Cell is Invalid! Click to continue ...");
		return;
	}

	// Read the endPos parameter
	pOut->PrintMessage("New Snake: Click on its End Cell ...");
	endPos = pIn->GetCellClicked();

	if (endPos.IsValidCell() == false)// to check if the end cell of snake is valid
	{
		pGrid->PrintErrorMessage("Error: The Clicked End Cell is Invalid! Click to continue ...");
		return;
	}


	///TODO: Make the needed validations on the read parameters
	if (startPos.GetCellNumFromPosition(startPos) <= endPos.GetCellNumFromPosition(endPos))//the start cell of snake must be above the end cell
	{
		pGrid->PrintErrorMessage("Error:the start cell can not be under end cell! Click to continue ...");
		return;
	}

	if (startPos.VCell() == 8)//the start cell of the snake can not be in the last row
	{
		pGrid->PrintErrorMessage("Error:the start cell can not be in the First Row! Click to continue ...");
		return;
	}
	if (startPos.HCell() != startPos.HCell())//snakes must be vertical so they must have same hcell
	{
		pGrid->PrintErrorMessage("Error:the snake cells must be in the same coulomn! Click to continue ...");
		return;
	}


	// Clear messages
	pOut->ClearStatusBar();
}


// Execute the action
void AddSnakeAction::Execute()
{
	Grid* pGrid = pManager->GetGrid(); // We get a pointer to the Grid from the ApplicationManager

	// The first line of any Action Execution is to read its parameter first 
	// and hence initializes its data members
	ReadActionParameters();
	if (startPos.GetCellNum() == 99)//th e start cell of snake cant be the winning cell 99
	{
		/*if the selected start cell is 99
	 the cells of the snake is set to -1 so it wont be drawn*/
		startPos.SetHCell(-1);
		startPos.SetVCell(-1);
		endPos.SetHCell(-1);
		endPos.SetVCell(-1);
		pGrid->PrintErrorMessage("the start cell of a snake cant be the winning cell 99");
		return;
	}

	// Create a Ladder object with the parameters read from the user
	Snake* pSnake = new Snake(startPos, endPos);

	if (pGrid->overlapping(pSnake) || pGrid->getcellsnakeorladder(endPos))// snake cant overlapwith other snake or ladder
	{
		startPos.SetHCell(-1);
		startPos.SetVCell(-1);
		endPos.SetHCell(-1);
		endPos.SetVCell(-1);
		pGrid->PrintErrorMessage("Error: The ladder should not be overlapped with other ladder or snake! Click to continue ...");
		return;
	}
	if (pGrid->getcellobject(startPos) || pGrid->getcellobject(endPos))// the end cells cant be the start cell of other snake or ladder
	{
		startPos.SetHCell(-1);
		startPos.SetVCell(-1);
		endPos.SetHCell(-1);
		endPos.SetVCell(-1);
		pGrid->PrintErrorMessage("Error: The ladder should not be overlapped with other ladder or snake! Click to continue ...");
		return;

	}

	// Add the card object to the GameObject of its Cell:
	bool added = pGrid->AddObjectToCell(pSnake);

	// if the GameObject cannot be added
	if (!added)
	{
		// Print an appropriate message
		pGrid->PrintErrorMessage("Error: Cell already has an object ! Click to continue ...");
	}
	// Here, the ladder is created and added to the GameObject of its Cell, so we finished executing the AddLadderAction

}
