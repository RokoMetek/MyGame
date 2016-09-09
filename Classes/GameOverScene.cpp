#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "GameLayer.h"
#include "HelloWorldScene.h"

USING_NS_CC;

cocos2d::Scene * GameOverScene::createScene()
{

	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameOverScene::create();
	layer->setName("GameOver");


	// add layer as a child to scene
	scene->addChild(layer);

	return scene;
}

bool GameOverScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	//Loading spritesheet menu_scene
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("menu_scene.plist", "menu_scene.png");

	//************* adds play again button ***********
	auto playagain_normal = Sprite::createWithSpriteFrameName("playagain_button.png");
	auto playagain_pressed = Sprite::createWithSpriteFrameName("playagain_button.png");

	playagain_item = MenuItemSprite::create(playagain_normal, playagain_pressed, CC_CALLBACK_1(GameOverScene::playAgain, this));
	playagain_item->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100);
	playagain_item->setRotation(-90.0f);

	//************* adds back to main menu button ***********
	auto backToMenu_normal = Sprite::createWithSpriteFrameName("backtomenu_button.png");
	auto backToMenu_pressed = Sprite::createWithSpriteFrameName("backtomenu_button.png");

	backToMenu_item = MenuItemSprite::create(backToMenu_normal, backToMenu_pressed, CC_CALLBACK_1(GameOverScene::backToMenu, this));
	backToMenu_item->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50);
	backToMenu_item->setRotation(-90.0f);

	//Menu
	auto menu = Menu::create(playagain_item, backToMenu_item, NULL);
	menu->setPosition(origin);
	menu->setScale(2.0);
	this->addChild(menu, 1);

	return true;
}


void GameOverScene::backToMenu(cocos2d::Ref * sender)
{
	//backToMenu_item button animation
	backToMenu_item->runAction(Sequence::create(
		ScaleTo::create(0.1f, 1.2f),
		ScaleTo::create(0.1f, 0.8f),
		ScaleTo::create(0.1f, 1.0f),
		CallFunc::create(CC_CALLBACK_0(GameOverScene::backToMenu_callback, this)), NULL));
}

void GameOverScene::backToMenu_callback()
{
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(scene);
}



void GameOverScene::playAgain(cocos2d::Ref * sender)
{
	//playagain_item button animation
	playagain_item->runAction(Sequence::create(
		ScaleTo::create(0.1f, 1.2f),
		ScaleTo::create(0.1f, 0.8f),
		ScaleTo::create(0.1f, 1.0f),
		CallFunc::create(CC_CALLBACK_0(GameOverScene::playAgain_callback, this)), NULL));
}

void GameOverScene::playAgain_callback()
{
	auto scene = HelloWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}


