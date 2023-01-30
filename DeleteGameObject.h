#pragma once

#include "Action.h"
class DeleteGameObject : public Action
{


	//ApplicationManager* pManager;	// Actions needs ApplicationManager to do their job
	CellPosition deletecell;
public:

	DeleteGameObject(ApplicationManager* pApp);  // Constructor

	// ============ Virtual Functions ============

	virtual void ReadActionParameters() ; // Reads parameters required for action to execute 
											 // (code depends on action type so virtual)

	virtual void Execute() ;  // Executes action (code depends on action type so virtual)

	virtual ~DeleteGameObject();  // Virtual Destructor
};
