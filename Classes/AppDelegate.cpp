#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"
#include "GameConfig.h"
#include "Definitions.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

	int height, width;
	height = 800;
	width = (height*(640.0 / 960.0));

	/*
	int height, width;
	height = 640;
	width = 960;
	*/
	
	
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        //glview = GLViewImpl::createWithRect("MyGame", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
		glview = GLViewImpl::createWithRect("MyGame", cocos2d::Rect(0, 0, width, height));
#else
        glview = GLViewImpl::create("MyGame");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    //glview->setDesignResolutionSize(width, height, ResolutionPolicy::NO_BORDER);
	glview->setDesignResolutionSize(640, 960, ResolutionPolicy::SHOW_ALL);
	//glview->setDesignResolutionSize(width, height, ResolutionPolicy::NO_BORDER);


	/*
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
	*/

    register_all_packages();


	//PRELOAD RESOURCES
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(ASTEROID_SPRITESHEET, ASTEROID_PNG);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BULLETS_SPRITESHEET, BULLETS_PNG);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("explosions.plist", "explosions.png");


	

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUND_SOUND_INTRO);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(BACKGROUND_SOUND_GAME);
	
	experimental::AudioEngine::preload(SOUND_EFFECT_LASERSHOOT);
	experimental::AudioEngine::preload(SOUND_EFFECT_EXPLOSION1);
	experimental::AudioEngine::preload(SOUND_EFFECT_EXPLOSION2);
	experimental::AudioEngine::preload(SOUND_EFFECT_EXPLOSION3);
	experimental::AudioEngine::preload(SOUND_EFFECT_BULLETIMPACT);

	
	

	/*
	auto Audio = CocosDenshion::SimpleAudioEngine::getInstance();
	Audio->playBackgroundMusic("Audio/Intro.mp3", true);
	*/

    // create a scene. it's an autorelease object
	auto scene = MainMenuScene::createScene();

    // run
    director->runWithScene(scene);
	glEnable(GL_CULL_FACE);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
