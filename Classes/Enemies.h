#pragma once
#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include "cocos2d.h"
#include "StarShipStats.h"
#include "Definitions.h"
#include "GameEntity.h"
#include "Bullets.h"

using namespace std;

enum moveType {
	move1,
	move2,
	move3,
	move4
};

enum shootType {
	shoot1,
	shoot2,
	shoot3,
	shoot4
};


class Enemies : public StarShipStats
{

public:
	Enemies();
	Enemies(Layer* layer);
	~Enemies();

	void runEnemies(Layer *layer, int index, int type);


	void resetEnemies();

	CC_SYNTHESIZE(int, _moveType, MoveType);
	CC_SYNTHESIZE(int, _shootType, ShootType);
	//CC_SYNTHESIZE(int, _offset, Offset);


	void movementMode(int tipMove);
	void displayExplosion(Layer *layer);

};



#endif // !__ENEMIES_H__