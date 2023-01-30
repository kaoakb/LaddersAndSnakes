#include "GameObject.h"


GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position
}

CellPosition GameObject::GetPosition() const
{
	return position;
}

void GameObject::SetPosition(CellPosition p)
{
	position = p;
}

bool GameObject::IsOverlapping(GameObject* obj)
{
	return false;
}
bool GameObject::GetCellObject(CellPosition cposition)
{
	return false;
}
GameObject::~GameObject()
{
}