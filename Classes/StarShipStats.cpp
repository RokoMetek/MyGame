#include "StarShipStats.h"

StarShipStats::StarShipStats()
{

	_alive = false;
	_hp = 100;
	_score = 10;
}


StarShipStats::~StarShipStats()
{

}



void StarShipStats::showExplosion(Layer * layer)
{
	auto explosion = ParticleSystemQuad::create("Particles/toonSmoke.plist");
	explosion->setPosition(this->getSpr3D()->getPosition());
	explosion->setAutoRemoveOnFinish(true);
	layer->addChild(explosion);
}

void StarShipStats::hurt(float damge)
{

	
}

