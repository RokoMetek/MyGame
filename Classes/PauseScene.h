#pragma once
#ifndef __PAUSE_SCENE_H__
#define __PAUSE_SCENE_H__

#include "cocos2d.h"


USING_NS_CC;
using namespace std;

class PauseScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(PauseScene);

	void resume(cocos2d::Ref* sender);
	void resume_callback();

	void backToMenu(cocos2d::Ref* sender);
	void backToMenu_callback();

	/*
	PauseScene();
	~PauseScene();
	*/

private:
	MenuItemSprite *resume_item;
	MenuItemSprite *backToMenu_item;
};

#endif

