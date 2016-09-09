#include "Bullets.h"



Bullets::Bullets()
{
}


Bullets::~Bullets()
{
}

PlayerBullet::PlayerBullet()
{

}

PlayerBullet::PlayerBullet(Layer *layer, PPlayer *player)
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	Size winSize = Director::getInstance()->getWinSize();
	_spr = Sprite::createWithSpriteFrameName("bullet_3.png");


	//_par = ParticleSystemQuad::create("Particles/Comet.plist");

	setWidth(_spr->getContentSize().width);
	setHeight(_spr->getContentSize().height);
	

	//Straightforward move bullet
	auto bulletMoveTo = MoveTo::create(0.01 * visibleSize.height, Vec2(player->getTargetPos().x + origin.x, visibleSize.height + origin.y));
	auto sequence = Sequence::create(
		bulletMoveTo,
		CallFunc::create(CC_CALLBACK_0(PlayerBullet::resetPlayerBullet, this)),
		nullptr);

	_spr->runAction(sequence);
	_spr->setPosition(player->getSpr3D()->getPosition());

	layer->addChild(_spr);

}

PlayerBullet::~PlayerBullet()
{

}

void PlayerBullet::resetPlayerBullet()
{
	//Remove bullet out of screen
	_spr->stopAllActions();
	_spr->removeFromParentAndCleanup(true);
}
