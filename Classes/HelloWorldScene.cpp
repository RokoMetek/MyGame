#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameConfig.h"
#include "GameOverScene.h"
#include "Meteor.h"
#include "physics3d\CCPhysics3D.h"




//#include "CCParallaxScrollNode.h"
//#include "CCParallaxScrollOffset.h"



USING_NS_CC;
using namespace std;
using namespace ui;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	layer->sceneWorld = scene->getPhysicsWorld();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	

	layer->setName("HelloWorld");	
	layer->setTag(100);
	
    // add layer as a child to scene
	scene->addChild(layer);

	//Warnin Layer
	auto warningLayer = LayerColor::create(Color4B(255, 0, 0, 60));
	warningLayer->setOpacity(0);
	warningLayer->setName("WarningLayer");
	scene->addChild(warningLayer, 7);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

	initStats();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 12);


	//Perload musci
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_LASERSHOOT);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_EXPLOSION1);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(SOUND_EFFECT_EXPLOSION2);

	
	//Game layer (logic)
	sb = GameLayer::create();
	sb->setName("GameLayer");
	sb->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height/2 + origin.y));
	addChild(sb, -1);



	_healthBar = LoadingBar::create();
	_healthBar->setName("HealthBar");
	_healthBar->loadTexture("HealthBar.png");
	_healthBar->setPercent(100);
	_healthBar->setRotation(90);
	_healthBar->setFlippedY(true);
	_healthBar->setScale(0.2);
	_healthBar->setPosition(Point(visibleSize.width / 2 - 250, visibleSize.height / 2 - 350));
	_healthBar->setDirection(LoadingBar::Direction::RIGHT);
	this->addChild(_healthBar, -1);


	



	_labelScore = Label::createWithTTF("Score: 0", "fonts/PLANK___.ttf", 32);
	_labelScore->setPosition(Point(visibleSize.width / 2, visibleSize.height - _labelScore->getContentSize().height));
	this->addChild(_labelScore);



	/*
	Sprite *progresBorder = Sprite::create("progress-bar-type.png");
	//progresBorder->setAnchorPoint(Vec2(0, 0));
	progresBorder->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	progresBorder->setRotation(90);
	progresBorder->setScaleY(2);
	this->addChild(progresBorder);

	Sprite *progresSprite = Sprite::create("HelloWorld.png");
	//progresSprite->setPosition(Point(visibleSize.width / 2 + 200, visibleSize.height / 2));

	
	ProgressTimer *progresTimerHP = ProgressTimer::create(progresSprite); 
	progresTimerHP->setBarChangeRate(Vec2(1, 1));
	progresTimerHP->setAnchorPoint(Vec2(0.5, 1));
	progresTimerHP->setType(ProgressTimer::Type::BAR);
	progresTimerHP->setPosition(Point(visibleSize.width / 2 + 100, visibleSize.height / 2));
	progresTimerHP->setPercentage(50);
	//progresTimerHP->getSprite()->setPosition(Vec2(0, 0));
	progresTimerHP->getSprite()->setScale(0.0001);

	progresSprite->setScale(1);

	this->addChild(progresTimerHP);
	*/


	

	


	//Physic world test
	/*
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode, 50);
	*/

	/*
	Meteor *met = new Meteor();
	met->runMeteor(this, 1, 0.5f);
	met->getSpr()->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	met->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(met, 111);
	*/

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    /*
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	*/



	//sprite sheet test animation
	/*
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("explosions.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("explosions.plist");

	auto Sprite1 = Sprite::createWithSpriteFrameName("explosionsA_1.png");

	spritebatch->addChild(Sprite1);
	addChild(spritebatch, -1);

	spritebatch->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	Vector<SpriteFrame*> animFrames(10);

	char str[100] = { 0 };
	for (int i = 0; i < 21; i++)
	{
		sprintf(str, "explosionsE_%d.png", i+1);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		animFrames.insert(i, frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.08f);
	Sprite1->runAction(RepeatForever::create(Animate::create(animation)));
	*/
	
	

	//Repeat Texture 1.
	_spr = Sprite::create("background5.png");
	addChild(_spr, -1);
	Texture2D::TexParams texRepeat = { GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_REPEAT };
	_spr->getTexture()->setTexParameters(texRepeat);
	_spr->setRotation3D(Vec3(-10.0, 0.0f, 0.0f));
	_spr->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 175));
	_spr->setScale(1.0);
	_spr->setGlobalZOrder(-1);

	
	
	/*
	backgroundNode = ParallaxNode::create();
	this->addChild(backgroundNode, -1);

	bg_planetEarth = Sprite::create("earth.png");
	bg_planetEuropa = Sprite::create("europa.png");
	bg_planeUranus = Sprite::create("uranus.png");
	bg_galaxy = Sprite::create("background2.png");
	bg_anomaly1 = Sprite::create("anomaly1");

	Point anomalySpeed = Vec2(0.1, 0.1);
	Point bgSpeed = Vec2(0.05, 0.05);

	
	float randX = rand_range(0, visibleSize.width);
	float randY = rand_range(0, visibleSize.height);

	backgroundNode->addChild(bg_galaxy, -1, bgSpeed, Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	backgroundNode->addChild(bg_planetEarth, 0, anomalySpeed, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	backgroundNode->addChild(bg_planetEuropa, 0, anomalySpeed, Vec2(bg_planetEarth->getContentSize().width, winSize.height / 2));
	


	this->addChild(backgroundNode);
	*/

	/*
	auto _streak = MotionStreak::create(0.4, 1, 15, Color3B(255, 255, 255), "europa.png");
	_streak->setBlendFunc(BlendFunc::ADDITIVE);
	_streak->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y));
	//auto _player->setTrail(_streak);
	addChild(_streak, 3);
	*/
	

	/*
	auto ss = Sprite::create("streak.png");
	ss->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y));
	addChild(ss, 3);
	*/


	//3D Test SciFi_Fighter-MK6 SciFi_Fighter-MK6-diffuse


	//auto _ambientLight = AmbientLight::create(Color3B(200, 200, 200));
	//_ambientLight->setEnabled(true);
	//addChild(_ambientLight);

	/*
	auto ss = Sprite3D::create("untitled1.c3b");
	ss->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y));
	ss->setScale(5);
	ss->setTexture("space_cruiser_4_color.png");
	//ss->setTexture("Weapons.jpg");
	this->addChild(ss, 100);
	*/

	/*
	Node* _Model = EffectSprite3D::createFromObjFileAndTexture("Main_starship.c3b", "mappa-base.png");
	_Model->setPosition(Vec2(visibleSize.width * 0.5f + origin.x, visibleSize.height * 0.5f + origin.y));
	_Model->setScale(1);
	_Model->setRotation3D(Vec3(45, 0, 0));

	this->addChild(_Model);
	*/


	this->scheduleUpdate();

    return true;
}

