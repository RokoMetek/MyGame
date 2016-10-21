#include "Enemies.h"



Enemies::Enemies()
{
	_moveType = 0;
	//_offset = 0;
	_shootType = 0;
}

Enemies::Enemies(Layer * layer)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	//Test Models ships
	int shipIndex = RandomHelper::random_int(1, 4);
	//shipIndex = 4;
	auto shipStringOBJ = __String::createWithFormat(SPACESHIP_OBJECT, shipIndex, shipIndex)->getCString();
	auto shipStringMATERIALS = __String::createWithFormat(SPACESHIP_MATERIALS, shipIndex, shipIndex)->getCString();
	_spr3D = Sprite3D::create(shipStringOBJ, shipStringMATERIALS);
	_spr3D->setScale(8);
	_spr3D->setRotation3D(Vec3(0, 180, 180));

	


	//SetPhysic body of 3DModels
	_body = cocos2d::PhysicsBody::createCircle(_spr3D->getContentSize().height / 2);
	_body->setCollisionBitmask(COLLISION_ENEMY);
	_body->setContactTestBitmask(1);
	_body->setDynamic(false);


	auto physicsNode = Node::create();
	_spr3D->addChild(physicsNode);
	physicsNode->setAnchorPoint(_spr3D->getAnchorPoint());
	physicsNode->setPhysicsBody(_body);

	//Set player at botom of scene
	_spr3D->setPosition(0, 0);


	StarShipStats::setAlive(true);
	StarShipStats::setHp(200);
	StarShipStats::setScore(50);

	layer->addChild(_spr3D);
}


Enemies::~Enemies()
{
}

void Enemies::runEnemies(Layer * layer, int index, int type)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();

	//Test Models ships
	int shipIndex = RandomHelper::random_int(1, 4);
	shipIndex = type;
	auto shipStringOBJ = __String::createWithFormat(SPACESHIP_OBJECT, shipIndex, shipIndex)->getCString();
	auto shipStringMATERIALS = __String::createWithFormat(SPACESHIP_MATERIALS, shipIndex, shipIndex)->getCString();
	_spr3D = Sprite3D::create(shipStringOBJ, shipStringMATERIALS);
	_spr3D->setScale(8);
	_spr3D->setRotation3D(Vec3(0, 180, 180));




	//SetPhysic body of 3DModels
	_body = cocos2d::PhysicsBody::createCircle(_spr3D->getContentSize().height / 2);
	_body->setCollisionBitmask(COLLISION_ENEMY);
	_body->setContactTestBitmask(1);
	_body->setDynamic(false);
	_body->setTag(index);


	auto physicsNode = Node::create();
	_spr3D->addChild(physicsNode);
	physicsNode->setAnchorPoint(_spr3D->getAnchorPoint());
	physicsNode->setPhysicsBody(_body);

	//Set player at botom of scene
	_spr3D->setPosition(0, 0);


	StarShipStats::setAlive(true);
	StarShipStats::setHp(200);
	StarShipStats::setScore(50);

	layer->addChild(_spr3D);
}

void Enemies::resetEnemies()
{
	
	this->unscheduleUpdate();
	_spr3D->stopAllActions();
	_spr3D->removeAllChildren();
	_spr3D->removeFromParentAndCleanup(true);
	StarShipStats::setAlive(false);
	log("Enemy deleted");
}

