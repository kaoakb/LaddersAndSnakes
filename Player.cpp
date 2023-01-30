#include "Player.h"
#include "GameObject.h"
#include"Grid.h"
#include"Output.h"
#include"Input.h"
Player::Player(Cell* pCell, int playerNum) : stepCount(0), wallet(100), playerNum(playerNum)
{
	fired = poisoned = iced = lighninged = true;
	this->pCell = pCell;
	this->turnCount = 0;
	justRolledDiceNum = 0;
	game = 0;
	Poison = 0;
	attackcount = 0;
	// Make all the needed initialization or validations
}

// ====== Setters and Getters ======

void Player::SetCell(Cell* cell)
{
	pCell = cell;
}

Cell* Player::GetCell() const
{
	return pCell;
}

void Player::SetWallet(int wallet)
{
	if (wallet > 0)
		this->wallet = wallet;
	else
		this->wallet = 0;
	// Make any needed validations
}

int Player::GetWallet() const
{
	return wallet;
}

int Player::GetTurnCount() const
{
	return turnCount;
}

void Player::setturncount(int a)
{
	turnCount = a;
}
void Player::setgame(int a)
{
	game = a;
}

int Player::getjustRolledDiceNum()
{
	return justRolledDiceNum;
}

int Player::GetStepCount() const
{
	return stepCount;
}

int Player::getgame() const
{
	return game;
}
void Player::incresetuncount()
{
	if (turnCount == 0)
	{
		turnCount = 1;
	}
	else if (turnCount == 1)
	{
		turnCount = 2;
	}
	else if (turnCount == 2)
	{
		turnCount = 0;
	}

}

void Player::SetPoison(int p)
{
	Poison = p;
}

void Player::SetFire(int f)
{
	fire = f;
}

// ====== Drawing Functions ======

void Player::Draw(Output* pOut) const
{
	color playerColor = UI.PlayerColors[playerNum];
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, playerColor);

	///TODO: use the appropriate output function to draw the player with "playerColor"

}

void Player::ClearDrawing(Output* pOut) const
{
	color cellColor = pCell->HasCard() ? UI.CellColor_HasCard : UI.CellColor_NoCard;
	pOut->DrawPlayer(pCell->GetCellPosition(), playerNum, cellColor);


	///TODO: use the appropriate output function to draw the player with "cellColor" (to clear it)

}

// ====== Game Functions ======
void Player::lightning(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	if (lighninged)
	{
		Player* player1 = pGrid->GetCurrentPlayer();
		for (int i = 0; i < 4; i++)
		{
			pGrid->AdvanceCurrentPlayer();
			if (player1 != pGrid->GetCurrentPlayer())
			{
				Player* player = pGrid->GetCurrentPlayer();
				player->SetWallet(player->GetWallet() - 20);
				lighninged = false;
				attackcount++;
			}
		}

	}
	else
		pOut->PrintMessage("You can't use the same attack twice");
}
void Player::Poisoned(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (poisoned)
	{
		pOut->PrintMessage("please enter number form 0 to 3 which represents the player number ");
		int player = pIn->GetInteger(pOut);
		if (player >= 0 && player <= 3)
			pGrid->ispoisoned(player);
		poisoned = false;
		attackcount++;
	}
	else
		pOut->PrintMessage("You can't use the same attack twice");
}
void Player::Fired(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if(fired)
	{
		pOut->PrintMessage("please enter number form 0 to 3 which represents the player number ");
		int player = pIn->GetInteger(pOut);
		if (player >= 0 && player <= 3)
		{
			pGrid->isfired(player);
		}
		fired = false;
		attackcount++;
	}
	else
		pOut->PrintMessage("You can't use the same attack twice");
}

// ====== Game Functions ======
void Player::ice(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (iced)
	{
		pOut->PrintMessage("please enter number form 0 to 3 which represents the player number ");
		int player = pIn->GetInteger(pOut);
		if (player >= 0 && player <= 3)
		{
			pGrid->isiced(player);
		}
		iced = false;
		attackcount++;
	}
	else
		pOut->PrintMessage("You can't use the same attack twice");
}
void Player::Move(Grid* pGrid, int diceNumber)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	if (Poison>0)
	{
		diceNumber--;
		Poison--;
	}

	if (fire > 0)
	{
		wallet -= 20;
		fire--;
	}
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==
	// 1- Increment the turnCount because calling Move() means that the player has rolled the dice once
	turnCount++;
	// 2- Check the turnCount to know if the wallet recharge turn comes (recharge wallet instead of move)
	//    If yes, recharge wallet and reset the turnCount and return from the function (do NOT move)
	if (turnCount == 3)
	{
		pOut->PrintMessage("do you like to use special attack if yes please enter 1");
		int reply = pIn->GetInteger(pOut);
		if (reply == 1)
		{

			if (attackcount < 2)
			{
				SpecialAttacks(pGrid);
				turnCount = 0;
				return;
			}
			else
			{
				pGrid->PrintErrorMessage("You have used all your special attacks this game");
			}

		}

			wallet += 10 * diceNumber;
			turnCount = 0;
			return;
	}
	if (wallet == 0)
		return;
	// 3- Set the justRolledDiceNum with the passed diceNumber
	Player* player = pGrid->GetCurrentPlayer();
	int x = player->getgame();
	if (x > 0)
	{
		pGrid->PrintErrorMessage("You have been prevented from rolling the dice this turn");
		--game;
		if (turnCount == 3)
		{
			turnCount = 0;
		}
		return;
	}
	justRolledDiceNum = diceNumber;
	// 4- Get the player current cell position, say "pos", and add to it the diceNumber (update the position)
	//    Using the appropriate function of CellPosition class to update "pos"
	CellPosition pos = pCell->GetCellPosition();
	pos.AddCellNum(diceNumber);
	// 5- Use pGrid->UpdatePlayerCell() func to Update player's cell POINTER (pCell) with the cell in the passed position, "pos" (the updated one)
	//    the importance of this function is that it Updates the pCell pointer of the player and Draws it in the new position
	pGrid->UpdatePlayerCell(player, pos);
	// 6- Apply() the game object of the reached cell (if any)
	GameObject* game = pCell->GetGameObject();
	if (game != NULL)
	{
		game->Apply(pGrid, this);
	}
	// 7- Check if the player reached the end cell of the whole game, and if yes, Set end game with true: pGrid->SetEndGame(true)

	stepCount = pCell->GetCellPosition().GetCellNum();
	Input* pin = pGrid->GetInput();
	Output* pout = pGrid->GetOutput();
	if(stepCount==99)
	{
		pout->PrintMessage("you are the winner");
		pin->GetCellClicked();
		pout->ClearStatusBar();
		pGrid->SetEndGame(true);
	}
	
}

void Player::AppendPlayerInfo(string& playersInfo) const
{
	playersInfo += "P" + to_string(playerNum) + "(";
	playersInfo += to_string(wallet) + ", ";
	playersInfo += to_string(turnCount) + ")";
}

void Player::SpecialAttacks(Grid* pGrid)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();
	pOut = pGrid->GetOutput();
	pIn = pGrid->GetInput();
	pOut->PrintMessage("please chose one of the attacts ice[0], fire[1],prison[2], lightning[3]");
	int answer = pIn->GetInteger(pOut);
	switch (answer)
	{
	case 0:
	{
		ice(pGrid);
		break;
	}
	case 1:
	{
		Fired(pGrid);
		break;
	}
	case 2:
	{
		Poisoned(pGrid);
		break;
	}
	case 3:
	{
		lightning(pGrid);
		break;
	}
	}
}
