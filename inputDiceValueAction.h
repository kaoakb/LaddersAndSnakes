#pragma once
#include"Action.h"
class inputDiceValueAction :public Action
{
	int dicenum;
public:
	inputDiceValueAction(ApplicationManager* pApp);
	virtual void ReadActionParameters() ;
	virtual void Execute() ;
	virtual ~inputDiceValueAction();
};

