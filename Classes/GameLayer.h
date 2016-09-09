#pragma once
#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameEntity.h"




USING_NS_CC;
class Player;
class GameEntity;
class PPlayer;

class GameLayer : public Layer
{
public:

	//static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameLayer);

	void didiAccelerate(CCAcceleration *pAccelerationValue);

	void GoToPauseScene(Ref *pSender);

	void update(float dt);
	void shootPlayerBullets(float dt);
	void playerUpdate(float dt);

	/*
	GameLayer();
	~GameLayer();
	*/

private:
	Sprite *backgroundSpriteArray[2];
	Sprite *_spr;

	ParallaxNode *backgroundNode;
	Sprite *bg_planetEarth;
	Sprite *bg_planetEuropa;
	Sprite *bg_planeUranus;


	Player *_player;
	Sprite3D *_spr3D;
	Vector<Sprite*> _shipLaser;
	int _nextShipLasser;

	PPlayer *_ship;


};

#endif