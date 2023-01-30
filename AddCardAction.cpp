#include "AddCardAction.h"
#include "Input.h"
#include "Output.h"
#include "CardOne.h"
#include "CardEleven.h"
#include "CardTen.h"
#include "CardFive.h"
#include "CardFour.h"
#include "CardNine.h"
#include"CardTen.h"
#include "CardThree.h"
#include "CardTwo.h"
#include "CardSeven.h"
#include "CardEight.h"
#include "CardSix.h"
#include "CardTwelve.h"
AddCardAction::AddCardAction(ApplicationManager* pApp) : Action(pApp)
{
	cardNumber = 0;// Initializes the pManager pointer of Action with the passed pointer
}

AddCardAction::~AddCardAction()
{
}

void AddCardAction::ReadActionParameters()
{

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below

	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Get a Pointer to the Input / Output Interfaces
	pOut->PrintMessage("New Card:Enter the Card Number");
	int number = pIn->GetInteger(pOut);
	if (number > 12 || number < 1)
	{
		pGrid->PrintErrorMessage("Error: The Entered Card Number is Invalid");
		return;
	}
	else
		cardNumber = number;
	pOut->PrintMessage("New Card: Click on Card Cell");
	cardPosition = pIn->GetCellClicked();
	if (cardPosition.IsValidCell() == false)
	{
		pGrid->PrintErrorMessage(" Error: the Clicked  Cell is Invalid");
		return;
	}

	// 2- Read the "cardNumber" parameter and set its data member

	// 3- Read the "cardPosition" parameter (its cell position) and set its data member

	// 4- Make the needed validations on the read parameters

	// 5- Clear status bar
	pOut->ClearStatusBar();
}

void AddCardAction::Execute()
{


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==
	ReadActionParameters();
	// 1- The first line of any Action Execution is to read its parameter first
	Grid* pGrid = pManager->GetGrid();
	Output* pOut = pGrid->GetOutput();
	// 2- Switch case on cardNumber data member and create the appropriate card object type
	Card* pCard = NULL; // will point to the card object type
	if (cardPosition.GetCellNum() == 1 || cardPosition.GetCellNum() == 99)// cards cant be added to the begining cell nor the winning cell
	{
		cardPosition.SetHCell(-1);
		cardPosition.SetVCell(-1);
		pGrid->PrintErrorMessage("ERROR:the cards cant be drawn in cell 1 nor cell 99");
		return;
	}
	switch (cardNumber)
	{
	case 1:
		pCard = new CardOne(cardPosition);
		break;
	case 2:
		pCard = new CardTwo(cardPosition);
		break;
	case 3:
		pCard = new CardThree(cardPosition);
		break;
	case 4:
		pCard = new CardFour(cardPosition);
		break;
	case 5:
		pCard = new CardFive(cardPosition);
		break;
	case 6:
		pCard = new CardSix(cardPosition);
		break;
	case 7:
		pCard = new CardSeven(cardPosition);
		break;

	case 8:
		pCard = new CardEight(cardPosition);
		break;
	case 9:
		pCard = new CardNine(cardPosition);
		break;
	case 10:
		pCard = new CardTen(cardPosition);
		break;
	case 11:
		pCard = new CardEleven(cardPosition);
		break;
	case 12:
		pCard = new CardTwelve(cardPosition);
		break;


		// A- Add the remaining cases

	}

	// 3- if pCard is correctly set in the switch case (i.e. if pCard is pointing to an object -- NOT NULL)
	if (pCard)
	{


		// A- We get a pointer to the Grid from the ApplicationManager

		pCard->ReadCardParameters(pGrid);

		// B- Make the "pCard" reads its card parameters: ReadCardParameters(), It is virtual and depends on the card type

		// C- Add the card object to the GameObject of its Cell:
		bool ifnadd = pGrid->AddObjectToCell(pCard);



		if (ifnadd == false)//if the card cant be added to a cell it means it contain the start cell of other object
		{
			cardPosition.SetVCell(-1);
			cardPosition.SetHCell(-1);
			pGrid->PrintErrorMessage("Error: the Cell contains another Object");

		}


		// D- if the GameObject cannot be added in the Cell, Print the appropriate error message on statusbar
		pOut->ClearStatusBar();
	}

	// Here, the card is created and added to the GameObject of its Cell, so we finished executing the AddCardAction

}
