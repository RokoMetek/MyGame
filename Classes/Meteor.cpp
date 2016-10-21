#include "Meteor.h"
#include "HelloWorldScene.h"





Meteor::Meteor()
{
	live = false;
	sprite = nullptr;
	score = 10;
	damge = 25;
	type = 0;
}


Meteor::~Meteor()
{

}

void Meteor::runMeteor(Layer * layer, int index, float speed)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
	
	
	int meteorIndex = 1;
	auto helloworldLayer = (HelloWorld*)Director::getInstance()->getRunningScene()->getChildByName("HelloWorld");
	if (helloworldLayer != nullptr)
	{
		if (helloworldLayer->getScore() >= 500 && helloworldLayer->getScore() < 1500)
		{
			meteorIndex = RandomHelper::random_int(1, 8);
		}
		else if(helloworldLayer->getScore() >= 1500)
		{
			meteorIndex = RandomHelper::random_int(1, 10);
		}
		
	}
	else
	{
		meteorIndex = RandomHelper::random_int(1,5);
	}


	if (meteorIndex >= 1 && meteorIndex <= 5)
	{
		type = 1;
		score = 10;
		damge = 25;
	}
	else if (meteorIndex >= 6 && meteorIndex <= 8)
	{
		type = 2;
		score = 30;
		damge = 50;
	}
	else if (meteorIndex >= 9 && meteorIndex <= 10)
	{
		type = 3;
		damge = 75;
		//score = 100;
	}

	//meteorIndex = RandomHelper::random_int(1,10);
	//Dodjeljivanje parametara
	auto meteorString = __String::createWithFormat(ASTEROID, meteorIndex);
	sprite = Sprite::createWithSpriteFrameName(meteorString->getCString());

	float randScale = RandomHelper::random_real(0.5, 1.5);
	sprite->setScale(randScale);

	auto _width = sprite->getContentSize().width;
	auto _height = sprite->getContentSize().height;

	auto _body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
	_body->setCollisionBitmask(COLLISION_METEOR);
	_body->setContactTestBitmask(1);
	_body->setDynamic(false);
	_body->setTag(index);
	sprite->setPhysicsBody(_body);

	

	//Random range generator
	//Formula: rand()*range + min)

	//srand(time(NULL));


	//Random generator range x-os
	//auto posX = RandomHelper::random_int((int)(-visibleSize.width / 2 + _width), (int)(visibleSize.width/2 - _width));

	auto posX = RandomHelper::random_int(-300, 300);
	//posX = 0;
	if (posX + _width / 2 > visibleSize.width)
		posX = visibleSize.width - _width / 2;

	//auto offX = (rand() % static_cast<int>(visibleSize.width)) + (_width / 2);
	auto offX = RandomHelper::random_int(-300, 300);
	if (offX + _width / 2 > visibleSize.width)
		offX = visibleSize.width - _width / 2;

	

	//auto meteorMoveTo = MoveTo::create(speed * visibleSize.height + origin.x, Vec2(offX + origin.x, -_height + origin.y));
	auto meteorMoveTo = MoveTo::create(speed *visibleSize.height, Vec2(offX + origin.x,  -visibleSize.height));
	auto meteorRotateBy = RepeatForever::create(RotateBy::create(speed * visibleSize.height, 360));

	auto sequence = Sequence::create(
		meteorMoveTo,
		CallFunc::create(CC_CALLBACK_0(Meteor::resetMeteor, this)),
		nullptr);

	sprite->setPosition(Vec2(posX, visibleSize.height/2 + origin.y + _height));

	sprite->runAction(sequence);
	sprite->runAction(meteorRotateBy);

	//Test colision
	//_spr->setPosition(Vec2(0, 0));
	//this->scheduleUpdate();
	live = true;
	layer->addChild(sprite, 1, GAME_OBJECT);

}

void Meteor::resetMeteor()
{
	live = false;
	this->unscheduleUpdate();
	sprite->stopAllActions();
	sprite->removeFromParentAndCleanup(true);
}

void Meteor::displayExplosion(Layer * layer)
{
	
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("explosions.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("explosions.plist");

	auto Sprite1 = Sprite::createWithSpriteFrameName("explosionsA_1.png");
	Sprite1->setPosition(sprite->getPosition());

	spritebatch->addChild(Sprite1);

	//spritebatch->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//spritebatch->setPosition(this->getSpr()->getPosition());

	Vector<SpriteFrame*> animFrames(10);

	char str[100] = { 0 };
	for (int i = 1; i < 47; i++)
	{
		sprintf(str, "explosionsB_%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		
		animFrames.insert(i - 1, frame);
	}

	auto removeSelf = RemoveSelf::create();
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.02f);

	Sprite1->runAction(Sequence::create(Animate::create(animation), removeSelf, nullptr));

	layer->addChild(spritebatch, -1);
	
	
}

void Meteor::update(float dt)
{
	//Check meteor position and delete if it's out of border
	if (sprite->getPosition().y < DESIGN_BOT_BORDER - sprite->getContentSize().height)
	{
		log("Meteor position x=%i  y=%i", this->sprite->getPosition().x, this->sprite->getPosition().y);
		log("Meteor out of border -> Delete meteor");
		this->resetMeteor();
	}

}
