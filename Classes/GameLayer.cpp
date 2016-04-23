/*

#include "GameLayer.h"
#include "WayPoint.h"
#include "DataModel.h"
#include "Tower.h"

bool GameLayer::init(){
	if(!Layer::init()){
		return false;
	}

	this->tileMap = TMXTiledMap::create("TileMap.tmx");
	this->background = tileMap->layerNamed("Background");
	this->background->setAnchorPoint(Point::ZERO);
	this->addChild(tileMap,-1);

	this->addWayPoint();
	this->addWaves();

	this->curLevel = 0;
	this->postion = ccp(-288,-122);

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameLayer::gameLogic),1.f);
	return true;
}

void GameLayer::addWayPoint(){
	DataModel* dm = DataModel::getInstance();
	auto objects = this->tileMap->objectGroupNamed("Objects");
	WayPoint* wp = NULL;
	std::string stringWithFormat = "Waypoint";
	int wayPointCounter = 0;
	ValueMap wayPoint;
	wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));
	char str[10] = {0};
	int i = 0;
	sprintf(str,"Waypoint%d",i);
	while(wayPoint.begin() != wayPoint.end()){
		float x = wayPoint.at("x").asInt();
		float y = wayPoint.at("y").asInt();
		CCLog("%s:(%f,%f)",str,x,y);
		sprintf(str,"Waypoint%d",++i);
		wp = WayPoint::create();
		wp->setPosition(ccp(x,y));
		dm->wayPoints.pushBack(wp);

		wayPointCounter ++;
		wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));
	}
	wp =NULL;
}

void GameLayer::addWaves()
{
	DataModel *m = DataModel::getInstance();

	Wave *wave = NULL;
	//creep，0.3 出现频率，50个
	wave = Wave::create()->initWithCreep(FastRedCreep::creep(), 0.3, 50);
	m->_waves.pushBack(wave);
	wave = NULL;
	wave = Wave::create()->initWithCreep(StrongGreenCheep::creep(),1.0,5);
	m->_waves.pushBack(wave);
	wave = NULL;
}

Wave* GameLayer::getCurrentWave(){
	return DataModel::getInstance()->_waves.at(this->curLevel);
}

Wave* GameLayer::getNextWave(){
	this->curLevel ++;
	
	if (this->curLevel > 1){
		this->curLevel = 0;
	}

	return DataModel::getInstance()->_waves.at(this->curLevel);
}


void GameLayer::addTower(Point pos){
	DataModel *m = DataModel::getInstance();
	Tower *target = NULL ;
	Point towerLoc = this->tileCoordForPosition(pos);

	int tileGid = this->background->tileGIDAt(towerLoc);
	Value props = this->tileMap->propertiesForGID(tileGid);
	ValueMap map = props.asValueMap();

	int type_int = map.at("buildable").asInt();
	if (1 == type_int) 
	{
		target = MachineGunTower::tower();
		target->setPosition(ccp((towerLoc.x * 32) + 16, this->tileMap->getContentSize().height - (towerLoc.y * 32) - 16));
		this->addChild(target,1);
		target->setTag(1);
		m->towers.pushBack(target);
	}
	else 
	{
		log("Tile Not Buildable");
	}
}

void GameLayer::addTarget(){
	
	Wave* wave= this->getCurrentWave();
	if(wave->totalCreeps < 0){
		return;
	}
	wave->totalCreeps --;
	Creep* target = NULL;
	int random = CCRANDOM_0_1() * 2;
	if (random == 0) {
		target = FastRedCreep::creep();
	}else{
		target = StrongGreenCheep::creep();
	}
	WayPoint* wayPoint = target->getCurrentWaypoint();
	target->setPosition(wayPoint->getPosition());
	wayPoint = target->getNextWaypoint();
	this->addChild(target,1);
		
	int moveDuration = target->moveDuration;
	auto actionMove = CCMoveTo::create(moveDuration, wayPoint->getPosition());
	auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameLayer::FollowPath));
	target->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	target->tag = 1;
	DataModel::getInstance()->_targets.pushBack(target);;
	
}

Point GameLayer::tileCoordForPosition(Point position)
{
	int x = position.x / this->tileMap->getTileSize().width;
	int y = ((this->tileMap->getMapSize().height * this->tileMap->getTileSize().height) - position.y) / this->tileMap->getTileSize().height;
	return ccp(x, y);
}

void GameLayer::gameLogic(float dt){
	
	DataModel *m = DataModel::getInstance();
	Wave * wave = this->getCurrentWave();
	static double lastTimeTargetAdded = 0;
	double now = 0;
	if (lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= wave->spawnRate){
		this->addTarget();
		lastTimeTargetAdded = now;
	}
}

void GameLayer::update(float dt){
	DataModel *m = DataModel::getInstance();
	Vector<Projectile*> projectilesToDelete;

	for(Projectile *projectile : m->_projectiles) 
	{
		Rect projectileRect = Rect(projectile->getPositionX() - (projectile->getContentSize().width / 2),
			projectile->getPositionY() - (projectile->getContentSize().height / 2),
			projectile->getContentSize().width,
			projectile->getContentSize().height);

		Vector<Creep*> targetsToDelete;

		for(Creep *target : m->_targets) 
		{
			Rect targetRect = Rect(target->getPositionX() - (target->sprite->getContentSize().width / 2),
				target->getPositionY() - (target->sprite->getContentSize().height / 2),
				target->sprite->getContentSize().width,
				target->sprite->getContentSize().height);

			if (projectileRect.intersectsRect(targetRect)) 
			{
				projectilesToDelete.pushBack(projectile);

				Creep *creep = target;
				creep->curHp -= 1;

				if (creep->curHp <= 0) 
				{
					targetsToDelete.pushBack(creep);
				}
				break;
			}
		}

		for(Creep *target : targetsToDelete)
		{
			m->_targets.eraseObject(target);
			this->removeChild(target, true);
		}		
	}

	for (Projectile *projectile : projectilesToDelete)
	{
		m->_projectiles.eraseObject(projectile);
		this->removeChild(projectile,true);
	}
}

void GameLayer::FollowPath(Node* sender){
	Creep *creep = (Creep *)sender;

	WayPoint * waypoint = creep->getNextWaypoint();

	int moveDuration = creep->moveDuration;
	auto actionMove = MoveTo::create(moveDuration,waypoint->getPosition());
	auto actionMoveDone = CallFuncN::create(this,callfuncN_selector(GameLayer::FollowPath));
	creep->stopAllActions();
	creep->runAction(Sequence::create(actionMove,actionMoveDone,NULL));
}

bool GameLayer::canBuildOnTilePosition(Point pos)
{
	Point towerLoc = this->tileCoordForPosition(pos);
	int tileGid = this->background->getTileGIDAt(towerLoc);
	Value props = this->tileMap->getPropertiesForGID(tileGid);
	ValueMap map = props.asValueMap();
	int type_int;
	if (map.size() == 0)
	{
		type_int = 0;
	}
	else
	{
		type_int = map.at("buildable").asInt();
	}

	if (1 == type_int)
	{
		return true;
	}
	return false;
}

*/