void HelloWorld::initStats()
{
	_score = 0;
	_scaleDificulty = 0;
	_scaleSpeedBG = 0;

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}

void HelloWorld::update(float dt)
{
	//log("update");
	/*
	Point backgroundScrollVert = ccp(0, -1000);
	backgroundNode->setPosition(ccpAdd(backgroundNode->getPosition(), ccpMult(backgroundScrollVert, dt)));
	*/

	xScroll += xSpeed*dt;
	_spr->setTextureRect(Rect(0, -((int)xScroll) % 2048, 1024, 1200));

	_healthBar->setPosition(sb->_player->getSpr3D()->getPosition() + Vec2(260, 480));
	
	if (!sb->_player->getAlive())
	{
		this->removeAllChildrenWithCleanup(true);

		auto scene = GameOverScene::createScene(_score);
		Director::getInstance()->replaceScene(scene);
	}

}

HelloWorld::HelloWorld()
{
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::incrementScore(float dt)
{
	//this->_score++;
	this->_score += dt;
	auto scoreString = __String::createWithFormat("Score: %i", _score)->getCString();
	_labelScore->setColor(Color3B::ORANGE);
	_labelScore->setString(scoreString);

	_scaleDificulty += dt;
	if (checkScaleDificulty())
	{
		sb->scaleDifficulty();
	}

	_scaleSpeedBG += dt;
	if (checkScaleSpeedBG())
	{
		sb->scaleBGspeed();
	}



}

void HelloWorld::setHealthBarPosition(Vec2 vec)
{
	_healthBar->setPosition(vec);
}

bool HelloWorld::checkScaleDificulty()
{

	if(_scaleDificulty >= 500.0f)
	{ 
		_scaleDificulty = 0;
		return true;
	}
	else
	{
		return false;
	}
}

bool HelloWorld::checkScaleSpeedBG()
{
	if (_scaleSpeedBG >= 50)
	{
		_scaleSpeedBG = 0;
		return true;
	}
	else
	{
		return false;
	}

}


