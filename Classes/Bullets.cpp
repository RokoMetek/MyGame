#include "Bullets.h"
#include "math\CCMath.h"


Bullets::Bullets()
{
	_damge = 10;
	_bulletParticle = nullptr;
	_bulletSprite = nullptr;
	_bulletSprites.clear();
}


Bullets::~Bullets()
{
}

void Bullets::resetBullet()
{


	this->unscheduleUpdate();
	_bulletSprite->stopAllActions();
	_bulletSprite->removeFromParentAndCleanup(true);
	

	//_bulletParticle->stopAllActions();
	//_bulletParticle->removeFromParentAndCleanup(true);

	/*
	for(int i=0; i < _bulletSprites.size(); i++)
	{ 
		this->unscheduleUpdate();
		_bulletSprites.at(i)->stopAllActions();
		_bulletSprites.at(i)->removeFromParentAndCleanup(true);

		//_bulletParticle->stopSystem();
	}
	*/

	//_bulletSprites.clear();
	
}



float Bullets::bulletTimeToPoint(Vec2 endPos, Vec2 startPos, float speed)
{

	/*
	-(float)getEnemyTimeToPoint:(CGPoint)targetPoint fromPoint:(CGPoint)sourcePoint speed:(int)travelSpeed {
	return sqrt( pow((targetPoint.x-sourcePoint.x),2) + pow((targetPoint.y-sourcePoint.y),2) ) / travelSpeed;}
	*/

	float distance = sqrt(pow((endPos.x - startPos.x), 2) + pow((endPos.y - startPos.y), 2)) / speed;
	return distance;

}

void Bullets::bulletImpact(Layer * layer)
{
	auto explosion = ParticleSystemQuad::create("Particles/bulletCollision.plist");
	explosion->setPosition(this->_bulletSprite->getPosition());
	explosion->setScale(0.8);
	explosion->setAutoRemoveOnFinish(true);

	layer->addChild(explosion);
}

void Bullets::update(float dt)
{



	if (_bulletSprite->getPosition().y > 460)
	{
		log("Bullet out of screen UP");
		this->resetBullet();
	}
	//Ako je dole
	else if (_bulletSprite->getPosition().y < -460)
	{
		log("Bullet out of screen Down");
		this->resetBullet();
	}
	//Ako je ljevo
	else if (_bulletSprite->getPosition().x > 320)
	{
		log("Bullet out of screen Left");
		this->resetBullet();
	}
	//Ako je desno
	else if (_bulletSprite->getPosition().x < -320)
	{
		log("Bullet out of screen Right");
		this->resetBullet();
	}

	/*
	//Ako je gore
	if (_bulletSprites.at(0)->getPosition().y > 460)
	{ 
		log("Bullet out of screen UP");
		this->resetBullet();
	}
	//Ako je dole
	else if (_bulletSprites.at(0)->getPosition().y < -460)
	{
		log("Bullet out of screen Down");
		this->resetBullet();
	}
	//Ako je ljevo
	else if (_bulletSprites.at(0)->getPosition().x > 320)
	{
		log("Bullet out of screen Left");
		this->resetBullet();
	}
	//Ako je desno
	else if (_bulletSprites.at(0)->getPosition().x < -320)
	{
		log("Bullet out of screen Right");
		this->resetBullet();
	}
	*/
	
}

	

PlayerBullet::PlayerBullet()
{

}


