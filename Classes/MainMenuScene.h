#pragma once
#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"


USING_NS_CC;

class MainMenuScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainMenuScene);


	void startgame(cocos2d::Ref* sender);
	void startgame_callback();

	void credits(cocos2d::Ref* sender);
	void credits_callback();

	/*
	MainMenuScene();
	~MainMenuScene();
	*/

private:
	MenuItemSprite *startgame_item;
	MenuItemSprite *credits_item;
};

#endif
