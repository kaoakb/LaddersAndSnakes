#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Ladder.h"
#include "Card.h"
#include "Player.h"
#include"Snake.h"
#include"CardEleven.h"
#include"CardNine.h"
#include"CardTen.h"
#include "CardEight.h"
#include "CardFive.h"
#include "CardFour.h"
#include "CardNine.h"
#include "CardOne.h"
#include "CardSeven.h"
#include "CardSix.h"
#include "CardThree.h"
#include "CardTwelve.h"
#include "CardTwo.h"

Grid::Grid(Input * pIn, Output * pOut) : pIn(pIn), pOut(pOut) // Initializing pIn, pOut
{
	// Allocate the Cell Objects of the CellList
	for (int i = NumVerticalCells-1; i >= 0 ; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			CellList[i][j] = new Cell(i, j);
		}
	}

	// Allocate thePlayer Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++) 
	{
		PlayerList[i] = new Player(CellList[NumVerticalCells-1][0], i); // first cell
		PlayerList[i]->Draw(pOut); // initially draw players in the first cell
	}

	// Initialize currPlayerNumber with 0 (first player)
	currPlayerNumber = 0; // start with the first player

	// Initialize Clipboard with NULL
	Clipboard = NULL;

	// Initialize endGame with false
	endGame = false;
}


// ========= Adding or Removing GameObjects to Cells =========
bool Grid::overlapping(GameObject* pNewObject)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--) // to allocate cells from bottom up
	{
		for (int j = 0; j < NumHorizontalCells; j++) // to allocate cells from left to right
		{
			if (CellList[i][j]->GetGameObject())// to check if the cell contains an object 
			{
				GameObject* pObject = CellList[i][j]->GetGameObject();
				{
					if (pNewObject->IsOverlapping(pObject))//calls the overlapping fuction of ladder class
						return true;
				}
				
			}
		}

	}


	return false;
}
void Grid::SetCurrentplayer(int currentplayernum)
{
	if (currentplayernum <= 0 && currentplayernum < 3)
		currPlayerNumber = currentplayernum;
}
bool Grid::AddObjectToCell(GameObject * pNewObject)  // think if any validation is needed
{
	// Get the cell position of pNewObject
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell()) // Check if valid position
	{
		// Get the previous GameObject of the Cell
		GameObject * pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if( pPrevObject)  // the cell already contains a game object
			return false; // do NOT add and return false

		// Set the game object of the Cell with the new game object
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true; // indicating that addition is done
	}
	return false; // if not a valid position
}


// Note: You may need to change the return type of this function (Think)
void Grid::RemoveObjectFromCell(const CellPosition & pos)
{
	if (pos.IsValidCell()) // Check if valid position
	{
		// Note: you can deallocate the object here before setting the pointer to null if it is needed

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
	}
}

void Grid::UpdatePlayerCell(Player * player, const CellPosition & newPosition)
{
	// Clear the player's circle from the old cell position
	player->ClearDrawing(pOut);

	// Set the player's CELL with the new position
	Cell * newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);	

	// Draw the player's circle on the new cell position
	player->Draw(pOut);
}


// ========= Setters and Getters Functions =========


Input * Grid::GetInput() const
{
	return pIn;
}

Output * Grid::GetOutput() const
{
	return pOut;
}

void Grid::SetClipboard(Card * pCard) // to be used in copy/cut
{
	// you may update slightly in implementation if you want (but without breaking responsibilities)
	Clipboard = pCard;
}

Card * Grid::GetClipboard() const // to be used in paste
{
	return Clipboard;
}

