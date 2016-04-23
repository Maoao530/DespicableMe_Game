/*

#pragma once

#include "cocos2d.h"
#include "WayPoint.h"


using namespace cocos2d;

class Creep:public Sprite
{
public:
	virtual bool init();
	CREATE_FUNC(Creep);
	void creepLogic(float dt);

	WayPoint* getNextWaypoint();
	WayPoint* getCurrentWaypoint();
	
public:
	int curHp;
	int moveDuration;
	int curWaypoint;
	int tag;
	Sprite* sprite;

};

class FastRedCreep : public Creep
{
public:
	static Creep* creep();
};

class StrongGreenCheep : public Creep
{
public:
	static Creep* creep();
};

*/