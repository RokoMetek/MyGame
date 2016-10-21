#pragma once
#ifndef __PPLAYER_H__
#define __PPLAYER_H__
#include "cocos2d.h"
#include "Definitions.h"
#include "GameEntity.h"
#include "StarShipStats.h"

USING_NS_CC;


using namespace std;

class PPlayer : public StarShipStats
{
public:
	//CREATE_FUNC(PPlayer);

	PPlayer();
	PPlayer(Layer* layer);
	~PPlayer();

	CC_SYNTHESIZE(float, targetAngle, TargetAngle);
	CC_SYNTHESIZE(Vec2, targetPos, TargetPos);



	//Touch listener
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);

	void setPosition(Vec2 pos);


	static const float rollSpeed;// recommended 1.5
	static const float returnSpeed;// recommended 4
	static const float maxRoll;
	static const float rollReturnThreshold;

	void targetRollUpdate(float dt);
	void initTail();


	virtual void hurt(float damge);
	
	//virtual Vec2 getPos() { return _spr3D->getPosition(); }

};


#endif // !__PPLAYER_H__