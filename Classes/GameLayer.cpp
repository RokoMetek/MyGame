#include "GameLayer.h"
#include "PauseScene.h"
#include "GameEntity.h"
#include "Box2D\Box2D.h"
#include "Definitions.h"
#include "Meteor.h"
#include "PPlayer.h"
#include "Bullets.h"
#include "ui\CocosGUI.h"
#include "Enemies.h"
#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "AudioEngine.h"


USING_NS_CC;
using namespace std;



/*
cocos2d::Scene * GameLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameLayer::create();
	layer->setName("GameLayer");


	// add layer as a child to scene
	scene->addChild(layer, 2, layer->getName());
	

	return scene;

}
*/


bool GameLayer::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
	
	/*
	auto pauseItem =MenuItemImage::create("pause_button.png", "pause_button.png", CC_CALLBACK_1(GameLayer::GoToPauseScene, this));
	pauseItem->setScale(0.5);
	
	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Vec2(visibleSize.width / 2 - pauseItem->getContentSize().width + 100, visibleSize.height / 2 - pauseItem->getContentSize().width + 100));
	this->addChild(menu);
	*/


	//Contac collision listener
	///////////////////////////////////////////////////////////////////////////////////////////
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	/////////////////////////////////////////////////////////////////////////////////////////////
	


	//Player init
	////////////////////////////////////////////////////////////////////////////////////////////////
	_player = new PPlayer(this);
	schedule(schedule_selector(GameLayer::playerUpdate));
	//////////////////////////////////////////////////////////////////////////////////////////////////
	

	this->reserveContainer();

	
	//Meteors spawn
	////////////////////////////////////////////////////////////////////////////////
	//schedule(schedule_selector(GameLayer::spawnMeteor), 0.35, -1, 0.5);
	///////////////////////////////////////////////////////////////////////////////

	//Bullet shoot
	///////////////////////////////////////////////////////////////////////////////
	schedule(schedule_selector(GameLayer::shootPlayerBullets), 0.4, -1, 0);
	schedule(schedule_selector(GameLayer::shootEnemyBullets), 0.1, -1, 0);
	/////////////////////////////////////////////////////////////////////////////


	//Spawn enemy
	///////////////////////////////////////////////////////////////////////////////
	//schedule(schedule_selector(GameLayer::spawnEnemy), 4.0, -1, 0);
	//schedule(schedule_selector(GameLayer::spawnEnemy2), 5.0, -1, 0);
	/////////////////////////////////////////////////////////////////////////////


							
	
	/*
	auto explosion = ParticleSystemQuad::create("Particles/Booster.plist");
	//explosion->setPosition(Vec2(0, 0));
	explosion->setPosition(_player->getSpr3D()->getPosition());
	explosion->setScale(1.5);
	//explosion->setRotation(90);
	explosion->setDuration(10);
	explosion->setAutoRemoveOnFinish(true);
	this->addChild(explosion);
	*/


	//Enemies *enemySpawnIn = new Enemies(this);
	//enemySpawnIn->getSpr3D()->setPosition(0, 0);
	//enemySpawnIn->setMoveType(moveType::move3);
	//enemySpawnIn->movementMode(enemySpawnIn->getMoveType(), 0);

	//Bezier Move Spawn
	/*
	Enemies *enemySpawnIn = new Enemies(this);
	float ss = enemySpawnIn->getSpr3D()->getRotation3D().x;
	enemySpawnIn->getSpr3D()->setScale(10);
	enemySpawnIn->getSpr3D()->setPosition(400, 400);
	auto ac1 = RotateBy::create(2.5, Vec3(0, 25, 0));
	auto ac4 = RotateBy::create(2.5, Vec3(0, -50, 0));

	
	int randY = RandomHelper::random_int(0, 400);


	ccBezierConfig *beziConfig = new ccBezierConfig();

	beziConfig->controlPoint_1.setPoint(0, -10);
	beziConfig->controlPoint_2.setPoint(0, -10);

	//beziConfig->controlPoint_1 = Vec2(0, -10);
	//beziConfig->controlPoint_1 = Vec2(0, -10);

	beziConfig->endPosition = Vec2(-400, randY);
	BezierBy *bez1 = BezierTo::create(5.0, *beziConfig);

	Sequence *seq2 = Sequence::create(ac4, ac1, NULL);
	Sequence *seq = Sequence::create(	Spawn::create(
														seq2,
														bez1,	
														NULL),
										NULL);
	enemySpawnIn->getSpr3D()->runAction(seq);
	*/

 
	/*
	Enemies *enemySpawn1 = new Enemies(this);
	enemySpawn1->setMoveType(moveType::move4);
	enemySpawn1->movementMode(enemySpawn1->getMoveType(), 0);


	Enemies *enemySpawn2 = new Enemies(this);
	enemySpawn2->setMoveType(moveType::move3);
	enemySpawn2->movementMode(enemySpawn2->getMoveType(), 0);
	*/

	//Fly In spawn
	/*
	Enemies *enemySpawnIn = new Enemies(this);
	enemySpawnIn->getSpr3D()->setScale(2);
	int spawnPos = RandomHelper::random_int(1, 3);


	int finishPosX = RandomHelper::random_int(DESIGN_LEFT_BORDER + 60, DESIGN_RIGHT_BORDER - 60);
	int finishPosY = RandomHelper::random_int(DESIGN_CENTER_BORDER + 100, DESIGN_TOP_BORDER - 60);
	auto ac1 = EaseBackIn::create(MoveTo::create(2.0, Vec2(finishPosX, finishPosY)));
	auto ac2 = RotateBy::create(2.0, Vec3(720, 360, 360));
	auto ac3 = ScaleTo::create(2.0, 10.0);

	auto spawn1 = Spawn::create(ac2, ac3, NULL);

	auto seq = Sequence::create(ac1, spawn1, NULL);



	switch (spawnPos)
	{
	//Top Spawn
	case 1:
	{
		int randX = RandomHelper::random_int(DESIGN_LEFT_BORDER - 60, DESIGN_RIGHT_BORDER + 60);
		int posY = ENEMY_TOP_OUT_BORDER;
		enemySpawnIn->getSpr3D()->setPosition(Vec2(randX, posY));
	}
		break;
	//Left Spawn
	case 2:
	{
		int randY = RandomHelper::random_int(DESIGN_CENTER_BORDER  -100, DESIGN_TOP_BORDER + 60);
		int posX = ENEMY_LEFT_OUT_BORDER;
		enemySpawnIn->getSpr3D()->setPosition(Vec2(posX, randY));

	}
		break;
	//Right Spawn
	case 3:
	{
		int randY = RandomHelper::random_int(DESIGN_CENTER_BORDER -100, DESIGN_TOP_BORDER + 60);
		int posX = ENEMY_RIGHT_OUT_BORDER;
		enemySpawnIn->getSpr3D()->setPosition(Vec2(posX, randY));

	}
		break;
	default:
		break;
	}

	enemySpawnIn->getSpr3D()->runAction(seq);
	*/

	//Test waves
	
	/*
	auto spawn = CallFunc::create(CC_CALLBACK_0(GameLayer::spawnEnemy3, this, 1));
	auto delay = DelayTime::create(0.5);
	auto sekvenca = Sequence::create(spawn, delay, nullptr);
	auto repeat = Repeat::create(sekvenca, 5);
	auto runForever = RepeatForever::create(repeat);
	this->runAction(runForever);
	*/


	/*
	Enemies *newEnemy = _enemysContainer.at(_enemyContainerIndex);
	newEnemy->runEnemies(this, _enemyContainerIndex);
	newEnemy->setShootType(shootType::shoot4);

	auto mm = MoveTo::create(3.0, Vec2(200, -300));
	auto dd = DelayTime::create(2.0);
	auto sesa = Sequence::create(dd, mm, nullptr);
	//newEnemy->getSpr3D()->runAction(sesa);
	//EnemyBullet *bullet = new EnemyBullet();
	auto bb = CallFunc::create(CC_CALLBACK_0(GameLayer::shootEnemyBullets, this, 0.1));
	auto delay = DelayTime::create(0.1);
	auto sekv = Sequence::create(bb, delay, nullptr);
	auto repeat = RepeatForever::create(sekv);
	*/
	//this->runAction(repeat);
	
	//bullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(0, -460), 1);

	this->scheduleUpdate();

	return true;
}


