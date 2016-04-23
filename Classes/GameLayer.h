/*

#pragma once

#include "cocos2d.h"
#include "Wave.h"

using namespace cocos2d;

class GameLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);

	void addWayPoint();
	void addWaves();
	void addTower(Point pos);
	void addTarget();

	Point tileCoordForPosition(Point position);
	void gameLogic(float dt);
	void update(float dt);

	Wave* getCurrentWave();
	Wave* getNextWave();

	void FollowPath(Node* sender);
	bool canBuildOnTilePosition(Point pos);

public:
	TMXTiledMap* tileMap;
	TMXLayer* background;
	int curLevel ;
	Point postion;

};

*/