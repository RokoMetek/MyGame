#include "PauseScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

cocos2d::Scene * PauseScene::createScene()
{

	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = PauseScene::create();
	layer->setName("PauseScene");


	// add layer as a child to scene
	scene->addChild(layer);

	return scene;
}

bool PauseScene::init()
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


	//************* adds resume button ***********
	auto resume_normal = Sprite::createWithSpriteFrameName("resume_button.png");
	auto resume_pressed = Sprite::createWithSpriteFrameName("resume_button.png");

	resume_item = MenuItemSprite::create(resume_normal, resume_pressed, CC_CALLBACK_1(PauseScene::resume, this));
	resume_item->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 100);

	//************* adds back to main menu button ***********
	auto backToMenu_normal = Sprite::createWithSpriteFrameName("backtomenu_button.png");
	auto backToMenu_pressed = Sprite::createWithSpriteFrameName("backtomenu_button.png");

	backToMenu_item = MenuItemSprite::create(backToMenu_normal, backToMenu_pressed, CC_CALLBACK_1(PauseScene::backToMenu, this));
	backToMenu_item->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 50);
	backToMenu_item->setRotation(-90.0f);

	//Menu
	auto menu = Menu::create(resume_item, backToMenu_item, NULL);
	menu->setPosition(origin);
	menu->setScale(2.0);
	this->addChild(menu, 1);

	return true;

}

void PauseScene::resume(cocos2d::Ref * sender)
{
	//resume_item button animation
	resume_item->runAction(Sequence::create(
		ScaleTo::create(0.1f, 1.2f),
		ScaleTo::create(0.1f, 0.8f),
		ScaleTo::create(0.1f, 1.0f),
		CallFunc::create(CC_CALLBACK_0(PauseScene::resume_callback, this)), NULL));
}

void PauseScene::resume_callback()
{
	log("test resume callback");
	Director::getInstance()->popScene();
}

void PauseScene::backToMenu(cocos2d::Ref * sender)
{
	//backToMenu_item button animation
	backToMenu_item->runAction(Sequence::create(
		ScaleTo::create(0.1f, 1.2f),
		ScaleTo::create(0.1f, 0.8f),
		ScaleTo::create(0.1f, 1.0f),
		CallFunc::create(CC_CALLBACK_0(PauseScene::backToMenu_callback, this)), NULL));
}

void PauseScene::backToMenu_callback()
{
	//log("test backToMenu_callback");

	auto scene = MainMenuScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(scene);
}

/*
PauseScene::PauseScene()
{

	//Touch interaction
	setTouchEnabled(true);
}


PauseScene::~PauseScene()
{
}
*/
