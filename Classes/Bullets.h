#pragma once
#ifndef __BULLETS_H__
#define __BULLETS_H__
#include "cocos2d.h"
#include "GameEntity.h"
#include "PPlayer.h"


USING_NS_CC;
using namespace std;

class Bullets : public GameEntity
{
public:
	Bullets();
	~Bullets();

	/*
	CC_SYNTHESIZE(Node*, _Model, Model);
	CC_SYNTHESIZE(float, _radius, Radius);

	CC_SYNTHESIZE(int, _type, Type);
	CC_SYNTHESIZE(float, _width, Width);
	CC_SYNTHESIZE(float, _height, Height);
	CC_SYNTHESIZE(Point*, _pos, Pos);
	CC_SYNTHESIZE(float, _posX, PosX);
	CC_SYNTHESIZE(float, _posY, PosY);

	CC_SYNTHESIZE(Sprite*, _spr, Spr);
	CC_SYNTHESIZE(Sprite3D*, _spr3D, Spr3D);
	*/

	CC_SYNTHESIZE(float, _damge, Damge);

};

class PlayerBullet : public Bullets
{
public:
	PlayerBullet();
	PlayerBullet(Layer *layer, PPlayer *player);
	~PlayerBullet();

	void resetPlayerBullet();


};

class EnemyBullet : public Bullets 
{

};


#endif // !__BULLETS_H__
