#pragma once
#include"Action.h"
#include"Player.h"
#include"Grid.h"
class NewGameAction :
    public Action
{public:
	NewGameAction(ApplicationManager* pApp);

	 void ReadActionParameters();

	 void Execute();

	 ~NewGameAction();

};

