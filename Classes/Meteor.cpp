#include "Meteor.h"


Meteor::Meteor()
{
}


Meteor::~Meteor()
{
}

void Meteor::runMeteor(Layer * layer, int index, float speed)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	auto meteorIndex = RandomHelper::random_int(1,22);

	//Dodjeljivanje parametara
	auto meteorString = __String::createWithFormat(ASTEROID, meteorIndex);
	_spr = Sprite::createWithSpriteFrameName(meteorString->getCString());
	_width = _spr->getContentSize().width;
	_height = _spr->getContentSize().height;

	_body = PhysicsBody::createCircle(this->getSpr()->getContentSize().width / 2);
	_body->setCollisionBitmask(0x000001);
	_body->setContactTestBitmask(true);
	_body->setDynamic(false);
	_spr->setPhysicsBody(_body);



	//Random range generator
	//Formula: rand()*range + min)

	srand(time(NULL));


	//Random generator range x-os
	auto posX = RandomHelper::random_int((int)(-visibleSize.width / 2 + _width), (int)(visibleSize.width/2 - _width));
	//auto posX = (rand() % static_cast<int>(visibleSize.width)) + (-(visibleSize.width / 2));
	if (posX + _width / 2 > visibleSize.width)
		posX = visibleSize.width - _width / 2;

	auto offX = (rand() % static_cast<int>(visibleSize.width)) + (_width / 2);
	if (offX + _width / 2 > visibleSize.width)
		offX = visibleSize.width - _width / 2;

	

	//auto meteorMoveTo = MoveTo::create(speed * visibleSize.height + origin.x, Vec2(offX + origin.x, -_height + origin.y));
	auto meteorMoveTo = MoveTo::create(speed *visibleSize.height, Vec2(offX + origin.x,  -visibleSize.height));
	auto meteorRotateBy = RepeatForever::create(RotateBy::create(speed * visibleSize.height, 360));

	auto sequence = Sequence::create(
		meteorMoveTo,
		CallFunc::create(CC_CALLBACK_0(Meteor::resetMeteor, this)),
		nullptr);

	_spr->setPosition(Vec2(posX, visibleSize.height/2 + origin.y + _height));
	_spr->runAction(sequence);
	_spr->runAction(meteorRotateBy);
	

	layer->addChild(_spr, 10, GAME_OBJECT);
}

void Meteor::resetMeteor()
{
	_spr->stopAllActions();
	_spr->removeFromParentAndCleanup(true);
}

void Meteor::displayExplosion(Layer * layer)
{
	
}