void GameLayer::GoToPauseScene(Ref * pSender)
{

	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(scene);
}

/*
void GameLayer::GoToGameOverScene()
{
	auto scene = GameOverScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
*/

//GameLayer update function
void GameLayer::update(float dt)
{
	//Get visibleSize, origin and winSize
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();


	_elapsedTime += dt;

	//Meteor spawn
	if (_player->getAlive())
	{
		_timerMeteor += dt;
		if (_timerMeteor > _frequencyMeteor)
		{
			_timerMeteor = 0;
			this->spawnMeteor(dt);
		}

		//Enemy spawn
		_timerEnemy += dt;
		if (_timerEnemy > _frequencyEnemy)
		{

			int randWave = RandomHelper::random_int(1, 6);
			//randWave = 5;
			_timerEnemy = 0;
			//this->spawnEnemy3(dt);
			enemyWave(randWave);
		}


		//scaleDifficulty();
	}
	else
	{
		safeRemoveAll();
		log("Player dead");
	}

	


}


//Shoting bullets
void GameLayer::shootPlayerBullets(float dt)
{
	experimental::AudioEngine::play2d(SOUND_EFFECT_LASERSHOOT, false, 0.1);
	auto bullet = _bulletsContainer.at(_bulletContainerIndex);
	bullet->startBullet(this, _player, _bulletContainerIndex);
	auto Audio = CocosDenshion::SimpleAudioEngine::getInstance();
	//Audio->playEffect(SOUND_EFFECT_LASERSHOOT,false,1.0f,0.0f,0.2f);

	//bullet->scheduleUpdate();

	Director::getInstance()->getScheduler()->scheduleUpdate(bullet, 0, false);


	_bulletContainerIndex++;
	if (_bulletContainerIndex == _bulletsContainer.size())
		_bulletContainerIndex = 0;

}

