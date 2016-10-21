#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "GameLayer.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void initStats();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float dt);




protected:
	HelloWorld();
	~HelloWorld();

private:
	CC_SYNTHESIZE(int, _score, Score);
	CC_SYNTHESIZE(Label*, _labelScore, LabelScore);
	CC_SYNTHESIZE(ui::LoadingBar*, _healthBar, HealthBar);
	CC_SYNTHESIZE(GameLayer*, sb, Sb);
	CC_SYNTHESIZE(float, _scaleDificulty, ScaleDificulty);
	CC_SYNTHESIZE(float, _scaleSpeedBG, ScaleSpeedBG)


	void incrementScore(float dt);
	void setHealthBarPosition(Vec2 vec);
	bool checkScaleDificulty();
	bool checkScaleSpeedBG();

	Sprite* _spr;

	ParallaxNode *backgroundNode;
	Sprite *bg_planetEarth;
	Sprite *bg_planetEuropa;
	Sprite *bg_planeUranus;

	Sprite *bg_galaxy;
	Sprite *bg_anomaly1;
	PhysicsWorld *sceneWorld;
	Physics3DWorld *sceneWorld3D;

	float xScroll = 0.0f;
	float xSpeed = 300;
	

};

#endif // __HELLOWORLD_SCENE_H__
