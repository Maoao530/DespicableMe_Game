/*

#pragma once

#include "cocos2d.h"
#include "WayPoint.h"
#include "GameLayer.h"
#include "GameHUD.h"
#include "Creep.h"
#include "Wave.h"
#include "Projectile.h"
#include "Tower.h"

using namespace cocos2d;

class DataModel{
public:
	static DataModel* getInstance();
	static void destroyInstance();
public:
	GameLayer* _gameLayer;
	GameHUD* _gameHUD;
	Vector<WayPoint*> wayPoints;
	Vector<Creep*> _targets;
	Vector<Wave*> _waves;
	Vector<Projectile*> _projectiles;
	Vector<Tower*> towers;
private:
	DataModel(){};
	static DataModel* m_pInstance;
};

*/