void GameLayer::shootEnemyBullets(float dt)
{
	

	_timerBulletE1 += dt;
	_timerBulletE2 += dt;
	_timerBulletE3 += dt;
	_timerBulletE4 += dt;
	

	if (_timerBulletE1 > 2.0)
		_timerBulletE1 = 0;

	if (_timerBulletE2 > 1.3)
		_timerBulletE2 = 0;

	if (_timerBulletE3 > 1.5)
		_timerBulletE3 = 0;

	if (_timerBulletE4 > 10.4)
		_timerBulletE4 = 0;
	

	for (int i = 0; i < _enemysContainer.size(); i++)
	{
		if (_enemysContainer.at(i)->getAlive())
		{
			Enemies *newEnemy = _enemysContainer.at(i);
			
			switch (newEnemy->getShootType())
			{
			case shootType::shoot1:
			{
				if (_timerBulletE1 >= 1.0 && _timerBulletE1 < 1.3)
				{
					EnemyBullet *newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
					auto offX = RandomHelper::random_int(-300, 300);
					//newBullet->startBullet(this, _enemysContainer.at(i)->getSpr3D()->getPosition(), Vec2(_enemysContainer.at(i)->getSpr3D()->getPosition().x, -460), _enemyBulletContainerIndex);
					newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(offX, -460), _enemyBulletContainerIndex);

					_enemyBulletContainerIndex++;

					if (_enemyBulletContainerIndex == 1000)
					{
						_enemyBulletContainerIndex = 0;
					}
					Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
				}
			}
			break;
			case shootType::shoot2:
			{
				if (_timerBulletE2 >= 1.0 && _timerBulletE2 < 1.1)
				{
					for (int i = 0, prefix = -2; i < 5; i++, prefix++)
					{

						EnemyBullet *newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 160 * prefix, -460), _enemyBulletContainerIndex);


						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

				}

			}
			break;
			case shootType::shoot3:
			{

				if (_timerBulletE3 >= 0.5)
				{
					//Prvi val
					if(_timerBulletE3 >= 0.5 && _timerBulletE3 < 0.6)
					{
						EnemyBullet *newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition() + Vec2(0, 0), Vec2(newEnemy->getSpr3D()->getPosition().x - 25, newEnemy->getSpr3D()->getPosition().y - 2* 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}
					if (_timerBulletE3 >= 0.7 && _timerBulletE3 < 0.8)
					{
						EnemyBullet *newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition() + Vec2(0, 0), Vec2(newEnemy->getSpr3D()->getPosition().x - 0, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}
					if (_timerBulletE3 >= 0.9 && _timerBulletE3 < 1.0)
					{
						EnemyBullet *newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition() + Vec2(0, 0), Vec2(newEnemy->getSpr3D()->getPosition().x + 25, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

					//Drugi Val
					if (_timerBulletE3 >= 1.1 && _timerBulletE3 < 1.2)
					{
						EnemyBullet *newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition() + Vec2(0, 0), Vec2(newEnemy->getSpr3D()->getPosition().x + 0, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}
					if (_timerBulletE3 >= 1.3 && _timerBulletE3 < 1.4)
					{
						EnemyBullet *newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition() + Vec2(0, 0), Vec2(newEnemy->getSpr3D()->getPosition().x - 25, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

				}

			}
			break;
			case shootType::shoot4:
			{

				if (_timerBulletE4 >= 1.0 && _timerBulletE4 < 10.4)
				{
					EnemyBullet *newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);


					//Gornji ljevi
					///////////////////////////////////////////////////////////////////////////////
					if (_timerBulletE4 >= 1.0 && _timerBulletE4 < 1.1)
					{
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 0, newEnemy->getSpr3D()->getPosition().y + 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 1.3 && _timerBulletE4 < 1.4)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 75, newEnemy->getSpr3D()->getPosition().y + 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

					else if (_timerBulletE4 >= 1.6 && _timerBulletE4 < 1.7)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 150, newEnemy->getSpr3D()->getPosition().y + 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 1.9 && _timerBulletE4 < 2.0)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 225, newEnemy->getSpr3D()->getPosition().y + 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

					else if (_timerBulletE4 >= 2.2 && _timerBulletE4 < 2.29)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 300, newEnemy->getSpr3D()->getPosition().y + 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



					//ljevi kut
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					else if (_timerBulletE4 >= 2.5 && _timerBulletE4 < 2.6)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 300, newEnemy->getSpr3D()->getPosition().y + 2 * 345), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 2.8 && _timerBulletE4 < 2.9)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 300, newEnemy->getSpr3D()->getPosition().y + 2 * 230), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 3.1 && _timerBulletE4 < 3.2)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 300, newEnemy->getSpr3D()->getPosition().y + 2 * 115), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 3.4 && _timerBulletE4 < 3.5)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 300, newEnemy->getSpr3D()->getPosition().y + 2 * 0), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					else if (_timerBulletE4 >= 3.7 && _timerBulletE4 < 3.8)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 300, newEnemy->getSpr3D()->getPosition().y - 2 * 115), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

					else if (_timerBulletE4 >= 4.0 && _timerBulletE4 < 4.1)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 300, newEnemy->getSpr3D()->getPosition().y - 2 * 230), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 4.3 && _timerBulletE4 < 4.4)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 300, newEnemy->getSpr3D()->getPosition().y - 2 * 345), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 4.6 && _timerBulletE4 < 4.7)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 300, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					else if (_timerBulletE4 >= 4.9 && _timerBulletE4 < 5.0)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 225, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

					else if (_timerBulletE4 >= 5.2 && _timerBulletE4 < 5.3)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 150, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

					else if (_timerBulletE4 >= 5.5 && _timerBulletE4 < 5.6)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 75, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 5.8 && _timerBulletE4 < 5.9)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x - 2 * 0, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					else if (_timerBulletE4 >= 6.1 && _timerBulletE4 < 6.2)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 75, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 6.4 && _timerBulletE4 < 6.5)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 150, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 6.7 && _timerBulletE4 < 6.8)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 225, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 7.0 && _timerBulletE4 < 7.1)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 300, newEnemy->getSpr3D()->getPosition().y - 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					else if (_timerBulletE4 >= 7.3 && _timerBulletE4 < 7.4)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 300, newEnemy->getSpr3D()->getPosition().y - 2 * 345), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

					else if (_timerBulletE4 >= 7.6 && _timerBulletE4 < 7.7)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 300, newEnemy->getSpr3D()->getPosition().y - 2 * 230), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

					else if (_timerBulletE4 >= 7.9 && _timerBulletE4 < 8.0)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 300, newEnemy->getSpr3D()->getPosition().y - 2 * 115), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

					else if (_timerBulletE4 >= 8.2 && _timerBulletE4 < 8.3)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 300, newEnemy->getSpr3D()->getPosition().y - 2 * 0), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					
					else if (_timerBulletE4 >= 8.5 && _timerBulletE4 < 8.6)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 300, newEnemy->getSpr3D()->getPosition().y + 2 * 115), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}



					else if (_timerBulletE4 >= 8.8 && _timerBulletE4 < 8.9)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 300, newEnemy->getSpr3D()->getPosition().y + 2 * 230), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 9.1 && _timerBulletE4 < 9.2)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 300, newEnemy->getSpr3D()->getPosition().y + 2 * 345), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}


					else if (_timerBulletE4 >= 9.4 && _timerBulletE4 <= 9.5)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 300, newEnemy->getSpr3D()->getPosition().y + 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					else if (_timerBulletE4 >= 9.7 && _timerBulletE4 < 9.8)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 225, newEnemy->getSpr3D()->getPosition().y + 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

					else if (_timerBulletE4 >= 10.0 && _timerBulletE4 < 10.1)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 150, newEnemy->getSpr3D()->getPosition().y + 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}

					else if (_timerBulletE4 >= 10.3 && _timerBulletE4 < 10.4)
					{
						newBullet = _enemyBulletsContainer.at(_enemyBulletContainerIndex);
						newBullet->startBullet(this, newEnemy->getSpr3D()->getPosition(), Vec2(newEnemy->getSpr3D()->getPosition().x + 2 * 75, newEnemy->getSpr3D()->getPosition().y + 2 * 460), _enemyBulletContainerIndex);
						_enemyBulletContainerIndex++;
						if (_enemyBulletContainerIndex == 1000)
						{
							_enemyBulletContainerIndex = 0;
						}
						Director::getInstance()->getScheduler()->scheduleUpdate(newBullet, 0, false);
					}
					/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}


			}
			break;
			default:
				break;
			}
		}
	}
}


