#pragma once
#ifndef __STARSHIP_STATS_H__
#define __STARSHIP_STATS_H__

#include "cocos2d.h"
#include "GameEntity.h"


USING_NS_CC;
using namespace std;

class StarShipStats : public GameEntity
{

public:
	StarShipStats();
	~StarShipStats();
	void showExplosion(Layer *layer);
	void hurt(float damge);



protected:

	CC_SYNTHESIZE(bool, _alive, Alive);
	CC_SYNTHESIZE(float, _hp, Hp);
	CC_SYNTHESIZE(int, _score, Score);


	//bool _alive;
	//float _hp;
	//int _score;


};

#endif

