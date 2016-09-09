#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Sprite3DEffect.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float dt);

	static inline float rand_range(float min_num, float max_num) {
		return min_num + (CCRANDOM_0_1()*(max_num - min_num));
	}


protected:
	HelloWorld();
	~HelloWorld();

protected:
	Sprite* _spr;

	ParallaxNode *backgroundNode;
	Sprite *bg_planetEarth;
	Sprite *bg_planetEuropa;
	Sprite *bg_planeUranus;

	Sprite *bg_galaxy;
	Sprite *bg_anomaly1;
	PhysicsWorld *sceneWorld;

	float xScroll = 0.0f;
	float xSpeed = 60;
	

};

#endif // __HELLOWORLD_SCENE_H__
