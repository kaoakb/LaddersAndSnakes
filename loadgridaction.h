#pragma once
#include "Action.h"
class loadgridaction :
    public Action
{
	string file;

public:
	loadgridaction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	virtual ~loadgridaction();
};
