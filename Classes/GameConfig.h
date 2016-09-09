#ifndef  _GAME_CONFIG_H_
#define  _GAME_CONFIG_H_
#include "cocos2d.h"


#define RANDOM_SEEDS() srand(time(0))

#define SCREEN_WIDTH 800*(640.0 / 960.0)
#define SCREEN_HEIGHT 800
#define DISPLAY_STATS true

#define PLAYER_LIMIT_LEFT -240
#define PLAYER_LIMIT_RIGHT 240
#define PLAYER_LIMIT_TOP 737
#define PLAYER_LIMIT_BOT -376

//#define visible_size_macro Director::getInstance()->getVisibleSize();
//#define origin_point Director::getInstance()->getVisibleOrigin();


enum {
	kSpriteManager = 0,
};


#endif