void Grid::SetEndGame(bool endGame)
{
	this->endGame = endGame;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

void Grid::AdvanceCurrentPlayer()
{
	currPlayerNumber = (currPlayerNumber + 1) % MaxPlayerCount; // this generates value from 0 to MaxPlayerCount - 1
}



// ========= Other Getters =========

void Grid::isiced(int player)
{
	PlayerList[player]->setgame(1);
}

void Grid::ispoisoned(int player)
{
	PlayerList[player]->SetPoison(5);
}

void Grid::isfired(int player)
{
	PlayerList[player]->SetFire(3);
}

Player * Grid::GetCurrentPlayer() const
{
	return PlayerList[currPlayerNumber];
}

Ladder * Grid::GetNextLadder(const CellPosition & position)
{
	
	int startH = position.HCell(); // represents the start hCell in the current row to search for the ladder in
	for (int i = position.VCell(); i >= 0; i--) // searching from position.vCell and ABOVE
	{
		for (int j = startH; j < NumHorizontalCells; j++) // searching from startH and RIGHT
		{

			if (CellList[i][j]->HasLadder())
			{
				Ladder* nextladder = CellList[i][j]->HasLadder();
				return nextladder;
			}
			///TODO: Check if CellList[i][j] has a ladder, if yes return it
			

		}
		startH = 0; // because in the next above rows, we will search from the first left cell (hCell = 0) to the right
	}
	return NULL; // not found
}

Player* Grid::GetLeastWallet() const
{
	Player* LeastWallet = PlayerList[0];
	for (int i = 0;i < MaxPlayerCount;i++)
	{
		if (LeastWallet->GetWallet() > PlayerList[i]->GetWallet())
		{
			LeastWallet = PlayerList[i];
		}
	}
	return LeastWallet;
}


Player* Grid::GetNextPlayer(Player* CurrentPlayer)
{
	Player* NextPlayer = NULL;
	int SmallestDis = NumHorizontalCells * NumVerticalCells;
	for (int i = 0;i < MaxPlayerCount;i++)
	{
		if (PlayerList[i] == CurrentPlayer)
		{
			continue;
		}
		if (PlayerList[i]->GetStepCount() > CurrentPlayer->GetStepCount() && (PlayerList[i]->GetStepCount() - CurrentPlayer->GetStepCount()) <= SmallestDis)
		{
			NextPlayer = PlayerList[i];
			SmallestDis = PlayerList[i]->GetStepCount() - CurrentPlayer->GetStepCount();
		}
	}

	return NextPlayer;
}


// ========= User Interface Functions =========

void Grid::UpdateInterface() const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// 1- Draw cells with or without cards 
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawCellOrCard(pOut);
			}
		}

		// 2- Draw other cell objects (ladders, snakes)
		for (int i = NumVerticalCells-1; i >= 0 ; i--) // bottom up
		{
			for (int j = 0; j < NumHorizontalCells; j++) // left to right
			{
				CellList[i][j]->DrawLadderOrSnake(pOut);
			}
		}

		// 3- Draw players
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->Draw(pOut);
		}
	}
	else // In PLAY Mode
	{
		// 1- Print Player's Info
		string playersInfo = "";
		for (int i = 0; i < MaxPlayerCount; i++)
		{
			PlayerList[i]->AppendPlayerInfo(playersInfo); // passed by reference
			if (i < MaxPlayerCount-1) // except the last player
				playersInfo += ", ";
		}
		playersInfo += " | Curr = " + to_string(currPlayerNumber);

		pOut->PrintPlayersInfo(playersInfo);

		// Note: UpdatePlayerCell() function --> already update drawing players in Play Mode
		//       so we do NOT need draw all players again in UpdateInterface() of the Play mode
		// In addition, cards/snakes/ladders do NOT change positions in Play Mode, so need to draw them here too
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

Card* Grid::GetCard(const CellPosition& position)
{
	return CellList[position.VCell()][position.HCell()]->HasCard();
}
void Grid::SaveAll(ofstream& OutFile, int type, string file)
{
	int count = 0;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			switch (type)
			{

			case 0:	if (CellList[i][j]->HasLadder())
				count++;
				break;
			case 1: if (CellList[i][j]->HasSnake())
				count++;
				break;
			case 2: if (CellList[i][j]->HasCard())
				count++;
				break;
			}
		}
	}
	OutFile << count<<endl;
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			if (CellList[i][j]->GetGameObject())
				CellList[i][j]->GetGameObject()->Save(OutFile, type, file);
		}

	}
}
void Grid::LoadAll(ifstream& infile, int type, string file)
{
	if (type == 0)
	{
		int count;
		infile >> count;
		for (int i = 0; i < count; i++)
		{
			Ladder* pL = new Ladder(CellPosition::GetCellPositionFromNum(36), CellPosition::GetCellPositionFromNum(80));
			pL->Load(infile, type, file);
			AddObjectToCell(pL);
		}

	}
	if (type == 1)
	{
		int count;
		infile >> count;
		for (int i = 0; i < count; i++)
		{
			Snake* pS = new Snake(CellPosition::GetCellPositionFromNum(97), CellPosition::GetCellPositionFromNum(31));
			pS->Load(infile, type, file);
			AddObjectToCell(pS);
		}

	}
	if (type == 2)
	{
		int count;
		infile >> count;
		for (int i = 0; i < count; i++)
		{
			int cardNum;
			infile >> cardNum;
			Card* pCard;
			CellPosition cardPosition = CellPosition::GetCellPositionFromNum(15);
			switch (cardNum)
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
			
			}
			pCard->Load(infile, type, file);
			AddObjectToCell(pCard);
		}
	}
}
Grid::~Grid()
{
	delete pIn;
	delete pOut;

	// Deallocate the Cell Objects of the CellList
	for (int i = NumVerticalCells - 1; i >= 0; i--)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			delete CellList[i][j];
		}
	}

	// Deallocate the Player Objects of the PlayerList
	for (int i = 0; i < MaxPlayerCount; i++)
	{
		delete PlayerList[i];
	}
}
	bool Grid::getcellobject(CellPosition cposition)
	{
		int v = cposition.VCell();
		int h = cposition.HCell();
		if (CellList[v][h]->GetGameObject())
			return true;
		else 
		{
			for (int i = NumHorizontalCells; i >= 0; i--) // to search the cells from right to left
			{
				if (cposition.HCell() == i)// to get the cells in the same column as cposition(calling parameter)
				{
					for (int j = 0; j < NumVerticalCells; j++) // searching from left to right 
					{
						if (CellList[j][i]->GetGameObject())
						{
							GameObject* cellobject = CellList[j][i]->GetGameObject();
							if (cellobject->GetCellObject(cposition))
								return true;
						}
					}
				}
			}
		}
		/*the function check if the parameter cellposition has a previous object(ladder, snake, or card)
		or end cell of a ladder or snake*/
		return false;
	}
	bool Grid::CellHasObject(CellPosition cposition)
	{
		/*
		to check if the calling position cantains a ladde or a snake
		*/
		int v = cposition.VCell();
		int h = cposition.HCell();
		if (CellList[v][h]->GetGameObject())
			return true;
		return false;
	}

	bool Grid::getcellsnakeorladder(CellPosition cposition)
	{
		int v = cposition.VCell();
		int h = cposition.HCell();

		if (CellList[v][h]->HasLadder())
			return true;
		if (CellList[v][h]->HasSnake())
			return true;

		return false;
		/*to check if the caller parameter cellposition has a start cell of other snake or ladder*/
	}