//Player Update
void GameLayer::playerUpdate(float dt)
{
	
	_player->targetRollUpdate(dt);
}

void GameLayer::spawnMeteor(float dt)
{

	Meteor *newMeteor = _meteorsContainer.at(_meteorContainerIndex);
	newMeteor->runMeteor(this, _meteorContainerIndex, _speedMeteor);
	_meteorContainerIndex++;

	Director::getInstance()->getScheduler()->scheduleUpdate(newMeteor, 0, false);


	if (_meteorContainerIndex == _meteorsContainer.size())
	{
		_meteorContainerIndex = 0;
	}
		
}


void GameLayer::spawnEnemy3(int enemySpawnType)
{

	Enemies *newEnemy = _enemysContainer.at(_enemyContainerIndex);

	switch (enemySpawnType)
	{
	case 1:
	{

		//Spawn down
		int randomType = RandomHelper::random_int(3, 4);
		newEnemy->runEnemies(this, _enemyContainerIndex, randomType);
		newEnemy->setShootType(shootType::shoot3);
		newEnemy->setMoveType(moveType::move1);
		
	}
	break;
	case 2:
	{
		//Spawn sideway
		int randomType = RandomHelper::random_int(1, 2);
		newEnemy->runEnemies(this, _enemyContainerIndex, 1);
		newEnemy->setShootType(shootType::shoot1);
		newEnemy->setMoveType(moveType::move2);
		
	}
	break;
	case 3:
	{
		//Bezier Spawn
		int randomType = RandomHelper::random_int(1, 2);
		newEnemy->runEnemies(this, _enemyContainerIndex, 1);
		newEnemy->setShootType(shootType::shoot2);
		newEnemy->setMoveType(moveType::move3);
	}
	break;
	case 4:
	{
		//Fly in spawn
		int randomType = RandomHelper::random_int(3, 4);
		newEnemy->runEnemies(this, _enemyContainerIndex, randomType);
		newEnemy->setShootType(shootType::shoot4);
		newEnemy->setMoveType(moveType::move4);
	}
	break;
	default:
		break;
	}

	_enemyContainerIndex++;
	newEnemy->movementMode(newEnemy->getMoveType());

	if (_enemyContainerIndex == 50)
	{
		_enemyContainerIndex = 0;
	}

}

