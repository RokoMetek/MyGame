#include "GameEntity.h"


/*
Node * GameEntity::getModel()
{
	//return this->_Model;
	return _Model;
}
*/

GameEntity::GameEntity()
{
	_Model = nullptr;
	_radius = 0;
	_type = 0;
	_width = 0;
	_height = 0;


	
	//_pos = new Vec2(0, 0);
	_posX = 0;
	_posY = 0;
}


GameEntity::~GameEntity()
{
}
