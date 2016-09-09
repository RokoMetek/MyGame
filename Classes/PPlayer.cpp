#include "PPlayer.h"
#include "GameConfig.h"


const float PPlayer::rollSpeed = 0.5;// recommended 1.5
const float PPlayer::returnSpeed = 8;// recommended 4
const float PPlayer::maxRoll = 60;
const float PPlayer::rollReturnThreshold = 1.02;

PPlayer::PPlayer()
{
}


PPlayer::PPlayer(Layer * layer)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();


	//Test Models ships
	int shipIndex = RandomHelper::random_int(1, 5);
	shipIndex = 5;
	auto shipStringOBJ = __String::createWithFormat(SPACESHIP_OBJECT, shipIndex, shipIndex)->getCString();
	auto shipStringMATERIALS = __String::createWithFormat(SPACESHIP_MATERIALS, shipIndex, shipIndex)->getCString();
	_spr3D = Sprite3D::create(shipStringOBJ, shipStringMATERIALS);
	_spr3D->setScale(120);
	

	//this->setPosition(Vec2(100, 200));
	//_spr3D = Sprite3D::create("Main_starship.c3b", "mappa-base.png")


	//_spr3D->setScale(1.2);
	_spr3D->setPosition(0, -400);

	setRadius(40);
	/*
	setWidth(_spr3D->getContentSize().width);
	setHeight(_spr3D->getContentSize().height);
	setPosX(_spr3D->getPosition().x);
	setPosY(_spr3D->getPosition().y);
	setPos(_spr3D->getPosition());
	*/

	layer->addChild(_spr3D);

	
	//Evnet Listner
	auto listener_mouse2 = EventListenerTouchOneByOne::create();
	listener_mouse2->setSwallowTouches(true);
	listener_mouse2->onTouchBegan = CC_CALLBACK_2(PPlayer::onTouchBegan, this);
	listener_mouse2->onTouchMoved = CC_CALLBACK_2(PPlayer::onTouchMoved, this);
	listener_mouse2->onTouchEnded = CC_CALLBACK_2(PPlayer::onTouchEnded, this);
	layer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_mouse2, layer);
	
}


PPlayer::~PPlayer()
{
}

bool PPlayer::onTouchBegan(Touch * touch, Event * event)
{

	CCLOG("Touch location: x->%f  y->%f", touch->getLocation().x, touch->getLocation().y);

	return true;
}

void PPlayer::onTouchMoved(Touch * touch, Event * event)
{

	Vec2 prev = _spr3D->getPosition();
	Vec2 delta = touch->getDelta();
	
	//Roll 3D models 
	setTargetAngle(targetAngle + 2*delta.x* rollSpeed*(rollReturnThreshold - fabsf(targetAngle) / maxRoll));
	
	//Promjena pozicije
	Vec2 shiftPostion = delta + prev;
	setPosition(shiftPostion.getClampPoint(Vec2(DESIGN_LEFT_BORDER, DESIGN_BOT_BORDER), Vec2(DESIGN_RIGHT_BORDER, DESIGN_TOP_BORDER)));
}

void PPlayer::onTouchEnded(Touch * touch, Event * event)
{
	//Touch ended
}

void PPlayer::setPosition(Vec2 pos)
{
	if (getTargetPos().equals(pos)) {
		return;
	}
	CCLOG("Touch location POSITION: x->%f  y->%f", pos.x, pos.y);
	_spr3D->setPosition(pos);
	setTargetPos(pos);

	_transformUpdated = _transformDirty = _inverseDirty = true;
}

void PPlayer::targetRollUpdate(float dt)
{
	//Update rotation 
	float smoothedAngle = std::min(std::max(targetAngle*(1 - dt*returnSpeed*(rollReturnThreshold - fabsf(targetAngle) / maxRoll)), -maxRoll), maxRoll);
	//_spr3D->setRotation3D(Vec3(fabsf(smoothedAngle)*0.15, smoothedAngle, 180));
	//setRotation3D(Vec3(fabsf(smoothedAngle)*0.15, smoothedAngle, 180));

	//Test Models
	_spr3D->setRotation3D(Vec3((fabsf(smoothedAngle)*0.15) + 120, smoothedAngle, 180));
	setRotation3D(Vec3((fabsf(smoothedAngle)*0.15) + 120, smoothedAngle, 180));

	targetAngle = getRotation3D().y;

}
