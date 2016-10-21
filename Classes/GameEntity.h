#pragma once

#ifndef __GAME_ENTITY_H__
#define __GAME_ENTITY_H__

#include "cocos2d.h"


USING_NS_CC;

using namespace std;


class GameEntity : public Node
{
public:
	//CREATE_FUNC(GameEntity);
	
	//Node* getModel();

	GameEntity();
	~GameEntity();


public:
	//CC_SYNTHESIZE(Node*, _Model, Model);
	CC_SYNTHESIZE(float, _radius, Radius);

	//CC_SYNTHESIZE(int, _type, Type);
	//CC_SYNTHESIZE(float, _width, Width);
	//CC_SYNTHESIZE(float, _height, Height);
	//CC_SYNTHESIZE(Vec2, _pos, Pos);
	//CC_SYNTHESIZE(float, _posX, PosX);
	//CC_SYNTHESIZE(float, _posY, PosY);


	CC_SYNTHESIZE(Sprite*, _spr, Spr);
	CC_SYNTHESIZE(Sprite3D*, _spr3D, Spr3D);
	CC_SYNTHESIZE(ParticleSystemQuad*, _par, Par);
	CC_SYNTHESIZE(PhysicsBody*, _body, Body);



	/*
	virtual int getType() const = 0;
	virtual float getWidth() const = 0;
	virtual float getHeight() const = 0;
	virtual Sprite* getSprite() const = 0;
	virtual Point getPosition() const = 0;
	virtual float getPositionX() const = 0;
	virtual float getPositionY() const = 0;
	*/


	//Node* _Model;
	//Sprite *test_sprite;


};

#endif // ! __GAME_ENTITY_H__

