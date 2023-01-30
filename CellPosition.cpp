#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition () 
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 
}

CellPosition::CellPosition (int v, int h)
{ 
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1; 
	hCell = -1; 

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition (int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
												// from the passed (cellNum)
												// (*this) = ... --> this will copy the returned (vCell and hCell)
												//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v) 
{
	if (v >= 0 && v < NumVerticalCells) ///TODO: Implement this function as described in the .h file (don't forget the validation)
	{
		vCell = v;
		return true; // this line sould be changed with your implementation
	} 
	else
	{
		vCell = -1;
			return false;
	}
}

bool CellPosition::SetHCell(int h)
{
	if (h >= 0 && h < NumHorizontalCells) ///TODO: Implement this function as described in the .h file (don't forget the validation)
	{
		hCell = h;
		return true;
	}
	else
	{
		hCell = -1;
		return false; // this line sould be changed with your implementation
	}
}

int CellPosition::VCell() const 
{
	return vCell;
}

int CellPosition::HCell() const 
{
	return hCell;
}

bool CellPosition::IsValidCell() const 
{
	if (vCell>-1 && vCell < NumVerticalCells && hCell>-1 && hCell <	NumHorizontalCells) //TODO: Implement this function as described in the .h file
		return true;
	else
	    return false; // this line sould be changed with your implementation
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
										  // which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition & cellPosition)
{
	if (cellPosition.IsValidCell())
	{
		int z;
		z = (NumVerticalCells - cellPosition.VCell() - 1) * NumHorizontalCells + cellPosition.HCell() + 1;
		return z;
	}
	else
		return -1;
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file
	 // this line should be changed with your implementation
}

CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;
	if(cellNum<1||cellNum>99)
	{ 
		position.SetVCell(-1);
		position.SetHCell(-1);

	}
	else
	{

		int vertical = (NumVerticalCells * NumHorizontalCells - cellNum) / NumHorizontalCells;
		int horizontal = cellNum - ((NumVerticalCells - vertical - 1) * NumHorizontalCells) - 1;
		position.SetVCell(vertical);
		position.SetHCell(horizontal);
	}
	/// TODO: Implement this function as described in the .h file
	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it
	return position;
}

void CellPosition::AddCellNum (int addedNum)
{
	int y=GetCellNum();
	y += addedNum;
	*this= GetCellPositionFromNum(y);
	/// TODO: Implement this function as described in the .h file



	// Note: this function updates the data members (vCell and hCell) of the calling object

}
