#include "Player.h"
#include "GameConfig.h"
#include "GameLayer.h"
#include "Definitions.h"



const float Player::rollSpeed = 1.5;// recommended 1.5
const float Player::returnSpeed = 10;// recommended 4
const float Player::maxRoll = 75;
const float Player::rollReturnThreshold = 1.02;

bool Player::init()
{
	//setModel(EffectSprite3D::createFromObjFileAndTexture("Main_starship.c3b", "mappa-base.png"));
	_Model = EffectSprite3D::createFromObjFileAndTexture("Main_starship.c3b", "mappa-base.png");
	
	//test_sprite = Sprite::create("HelloWorld.png");
	if (_Model) {

		//Model Broda - inicializacija
		setHp(100);
		setAlive(true);
		setRadius(40);


		_Model->setScale(1.2);
		_Model->setRotation3D(Vec3(30, 0, 180));
		_Model->setGlobalZOrder(10);
		
		addChild(_Model, 10);
		//addChild(test_sprite);

		
		//Event Listner - Mouse Click
		/*
		auto listener_mouse = EventListenerTouchOneByOne::create();
		listener_mouse->setSwallowTouches(true);
		listener_mouse->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
		listener_mouse->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
		listener_mouse->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_mouse, this);
		


		//Event Listener - Keyboard
		
		auto listener_keyboard = EventListenerKeyboard::create();
		listener_keyboard->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
		listener_keyboard->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_keyboard, this);
		*/

		//Update player function - roll 3D models
		//this->scheduleUpdate();
		
		return true;
	}

	return false;
}

bool Player::onTouchBegan(Touch * touch, Event * event)
{

	CCLOG("Touch location: x->%f  y->%f", touch->getLocation().x, touch->getLocation().y);
	return true;
}

void Player::onTouchMoved(Touch * touch, Event * event)
{
	Vec2 prev = _Model->getPosition();
	//Vec2 prev = event->getCurrentTarget()->getPosition();
	Vec2 delta = touch->getDelta();
	
	//Angel - mozda bom trebal a mozda niti nej
	//Roll 3D models 
	setTargetAngle(targetAngle + delta.x* rollSpeed*(rollReturnThreshold - fabsf(targetAngle) / maxRoll));
	
	//Promjena pozicije
	Vec2 shiftPostion = delta + prev;
	setPosition(shiftPostion.getClampPoint(Vec2(DESIGN_LEFT_BORDER, DESIGN_BOT_BORDER), Vec2(DESIGN_RIGHT_BORDER, DESIGN_TOP_BORDER)));



}

void Player::onTouchEnded(Touch * touch, Event * event)
{
	
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	log("Key with keycode %d pressed", keyCode);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		log("Pritisnuta tipka W");
		break;
	case EventKeyboard::KeyCode::KEY_S:
		log("Pritisnuta tipka S");
		break;
	case EventKeyboard::KeyCode::KEY_A:
		log("Pritisnuta tipka A");
		break;
	case EventKeyboard::KeyCode::KEY_D:
		log("Pritisnuta tipka D");
		break;
	}
	
}

void Player::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	log("Key with keycode %d released", keyCode);
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
		log("Pustena tipka W");
		break;
	case EventKeyboard::KeyCode::KEY_S:
		log("Pustena tipka S");
		break;
	case EventKeyboard::KeyCode::KEY_A:
		log("Pustena tipka A");
		break;
	case EventKeyboard::KeyCode::KEY_D:
		log("Pustena tipka D");
		break;
	}
}

void Player::update(float dt)
{
	//log("Update function");
	float smoothedAngle = std::min(std::max(targetAngle*(1 - dt*returnSpeed*(rollReturnThreshold - fabsf(targetAngle) / maxRoll)), -maxRoll), maxRoll);
	_Model->setRotation3D(Vec3(fabsf(smoothedAngle)*0.15, smoothedAngle, 180));
	setRotation3D(Vec3(fabsf(smoothedAngle)*0.15, smoothedAngle, 0));

	targetAngle = getRotation3D().y;
}

void Player::setPosition(Vec2 pos)
{
	if (_position.equals(pos)) {
		return;
	}


	CCLOG("Touch location POSITION: x->%f  y->%f", pos.x, pos.y);

	_Model->setPosition(pos);
	_position = pos;
	_transformUpdated = _transformDirty = _inverseDirty = true;

	//_Model->setPosition(_position);
	
}

void Player::shoot()
{
}


Player::Player()
{
}

Player::Player(Layer * layer)
{

	//setModel(EffectSprite3D::createFromObjFileAndTexture("Main_starship.c3b", "mappa-base.png"));
	_Model = EffectSprite3D::createFromObjFileAndTexture("Main_starship.c3b", "mappa-base.png");
	//test_sprite = Sprite::create("HelloWorld.png");
	if (_Model) {

		//Model Broda - inicializacija
		setHp(100);
		setAlive(true);
		setRadius(40);


		_Model->setScale(1.2);
		_Model->setRotation3D(Vec3(30, 0, 180));
		_Model->setGlobalZOrder(10);

		layer->addChild(_Model, 10);



		//Event Listner - Mouse Click
		/*
		auto listener_mouse = EventListenerTouchOneByOne::create();
		listener_mouse->setSwallowTouches(true);
		listener_mouse->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
		listener_mouse->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
		listener_mouse->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_mouse, layer);



		//Event Listener - Keyboard

		auto listener_keyboard = EventListenerKeyboard::create();
		listener_keyboard->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
		listener_keyboard->onKeyReleased = CC_CALLBACK_2(Player::onKeyReleased, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener_keyboard, layer);
		*/
	}


}


Player::~Player()
{
}

