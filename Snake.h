#pragma once

#include "GameObject.h"

class Snake : public GameObject // inherited from GameObject
{
	

	CellPosition endCellPos; // snake end cell

public:

	Snake(const CellPosition& startCellPos, const CellPosition& endCellPos); // A constructor for initialization

	virtual bool IsOverlapping(GameObject* obj);
		virtual bool GetCellObject(CellPosition cposition);


	virtual void Draw(Output* pOut) const; // Draws a snake from its start cell to its end cell

	virtual void Apply(Grid* pGrid, Player* pPlayer); // Applys the effect of the snake by moving player to snake's end cell

	CellPosition GetEndPosition() const; // A getter for the endCellPos data member
	 void Save(ofstream& OutFile, int type, string file);
	 void Load(ifstream& Infile, int type, string file);
	virtual ~Snake(); // Virtual destructor
};
