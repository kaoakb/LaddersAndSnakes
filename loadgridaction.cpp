#include "loadgridaction.h"
#include"Action.h"
#include"Grid.h"
#include"fstream"
loadgridaction::loadgridaction(ApplicationManager* pApp):Action(pApp)
{
}

void loadgridaction::ReadActionParameters()
{
	Grid* pGrid = pManager->GetGrid();
	Input* pIn = pManager->GetGrid()->GetInput();
	Output* pO = pManager->GetGrid()->GetOutput();
	pO->PrintMessage("enter file name to load from: ");
	file = pIn->GetSrting(pO) + ".txt";
}

void loadgridaction::Execute()
{
	// i call here function loadall to save every thing 
	// i call here there time once to ladder and snake and all card
	ReadActionParameters();
		ifstream infile;
	infile.open(file, ios::in);
	//type =0 is ladder
	//type =1 is snake
	//type =2 is card
	if (infile.is_open())
	{
		pManager->GetGrid()->LoadAll(infile, 0, file);
		pManager->GetGrid()->LoadAll(infile, 1, file);
		pManager->GetGrid()->LoadAll(infile, 2, file);
		infile.close();
		Grid* pGrid = pManager->GetGrid();
		Input* pIn = pGrid->GetInput();
		Output* pO = pGrid->GetOutput();
		pO->PrintMessage("load finish");
		pIn->GetCellClicked();
		pO->ClearStatusBar();
	}
	else
		pManager->GetGrid()->PrintErrorMessage("Error to load file");
}

loadgridaction::~loadgridaction()
{
}
