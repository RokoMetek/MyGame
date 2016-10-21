#pragma once
#ifndef __BULLETS_H__
#define __BULLETS_H__
#include "cocos2d.h"
//#include "GameEntity.h"
#include "PPlayer.h"


USING_NS_CC;
using namespace std;

class Bullets : public Node
{
public:
	Bullets();
	~Bullets();


	CC_SYNTHESIZE(float, _damge, Damge);
	CC_SYNTHESIZE(Sprite*, _bulletSprite, BullettSprite);
	CC_SYNTHESIZE(Vector<Sprite*>, _bulletSprites, BulletSprites);
	CC_SYNTHESIZE(ParticleSystemQuad*, _bulletParticle, BulletParticle);


	void resetBullet();
	float bulletTimeToPoint(Vec2 endPos, Vec2 startPos, float speed);
	void bulletImpact(Layer *layer);
	void update(float dt);

};

class PlayerBullet : public Bullets
{
public:

	PlayerBullet();
	void startBullet(Layer *layer, PPlayer *player, int index);
	void update(float dt);
	~PlayerBullet();





};

class EnemyBullet : public Bullets
{

public:
	EnemyBullet();
	void startBullet(Layer *layer, Vec2 startPos, Vec2 directionVector, int index);
	void update(float dt);
	~EnemyBullet();

};


#endif // !__BULLETS_H__
