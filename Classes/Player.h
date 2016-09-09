#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "base\CCController.h"
#include "base\CCEventListenerController.h"
#include "GameConfig.h"
#include "GameEntity.h"
#include "StarShipStats.h"

USING_NS_CC;

using namespace std;

class Player : public StarShipStats
{


public:
	CREATE_FUNC(Player);

	//Inicijalizacija
	bool init();

	//Touch listener
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	virtual void onTouchEnded(Touch *touch, Event *event);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void update(float dt);

	CC_SYNTHESIZE(float, targetAngle, TargetAngle);
	CC_SYNTHESIZE(Vec2, targetPos, TargetPos);


	//void setTargetAngle(float angle) { targetAngle = angle; };
	//void setTargetPos(Vec2 target) { targetPos = target; };

	static const float rollSpeed;// recommended 1.5
	static const float returnSpeed;// recommended 4
	static const float maxRoll;
	static const float rollReturnThreshold;

	void setPosition(Vec2 pos);

	void shoot();


	Player();
	Player(Layer *layer);
	~Player();

protected:
	//float targetAngle;
	//Vec2 targetPos;
};

#endif 