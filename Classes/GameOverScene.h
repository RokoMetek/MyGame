#pragma once
#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"


USING_NS_CC;
using namespace std;

class GameOverScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene(int score);

	virtual bool init();

	CREATE_FUNC(GameOverScene);

	void backToMenu(cocos2d::Ref* sender);
	void backToMenu_callback();

	void playAgain(cocos2d::Ref* sender);
	void playAgain_callback();


	GameOverScene();
	~GameOverScene();

private:

	MenuItemSprite *backToMenu_item;
	MenuItemSprite *playagain_item;
	

};

#endif