void GameLayer::enemyWave(int type)
{
	switch (type)
	{
	case 1:
	{
		//Type sideway
		int randPrefix = RandomHelper::random_int(-1, 1);
		if (randPrefix == 0)
		{
			randPrefix = 1;
		}

		int endPositionX = 350;
		int posY = RandomHelper::random_int(0, 460);
		int posX = randPrefix * endPositionX;

		

		Enemies *newEnemyLeader = _enemysContainer.at(_enemyContainerIndex);

		int randomType = RandomHelper::random_int(2, 4);
		newEnemyLeader->runEnemies(this, _enemyContainerIndex, randomType);
		newEnemyLeader->getSpr3D()->setPosition(Vec2(-posX, posY));
		newEnemyLeader->getSpr3D()->setScale(6);

		_enemyContainerIndex++;
		if (_enemyContainerIndex == 50)
		{
			_enemyContainerIndex = 0;
		}

		float time = timeToPoint(Vec2(randPrefix * endPositionX, newEnemyLeader->getSpr3D()->getPosition().y), newEnemyLeader->getSpr3D()->getPosition(), 100);
		auto actionMoveTo = MoveTo::create(time, Vec2(randPrefix * endPositionX, newEnemyLeader->getSpr3D()->getPosition().y));
		auto sekvenca1 = Sequence::create(actionMoveTo,
			CallFunc::create(CC_CALLBACK_0(Enemies::resetEnemies, newEnemyLeader)),
			nullptr);

		newEnemyLeader->getSpr3D()->runAction(sekvenca1);
		



		for (int i = 0; i < 3; i++)
		{
			Enemies *newEnemy = _enemysContainer.at(_enemyContainerIndex);
			newEnemy->runEnemies(this, _enemyContainerIndex, randomType);
			newEnemy->getSpr3D()->setPosition(Vec2(newEnemyLeader->getSpr3D()->getPosition().x - (i+1)*75*randPrefix, newEnemyLeader->getSpr3D()->getPosition().y));
			newEnemy->getSpr3D()->setScale(6);


			_enemyContainerIndex++;
			if (_enemyContainerIndex == 50)
			{
				_enemyContainerIndex = 0;
			}

			time = timeToPoint(Vec2(randPrefix * endPositionX, newEnemy->getSpr3D()->getPosition().y), newEnemy->getSpr3D()->getPosition(), 100);
			auto actionMoveToFollower = MoveTo::create(time, Vec2(randPrefix * endPositionX, newEnemy->getSpr3D()->getPosition().y));
			auto sekvenca2 = Sequence::create(actionMoveToFollower,
				CallFunc::create(CC_CALLBACK_0(Enemies::resetEnemies, newEnemy)),
				nullptr);

			newEnemy->getSpr3D()->runAction(sekvenca2);
		}

	}
	break;
	case 2:
	{

		//Triangle
		int endPosY = -500;
		int posX = RandomHelper::random_int(-150, 150);
		int posY = 460;
		int randomType = RandomHelper::random_int(2, 4);

		Enemies *newEnemyLeader = _enemysContainer.at(_enemyContainerIndex);
		newEnemyLeader->runEnemies(this, _enemyContainerIndex, randomType);
		newEnemyLeader->getSpr3D()->setPosition(Vec2(posX, posY));
		newEnemyLeader->getSpr3D()->setScale(6);

		newEnemyLeader->setShootType(shootType::shoot2);

		_enemyContainerIndex++;
		if (_enemyContainerIndex == 50)
		{
			_enemyContainerIndex = 0;
		}


		float time = timeToPoint(Vec2(newEnemyLeader->getSpr3D()->getPosition().x, endPosY), newEnemyLeader->getSpr3D()->getPosition(), 200);
		auto actionMoveTo = MoveTo::create(time, Vec2(newEnemyLeader->getSpr3D()->getPosition().x, endPosY));


		auto sekvenca1 = Sequence::create(actionMoveTo,
			CallFunc::create(CC_CALLBACK_0(Enemies::resetEnemies, newEnemyLeader)),
			nullptr);
		newEnemyLeader->getSpr3D()->runAction(sekvenca1);

		for (int i = 0, smjer = -1; i < 2; i++, smjer +=2)
		{

			for (int j = 0; j < 2; j++)
			{
				Enemies *newEnemy = _enemysContainer.at(_enemyContainerIndex);
				newEnemy->runEnemies(this, _enemyContainerIndex, 1);
				newEnemy->getSpr3D()->setPosition(Vec2(newEnemyLeader->getSpr3D()->getPosition().x + (j+1) * 65 * smjer, newEnemyLeader->getSpr3D()->getPosition().y + (j+1) * 50));
				newEnemy->getSpr3D()->setScale(6);
				
				newEnemy->setShootType(-1);

				_enemyContainerIndex++;
				if (_enemyContainerIndex == 50)
				{
					_enemyContainerIndex = 0;
				}

				time = timeToPoint(Vec2(newEnemy->getSpr3D()->getPosition().x, endPosY), newEnemy->getSpr3D()->getPosition(), 200);
				auto actionMoveToFollower = MoveTo::create(time, Vec2(newEnemy->getSpr3D()->getPosition().x, endPosY));
				auto sekvenca2 = Sequence::create(actionMoveToFollower,
					CallFunc::create(CC_CALLBACK_0(Enemies::resetEnemies, newEnemy)),
					nullptr);
				newEnemy->getSpr3D()->runAction(sekvenca2);

			}

		}


	}
	break;
	case 3:
	{
		auto callSpawn = CallFunc::create(CC_CALLBACK_0(GameLayer::spawnEnemy3, this, 1));
		auto delay = DelayTime::create(0.3);
		auto sekvenca = Sequence::create(callSpawn, delay, nullptr);
		auto repeatSekvenca = Repeat::create(sekvenca, 4);
		this->runAction(repeatSekvenca);

	}
	break;
	case 4:
	{
		auto callSpawn = CallFunc::create(CC_CALLBACK_0(GameLayer::spawnEnemy3, this, 2));
		auto delay = DelayTime::create(0.3);
		auto sekvenca = Sequence::create(callSpawn, delay, nullptr);
		auto repeatSekvenca = Repeat::create(sekvenca, 4);
		this->runAction(repeatSekvenca);

	}
	break;
	case 5:
	{
		auto callSpawn = CallFunc::create(CC_CALLBACK_0(GameLayer::spawnEnemy3, this, 3));
		auto delay = DelayTime::create(0.3);
		auto sekvenca = Sequence::create(callSpawn, delay, nullptr);
		auto repeatSekvenca = Repeat::create(sekvenca, 2);
		this->runAction(repeatSekvenca);

	}
	break;
	case 6:
	{
		auto callSpawn = CallFunc::create(CC_CALLBACK_0(GameLayer::spawnEnemy3, this, 4));
		auto delay = DelayTime::create(0.3);
		auto sekvenca = Sequence::create(callSpawn, delay, nullptr);
		auto repeatSekvenca = Repeat::create(sekvenca, 3);
		this->runAction(repeatSekvenca);

	}
	default:
		break;
	}

}


