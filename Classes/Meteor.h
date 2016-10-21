#pragma once
#ifndef __METEOR_H__
#define __METEOR_H__

#include "cocos2d.h"
#include "GameEntity.h"
#include "Definitions.h"
#include <cstdlib>
#include <ctime>

USING_NS_CC;

using namespace std;

class Meteor : public GameEntity
{
public:
	Meteor();
	~Meteor();

	void runMeteor(Layer *layer, int index, float speed);
	void resetMeteor();
	void displayExplosion(Layer *layer);
	void update(float dt);


	
	Sprite *sprite;
	bool live;
	int damge;
	int score;
	int type;

protected:


};

#endif // !__METEOR_H__