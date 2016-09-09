#include "GameLayer.h"
#include "PauseScene.h"
#include "Player.h"
#include "GameEntity.h"
#include "Box2D\Box2D.h"
#include "Definitions.h"
#include "Meteor.h"
#include "PPlayer.h"
#include "Bullets.h"


USING_NS_CC;
using namespace std;



/*
cocos2d::Scene * GameLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameLayer::create();
	layer->setName("GameLayer");


	// add layer as a child to scene
	scene->addChild(layer, 2, layer->getName());
	

	return scene;

}
*/

bool GameLayer::init()
{


	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	auto pauseItem =MenuItemImage::create("pause_button.png", "pause_button.png", CC_CALLBACK_1(GameLayer::GoToPauseScene, this));
	pauseItem->setPosition(Point(pauseItem->getContentSize().width -(pauseItem->getContentSize().width / 4) + origin.x, visibleSize.height - pauseItem->getContentSize().height + (pauseItem->getContentSize().width / 4) + origin.y));
	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);


	_ship = new PPlayer(this);

	Meteor *mm = new Meteor();
	mm->runMeteor(this, 1, 0.005f);

	schedule(schedule_selector(GameLayer::shootPlayerBullets), 1.5, -1, 0);
	schedule(schedule_selector(GameLayer::playerUpdate));


	//Particle test
	
	auto booster = ParticleSystemQuad::create("Particles/missileFlare.plist");
	//addChild(booster);
		
	//Physic world test
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	//Bezier Test
	/*
	auto spr = Sprite::create("earth.png");
	addChild(spr);

	ccBezierConfig bezier;     
	bezier.controlPoint_1 = Vec2(0, 100);
	bezier.controlPoint_2 = Vec2(100, 100);
	bezier.endPosition = Vec2(200, 200);

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = ccp(100, winSize.height / 2);
	bezier2.controlPoint_2 = ccp(200, -winSize.height / 2);
	bezier2.endPosition = ccp(240, 160);

	CCActionInterval* bezierTo1 = CCBezierTo::create(2, bezier2);

	spr->runAction(bezierTo1);
	*/


	this->scheduleUpdate();

	return true;
}

void GameLayer::didiAccelerate(CCAcceleration * pAccelerationValue)
{
	float accel_filter = 0.1f;
}

void GameLayer::GoToPauseScene(Ref * pSender)
{
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}


//GameLayer update function
void GameLayer::update(float dt)
{
	//Get visibleSize, origin and winSize
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	//_ship->showExplosion(this);

	//_ship->targetRollUpdate(dt);
	//_player->update(dt);

}


//Shoting bullets
void GameLayer::shootPlayerBullets(float dt)
{
	//log("shoot bullets");
	Bullets *bul = new PlayerBullet(this, _ship);
}


//Player Update
void GameLayer::playerUpdate(float dt)
{
	_ship->targetRollUpdate(dt);
}

/*
GameLayer::GameLayer()
{


	//Touch interaction
	setTouchEnabled(true);

	setAccelerometerEnabled(true);
}


GameLayer::~GameLayer()
{
}
*/