bool GameLayer::onContactBegin(PhysicsContact & physicContact)
{

	auto bodyA = physicContact.getShapeA()->getBody();
	auto bodyB = physicContact.getShapeB()->getBody();

	auto aBodySprite = static_cast<Sprite *>(bodyA->getNode());
	auto bBodySprite = static_cast<Sprite *>(bodyB->getNode());



	//Colision Player->Meteor <-> Meteor->Player
	if (aBodySprite && bBodySprite && COLLISION_PLAYER == bodyA->getCollisionBitmask() && COLLISION_METEOR == bodyB->getCollisionBitmask())
	{
		log("Collision bodyA=PLAYER  bodyB=METEOR ");
		meteorCollision(bodyB->getTag());
		//_player->showExplosion(this);
		_player->hurt(_meteorsContainer.at(bodyB->getTag())->damge);

	}
	else if (aBodySprite && bBodySprite && COLLISION_METEOR == bodyA->getCollisionBitmask() && COLLISION_PLAYER == bodyB->getCollisionBitmask())
	{
		log("Collision bodyB=PLAYER bodyA=METEOR");
		meteorCollision(bodyA->getTag());
		//_player->showExplosion(this);
		_player->hurt(_meteorsContainer.at(bodyA->getTag())->damge);
	}


	//Colision Bullet->Meteor <-> Meteor->Bullet
	if (aBodySprite && bBodySprite && COLLISION_BULLET == bodyA->getCollisionBitmask() && COLLISION_METEOR == bodyB->getCollisionBitmask())
	{
		bulletCollision(bodyA->getTag());
		meteorCollision(bodyB->getTag());


		log("Collision BULLET METEOR");

	}
	else if(aBodySprite && bBodySprite && COLLISION_METEOR == bodyA->getCollisionBitmask() && COLLISION_BULLET == bodyB->getCollisionBitmask())
	{
		bulletCollision(bodyB->getTag());
		meteorCollision(bodyA->getTag());


		log("Collision BULLET METEOR");
	}


	//Colision Bullet->Enemy <-> Enemy->Bullet
	if (aBodySprite && bBodySprite && COLLISION_BULLET == bodyA->getCollisionBitmask() && COLLISION_ENEMY == bodyB->getCollisionBitmask())
	{
		log("Collision BULLET ENEMY");
		bulletCollision(bodyA->getTag());
		enemyCollision(bodyB->getTag());

	}
	else if (aBodySprite && bBodySprite && COLLISION_ENEMY == bodyA->getCollisionBitmask() && COLLISION_BULLET == bodyB->getCollisionBitmask())
	{
		log("Collision ENEMY BULLET");
		bulletCollision(bodyB->getTag());
		enemyCollision(bodyA->getTag());
	}

	//Colision EnemyBullet->Player <-> Player->EnemyBullet
	if (aBodySprite && bBodySprite && COLLISION_BULLET_ENEMY == bodyA->getCollisionBitmask() && COLLISION_PLAYER == bodyB->getCollisionBitmask())
	{

		enemyBulletCollision(bodyA->getTag());
		//_player->hurt(_bulletsContainer.at(bodyA->getTag())->getDamge());
		log(" COLLLLLLLLLLLLISOION B - P");

	}
	else if (aBodySprite && bBodySprite && COLLISION_PLAYER == bodyA->getCollisionBitmask() && COLLISION_BULLET_ENEMY == bodyB->getCollisionBitmask())
	{


		enemyBulletCollision(bodyB->getTag());
		//_player->hurt(_bulletsContainer.at(bodyB->getTag())->getDamge());
		log(" COLLLLLLLLLLLLISOION P - B");

	}



	
	return true;
}



