
#pragma once
#ifndef  __DEFINITIONS_H__
#define  __DEFINITIONS_H__



//CONTAINER SIZE
#define CONTAINER_SIZE 50
#define METEOR_CONTAINER_SIZE 50
#define BULLET_CONTAINER_SIZE 50
#define ENEMY_CONTAINER_SIZE 50
#define ENEMYBULLET_CONTAINER_SIZE 50

//PLAYER DEFINE
#define PLAYER_SCALE 80
#define PLAYER_RADIUS 0.4


//COLLISION BITMASK
#define COLLISION_PLAYER 0x000001
#define COLLISION_METEOR 0x000002
#define COLLISION_BULLET 0x000003
#define COLLISION_ENEMY  0x000004 
#define COLLISION_BULLET_ENEMY 0x000005


//DESIGN RESOLUTION
#define DESIGN_LEFT_BORDER -300
#define DESIGN_RIGHT_BORDER 300
#define DESIGN_TOP_BORDER 460
#define DESIGN_BOT_BORDER -460
#define DESIGN_CENTER_BORDER 0

//DESING RES x=  -320 <-> 320
//DESIGN RES y=   480 <-> -480

//Asteroids
#define ASTEROID_SPRITESHEET "asteroids_spritesheet.plist"
#define ASTEROID_PNG "asteroids_spritesheet.png"
#define ASTEROID "asteroids_%i.png"

//BULLETS
#define BULLETS_SPRITESHEET "bullets_spritesheet.plist"
#define BULLETS_PNG "bullets_spritesheet.png"
#define BULLET "bullet_%i.png"

//Spaceship
#define SPACESHIP_OBJECT "Spaceship%i/spaceship_%i.c3t"
#define SPACESHIP_MATERIALS "Spaceship%i/Ship_%i-Diffuse.png"


//TAG
#define GAME_OBJECT 1

//Enemy Movement StartPos
#define ENEMY_LEFT_OUT_BORDER -350
#define ENEMY_RIGHT_OUT_BORDER 350

#define ENEMY_TOP_OUT_BORDER 650
#define ENEMY_BOT_OUT_BORDER -650


//AUDIO
#define BACKGROUND_SOUND_INTRO "Audio/Intro.mp3"
#define BACKGROUND_SOUND_GAME "Audio/GameMusic.mp3"

#define SOUND_EFFECT_LASERSHOOT "Audio/LaserShoot.ogg"
#define SOUND_EFFECT_EXPLOSION1 "Audio/Explosion1.ogg"
#define SOUND_EFFECT_EXPLOSION2 "Audio/Explosion2.ogg"
#define SOUND_EFFECT_EXPLOSION3 "Audio/Explosion3.ogg"
#define SOUND_EFFECT_BULLETIMPACT "Audio/BulletImpact.ogg"




#endif