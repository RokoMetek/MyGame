#pragma once
#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameEntity.h"
#include "Enemies.h"
#include "Meteor.h"
#include "Bullets.h"



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


	void GoToPauseScene(Ref *pSender);
	//void GoToGameOverScene();

	void update(float dt);
	void shootPlayerBullets(float dt);
	void shootEnemyBullets(float dt);
	void playerUpdate(float dt);
	void spawnMeteor(float dt);
	void spawnEnemy3(int enemySpawnType);

	void enemyWave(int type);



	bool onContactBegin(PhysicsContact &physicContact);



	void reserveContainer();


	void meteorCollision(int index);
	void bulletCollision(int index);
	void enemyCollision(int index);
	void enemyBulletCollision(int index);


	float timeToPoint(Vec2 endPos, Vec2 startPos, float speed);

	void scaleDifficulty();
	void scaleBGspeed();


	void safeRemoveAll();


public:

	float _timerMeteor;
	float _timerBullet;
	float _timerEnemy;

	float _timerBulletE1 = 0;
	float _timerBulletE2 = 0;
	float _timerBulletE3 = 0;
	float _timerBulletE4 = 0;

	float _elapsedTime = 0;


	PPlayer *_player;



	int _meteorContainerIndex;
	int _bulletContainerIndex;
	int _enemyContainerIndex;
	int _enemyBulletContainerIndex;



	Meteor *_meteor;
	//Bullets *_bullet;


	//vector<Meteor *> _meteorsContainer;
	Vector<Meteor *> _meteorsContainer;
	Vector<PlayerBullet *> _bulletsContainer;
	
	Vector<Enemies *> _enemysContainer;
	Vector<EnemyBullet *> _enemyBulletsContainer;




	float _frequencyMeteor = 0.4f;
	float _frequencyEnemy = 15.0f;

	float _speedMeteor = 0.008f;
	






	/*
	Sprite *backgroundSpriteArray[2];
	Sprite *_spr;

	ParallaxNode *backgroundNode;
	Sprite *bg_planetEarth;
	Sprite *bg_planetEuropa;
	Sprite *bg_planeUranus;


	//Player *_player;
	Sprite3D *_spr3D;
	Vector<Sprite*> _shipLaser;
	int _nextShipLasser;
	*/

	/*
	PPlayer *_ship;
	Meteor *metro;
	Enemies *enemy;
	*/





};

#endif