void GameLayer::reserveContainer()
{
	_meteorContainerIndex = 0;
	_bulletContainerIndex = 0;
	_enemyContainerIndex = 0;
	_enemyBulletContainerIndex = 0;

	_meteorsContainer.reserve(METEOR_CONTAINER_SIZE);
	_bulletsContainer.reserve(BULLET_CONTAINER_SIZE);
	_enemysContainer.reserve(ENEMY_CONTAINER_SIZE);
	//_enemyBulletsContainer.reserve(ENEMYBULLET_CONTAINER_SIZE);
	_enemyBulletsContainer.reserve(1000);



	for (int i = 0; i < CONTAINER_SIZE; i++)
	{

		_meteorsContainer.pushBack(new Meteor());
		_bulletsContainer.pushBack(new PlayerBullet());
		_enemysContainer.pushBack(new Enemies());
		//_enemyBulletsContainer.pushBack(new EnemyBullet());

	}

	for (int i = 0; i < 1000; i++)
	{
		_enemyBulletsContainer.pushBack(new EnemyBullet());
	}


}

void GameLayer::meteorCollision(int index)
{


	auto newMeteor = _meteorsContainer.at(index);

	if (newMeteor->type == 1 || newMeteor->type == 2)
	{
		//auto Audio = CocosDenshion::SimpleAudioEngine::getInstance();
		//Audio->playEffect(SOUND_EFFECT_EXPLOSION1);
		experimental::AudioEngine::play2d(SOUND_EFFECT_EXPLOSION1, false, 0.5);

		newMeteor->displayExplosion(this);
		auto helloworldLayer = (HelloWorld*)Director::getInstance()->getRunningScene()->getChildByName("HelloWorld");
		helloworldLayer->incrementScore(newMeteor->score);
		newMeteor->resetMeteor();
	}

}

