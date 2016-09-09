#include "GameConfig.h"
#include "MainMenuScene.h"
#include "HelloWorldScene.h"
#include "GameLayer.h"
#include "PauseScene.h"
#include "GameOverScene.h"


USING_NS_CC;

Scene * MainMenuScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainMenuScene::create();
	layer->setName("MainMenu");


	// add layer as a child to scene
	scene->addChild(layer);
	
	return scene;
}

bool MainMenuScene::init()
{
	if( !Layer::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	//Loading spritesheet menu_scene
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("menu_scene.plist", "menu_scene.png");

	//Add background
	auto background = Sprite::createWithSpriteFrameName("space_background.png");
	this->addChild(background, -1);
	background->setScale(visibleSize.width / background->getContentSize().width, visibleSize.height / background->getContentSize().height);

	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	background->setGlobalZOrder(-1);

	//************* adds start game button ***********
	auto start_normal = Sprite::createWithSpriteFrameName("startgame_button.png");
	auto start_pressed = Sprite::createWithSpriteFrameName("startgame_button.png");
	
	startgame_item = MenuItemSprite::create(start_normal, start_pressed, CC_CALLBACK_1(MainMenuScene::startgame, this));
	startgame_item->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height/2 + origin.y + 100);

	//************* adds credits game button ***********
	auto credits_normal = Sprite::createWithSpriteFrameName("credits_button.png");
	auto credits_pressed = Sprite::createWithSpriteFrameName("credits_button.png");
	
	credits_item = MenuItemSprite::create(credits_normal, credits_pressed, CC_CALLBACK_1(MainMenuScene::credits, this));
	credits_item->setScale(0.8);
	credits_item->setPosition(visibleSize.width / 2+ origin.x, visibleSize.height / 2 + origin.y + 50);


	//Menu
	auto menu = Menu::create(startgame_item, credits_item, NULL);
	menu->setPosition(origin);
	//menu->setScale(2.0);
	this->addChild(menu, 1);


	return true;
}


void MainMenuScene::startgame(cocos2d::Ref * sender)
{
	//StartGame button animation
	startgame_item->runAction(Sequence::create(
		ScaleTo::create(0.1f, 1.2f),
		ScaleTo::create(0.1f, 0.8f),
		ScaleTo::create(0.1f, 1.0f),
		CallFunc::create(CC_CALLBACK_0(MainMenuScene::startgame_callback, this)), NULL));
}

void MainMenuScene::startgame_callback()
{
	//StartGame button - chnage scene
	//auto scene = TransitionMoveInR::create(0.2f, GameLayer::createScene());
	auto scene = TransitionZoomFlipX::create(0.2f, HelloWorld::createScene());
	
	
	Director::getInstance()->replaceScene(scene);
	
}

void MainMenuScene::credits(cocos2d::Ref * sender)
{
	//Credits button animation
	credits_item->runAction(Sequence::create(
		ScaleTo::create(0.1f, 0.9f),
		ScaleTo::create(0.1f, 0.7f),
		ScaleTo::create(0.1f, 0.8f),
		CallFunc::create(CC_CALLBACK_0(MainMenuScene::credits_callback, this)), NULL));
}

void MainMenuScene::credits_callback()
{
}

/*
MainMenuScene::MainMenuScene()
{

	//Touch interaction
	setTouchEnabled(true);
}


MainMenuScene::~MainMenuScene()
{
}
*/
