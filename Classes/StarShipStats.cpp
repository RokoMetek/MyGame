#include "StarShipStats.h"

StarShipStats::StarShipStats()
{
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

void StarShipStats::showCollision()
{
}