void GameLayer::bulletCollision(int index)
{
	//_bulletsContainer.at(index)->resetBullet();
	Bullets *newBullet = _bulletsContainer.at(index);
	newBullet->getBulletParticle()->removeFromParentAndCleanup(true);
	newBullet->bulletImpact(this);
	newBullet->resetBullet();
}

void GameLayer::enemyCollision(int index)
{
	experimental::AudioEngine::play2d(SOUND_EFFECT_EXPLOSION3, false, 0.2);
	
	Enemies *newEnemy = _enemysContainer.at(index);
	newEnemy->displayExplosion(this);

	auto helloworldLayer = (HelloWorld*)Director::getInstance()->getRunningScene()->getChildByName("HelloWorld");
	helloworldLayer->incrementScore(newEnemy->getScore());

	newEnemy->resetEnemies();
}



void GameLayer::enemyBulletCollision(int index)
{
	experimental::AudioEngine::play2d(SOUND_EFFECT_BULLETIMPACT, false, 0.3);
	EnemyBullet *newBullet = _enemyBulletsContainer.at(index);
	newBullet->bulletImpact(this);
	newBullet->resetBullet();

	_player->hurt(newBullet->getDamge());
}

float GameLayer::timeToPoint(Vec2 endPos, Vec2 startPos, float speed)
{
	float distance = sqrt(pow((endPos.x - startPos.x), 2) + pow((endPos.y - startPos.y), 2)) / speed;
	return distance;
}

void GameLayer::scaleDifficulty()
{
	auto helloworldLayer = (HelloWorld*)Director::getInstance()->getRunningScene()->getChildByName("HelloWorld");
	if (helloworldLayer != nullptr)
	{
		//log("layer obstaja");
		//auto scorePoints = helloworldLayer->getScore();

		//Meteor frekvency spawn
		if (_frequencyMeteor <= 0.15)
		{
			_frequencyMeteor = 0.15;
		}
		else
		{
			_frequencyMeteor -= 0.05;
		}

		//Enemy frekvency spawn
		if (_frequencyEnemy <= 4.0)
		{
			_frequencyEnemy = 4.0;
		}
		else
		{
			_frequencyEnemy -= 1.5;
		}

		//Meteor speed
		if (_speedMeteor <= 0.003)
		{
			_speedMeteor = 0.003;
		}
		else
		{
			_speedMeteor -= 0.001;
		}



	}
}

void GameLayer::scaleBGspeed()
{
	auto helloworldLayer = (HelloWorld*)Director::getInstance()->getRunningScene()->getChildByName("HelloWorld");
	if (helloworldLayer != nullptr)
	{
		if (helloworldLayer->xSpeed >= 1000)
		{
			helloworldLayer->xSpeed = 1000;
		}
		else
		{
			helloworldLayer->xSpeed += 5;
		}
	}

}

void GameLayer::safeRemoveAll()
{

	for (int i = 0; i < 50; i++)
	{
		_meteorsContainer.at(i)->unscheduleUpdate();
		_bulletsContainer.at(i)->unscheduleUpdate();
		_enemysContainer.at(i)->unscheduleUpdate();
	}

	for (int i = 0; i < 1000; i++)
	{
		_enemyBulletsContainer.at(i)->unscheduleUpdate();
	}

	log("Safley remove all");

}




