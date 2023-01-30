#include "savegridaction.h"
#include"Action.h"
#include"Grid.h"
#include<fstream>
savegridaction::savegridaction(ApplicationManager* pApp):Action(pApp)
{
}

void savegridaction::ReadActionParameters()
{	// there i will ask the user to write name the file
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pGrid->GetInput();
	Output* pO = pGrid->GetOutput();
	pO->PrintMessage("enter file name : ");
	file = pIn->GetSrting(pO) + ".txt";
}

void savegridaction::Execute()
{
	// i call here function saveall to save every thing 
	// i call here there time once to ladder and snake and all card
	ReadActionParameters();
	ofstream OutFile;
	OutFile.open(file, ios::out);
	//type =0 is ladder
	//type =1 is snake
	//type =2 is card
	if (OutFile.is_open())
	{
		pManager->GetGrid()->SaveAll(OutFile, 0, file);
		pManager->GetGrid()->SaveAll(OutFile, 1, file);
		pManager->GetGrid()->SaveAll(OutFile, 2, file);
		OutFile.close();
		Grid* pGrid = pManager->GetGrid();
		Input* pIn = pGrid->GetInput();
		Output* pO = pGrid->GetOutput();
		pO->PrintMessage("save finish");
		pIn->GetCellClicked();
		pO->ClearStatusBar();
	}
	else
	{
		pManager->GetGrid()->PrintErrorMessage("Error to save file");
		return;
	}
}


savegridaction::~savegridaction()
{
}