void Enemies::movementMode(int tipMove)
{
	switch (tipMove)
	{
	//Action move forward
	case moveType::move1:
	{		

		
		this->getSpr3D()->setPositionY(460);
		this->getSpr3D()->setPositionX(RandomHelper::random_int(-250, 250));

		auto randYEnd = RandomHelper::random_int(0, 400);


		Action *movementMode = EaseIn::create(MoveTo::create(2.0, Vec2(this->getSpr3D()->getPosition().x, 2*(-ENEMY_TOP_OUT_BORDER) + this->getSpr3D()->getPosition().y)), 2.0);
		Action *moveStart = MoveTo::create(2.0, Vec2(this->getSpr3D()->getPosition().x, randYEnd));
		//MoveTo::create(2.0, Vec2(this->getSpr3D()->getPosition().x, (-ENEMY_TOP_OUT_BORDER) + this->getSpr3D()->getPosition().y + 230)),
		Sequence *seq = Sequence::create(	MoveTo::create(2.0, Vec2(this->getSpr3D()->getPosition().x, randYEnd)),
											DelayTime::create(1.0),
											RotateBy::create(0.5, Vec3(15, 0, 0)),
											DelayTime::create(0.5),
											Spawn::create(	
															RotateBy::create(2.75, Vec3(0,720,0)),
															movementMode,
				
												NULL),
											CallFunc::create(CC_CALLBACK_0(Enemies::resetEnemies, this)), 
											NULL);

		this->getSpr3D()->runAction(seq);
	}
		break;

	//Action move triangle
	case moveType::move2:
	{


		int randomPosY = RandomHelper::random_int(0, 440);
		int randomPrefix = RandomHelper::random_int(-1, 1);
		if (randomPrefix >= 0)
		{
			randomPrefix = 1;
		}
		this->getSpr3D()->setPosition(Vec2(-randomPrefix * (300) , randomPosY));
		//int test1 = this->getSpr3D()->getPosition().x;
		//Action *movementMode = MoveTo::create(5.0, Vec2(this->_offset + this->getSpr3D()->getPosition().x + offset, this->getSpr3D()->getPosition().y));
		Action *movementMode = MoveTo::create(5.0, Vec2(randomPrefix*(300+50), this->getSpr3D()->getPositionY()));


		Sequence *seq = Sequence::create(	Spawn::create(
														RotateBy::create(1.0, Vec3(0, randomPrefix * -30, 0)),
														movementMode,
														NULL),
											CallFunc::create(CC_CALLBACK_0(Enemies::resetEnemies, this)),
											//RotateBy::create(1.0, Vec3(0, randomPrefix * 30, 0)),
											NULL);


		this->getSpr3D()->runAction(seq);

	}
		break;

	//Action move bezier
	case moveType::move3:
	{
		this->getSpr3D()->setScale(10);
		



		int randY = RandomHelper::random_int(-100, 400);
		int randStartPos = RandomHelper::random_int(-1, 1);
		if (randStartPos >= 0)
		{
			randStartPos = 1;
		}
		
		

		this->getSpr3D()->setPosition(randStartPos * 400, 400);
		auto action1 = RotateBy::create(2.5, Vec3(0, randStartPos*25, 0));
		auto action2 = RotateBy::create(1.5, Vec3(0, randStartPos*-50, 0));



		int randomBezierX = RandomHelper::random_int(0, 300);
		int randomBezierY = RandomHelper::random_int(0, 460);


		ccBezierConfig *bezierConfig = new ccBezierConfig();
		
		bezierConfig->controlPoint_1.setPoint(randomBezierX, -randomBezierY);
		bezierConfig->controlPoint_2.setPoint(-randomBezierX, randomBezierY);
		bezierConfig->endPosition.setPoint(-(randStartPos )*400, randY);

		auto action3 = BezierTo::create(5.0, *bezierConfig);
		auto seq1 = Sequence::create(action1, action2, NULL);

		
		auto seq2 = Sequence::create(Spawn::create(
													seq1,
													action3,
													NULL),
									 CallFunc::create(CC_CALLBACK_0(Enemies::resetEnemies, this)),
									 NULL);

		this->getSpr3D()->runAction(seq2);

	}
		break;

	//Action spawnIn
	case moveType::move4:
	{
		this->setScale(2);

		int randomSelector = RandomHelper::random_int(1, 3);

		int finishPosX = RandomHelper::random_int(DESIGN_LEFT_BORDER + 60, DESIGN_RIGHT_BORDER - 60);
		int finishPosY = RandomHelper::random_int(DESIGN_CENTER_BORDER + 100, DESIGN_TOP_BORDER - 60);

		//Actions
		auto ac1 = EaseBackIn::create(MoveTo::create(2.0, Vec2(finishPosX, finishPosY)));
		auto ac2 = RotateBy::create(2.0, Vec3(720, 360, 360));
		auto ac3 = ScaleTo::create(2.0, 10.0);
		auto spawn1 = Spawn::create(ac2, ac3, NULL);
		auto seq = Sequence::create(ac1, spawn1, NULL);

			switch (randomSelector)
			{
					//Top Spawn
				case 1:
				{
					int randX = RandomHelper::random_int(DESIGN_LEFT_BORDER - 60, DESIGN_RIGHT_BORDER + 60);
					int posY = ENEMY_TOP_OUT_BORDER;
					this->getSpr3D()->setPosition(Vec2(randX, posY));
				}
				break;
				//Left Spawn
				case 2:
				{
					int randY = RandomHelper::random_int(DESIGN_CENTER_BORDER - 100, DESIGN_TOP_BORDER + 60);
					int posX = ENEMY_LEFT_OUT_BORDER;
					this->getSpr3D()->setPosition(Vec2(posX, randY));

				}
				break;
				//Right Spawn
				case 3:
				{
					int randY = RandomHelper::random_int(DESIGN_CENTER_BORDER - 100, DESIGN_TOP_BORDER + 60);
					int posX = ENEMY_RIGHT_OUT_BORDER;
					this->getSpr3D()->setPosition(Vec2(posX, randY));

				}
				break;
				default:
					break;
			}

		this->getSpr3D()->runAction(seq);



	}

		break;
	default:
		break;
	}

}

void Enemies::displayExplosion(Layer * layer)
{

	SpriteBatchNode* spritebatch = SpriteBatchNode::create("explosions.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("explosions.plist");

	auto Sprite1 = Sprite::createWithSpriteFrameName("explosionsA_1.png");
	Sprite1->setPosition(this->getSpr3D()->getPosition());

	spritebatch->addChild(Sprite1);

	//spritebatch->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//spritebatch->setPosition(this->getSpr()->getPosition());

	Vector<SpriteFrame*> animFrames(10);

	char str[100] = { 0 };
	for (int i = 1; i < 17; i++)
	{
		sprintf(str, "explosionsA_%d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);

		animFrames.insert(i - 1, frame);
	}

	auto removeSelf = RemoveSelf::create();
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.02f);

	Sprite1->runAction(Sequence::create(Animate::create(animation), removeSelf, nullptr));

	layer->addChild(spritebatch, 2);

	
	auto explosion = ParticleSystemQuad::create("Particles/toonSmoke.plist");
	explosion->setPosition(this->getSpr3D()->getPosition());
	explosion->setAutoRemoveOnFinish(true);
	layer->addChild(explosion, 1);
	
}