void PlayerBullet::startBullet(Layer * layer, PPlayer * player, int index)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();


	_bulletSprite = Sprite::createWithSpriteFrameName("bullet_4.png");


	//SetPhysic body
	auto _body = PhysicsBody::createCircle(this->getBullettSprite()->getContentSize().width / 3);
	_body->setCollisionBitmask(COLLISION_BULLET);
	_body->setContactTestBitmask(1);
	_body->setDynamic(false);
	_body->setTag(index);
	_bulletSprite->setPhysicsBody(_body);


	//_par = ParticleSystemQuad::create("Particles/Comet.plist");



	//Straightforward move bullet
	//float speedBullet = bulletTimeToPoint(Vec2(player->getTargetPos().x + origin.x, visibleSize.height / 2 + origin.y), player->getTargetPos(), 500);
	//auto bulletMoveTo = MoveTo::create(0.003 * visibleSize.height, Vec2(player->getTargetPos().x + origin.x, visibleSize.height + origin.y));
	auto bulletMoveTo = MoveTo::create(2.88f, Vec2(player->getTargetPos().x + origin.x, visibleSize.height + origin.y));
	//auto bulletMoveTo = MoveTo::create(speedBullet, Vec2(player->getTargetPos().x + origin.x, visibleSize.height / 2 + origin.y));
	auto sequence = Sequence::create(
		bulletMoveTo,
		CallFunc::create(CC_CALLBACK_0(Bullets::resetBullet, this)),
		nullptr);



	_bulletSprite->runAction(sequence);
	_bulletSprite->setPosition(player->getSpr3D()->getPosition());
	_bulletSprite->setPositionY(player->getSpr3D()->getPosition().y + 50);
	//_bulletSprites.pushBack(_bulletSprite);

	
	_bulletParticle = ParticleSystemQuad::create("Particles/Bullet1.plist");
	_bulletParticle->setPosition(Vec2(0, 0));
	_bulletParticle->setScale(1);
	_bulletParticle->setRotation(90);
	_bulletParticle->setAutoRemoveOnFinish(true);
	_bulletParticle->setPosition(player->getSpr3D()->getPosition());
	_bulletParticle->setPositionY(player->getSpr3D()->getPosition().y + 50);
	_bulletParticle->setScaleY(0.8);
	_bulletParticle->setLifeVar(0.3);
	_bulletParticle->setDuration(2);
	_bulletParticle->runAction(sequence->clone());

	layer->addChild(_bulletParticle);
	
	this->_damge = 10;


	this->scheduleUpdate();
	layer->addChild(_bulletSprite);

	//layer->addChild(_bulletSprites.at(0));
}

void PlayerBullet::update(float dt)
{
	Bullets::update(dt);
}

PlayerBullet::~PlayerBullet()
{

}



EnemyBullet::EnemyBullet()
{

}


void EnemyBullet::startBullet(Layer * layer, Vec2 startPos, Vec2 directionVector, int index)
{

	////////////////////////////////////////////////////////////
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
	///////////////////////////////////////////////////////////

	int bulletIndex = RandomHelper::random_int(1, 6);
	bulletIndex = 3;
	auto bulletStringOBJ = __String::createWithFormat(BULLET, bulletIndex)->getCString();
	_bulletSprite = Sprite::createWithSpriteFrameName(bulletStringOBJ);


	auto _body = PhysicsBody::createCircle(_bulletSprite->getContentSize().width / 2);
	_body->setCollisionBitmask(COLLISION_BULLET_ENEMY);
	_body->setContactTestBitmask(1);
	_body->setDynamic(false);
	_body->setTag(index);
	_bulletSprite->setPhysicsBody(_body);




	float bulletTime = bulletTimeToPoint(directionVector, startPos, 270);

	//auto offX = RandomHelper::random_int(-300, 300);

	//auto bulletMoveTo = MoveTo::create(bulletTime * visibleSize.height, directionVector);
	auto bulletMoveTo = MoveTo::create(bulletTime, directionVector);
	auto sequence = Sequence::create(
		bulletMoveTo,
		CallFunc::create(CC_CALLBACK_0(Bullets::resetBullet, this)),
		nullptr);


	_bulletSprite->runAction(sequence);
	_bulletSprite->setPosition(startPos);
	_bulletSprite->setPositionY(startPos.y);
	//_bulletSprites.pushBack(bulletSprite);

	
	this->scheduleUpdate();
	layer->addChild(_bulletSprite);
	//layer->addChild(_bulletSprites.at(0));


}

void EnemyBullet::update(float dt)
{
	Bullets::update(dt);
}

EnemyBullet::~EnemyBullet()
{
}
