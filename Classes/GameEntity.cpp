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
	_spr = nullptr;
	_spr3D = nullptr;
	_body = nullptr;
	_radius = 0;

}


GameEntity::~GameEntity()
{
}
