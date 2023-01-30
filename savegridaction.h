#pragma once
#include "Action.h"
class savegridaction :
    public Action
{
	string file;

public:
	savegridaction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~savegridaction();
};

