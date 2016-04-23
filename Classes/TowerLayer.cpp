#include "TowerLayer.h"
#include "GameData.h"
#include "Plant.h"
#include "Resources.h"
#include "AnimationUtil.h"
#include "Tower.h"
#include "TowerSelect.h"
#include "MainScene.h"
#include "TowerUpdate.h"
#include "GameAudio.h"


bool TowerLayer::init(){
	if(!Layer::init())
	{
		return false;
	}
	//触摸
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);//需要向下传递触摸
	listener->onTouchBegan = CC_CALLBACK_2(TowerLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TowerLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TowerLayer::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//是否在创建塔
	isBuildingTower = false;
	_isUpdatingTower = false;

	//在update中处理子弹碰撞
	this->scheduleUpdate();

	return true;
}

bool TowerLayer::onTouchBegan(Touch *touch, Event *event){
	return true;
}

void TowerLayer::onTouchMoved(Touch *touch, Event *event){

}
void TowerLayer::onTouchEnded(Touch* touch, Event* event){
	Point touchPos = touch->getLocation();
//	CCLOG("(%F,%f)",touchPos.x,touchPos.y);

	//表明当前状态为创建炮塔中，如果选中炮塔则创建炮塔
	if(isBuildingTower){

		int level = GameData::getInstance()->_currentLevel;

		TowerSelect* tower1 = (TowerSelect*)this->getChildByTag(level);
		TowerSelect* tower2 = (TowerSelect*)this->getChildByTag(level + 1);
		TowerSelect* tower3 = (TowerSelect*)this->getChildByTag(level + 2);

		Point pointInNode1 = tower1->convertToNodeSpace(touchPos);
		Point pointInNode2 = tower2->convertToNodeSpace(touchPos);
		Point pointInNode3 = tower3->convertToNodeSpace(touchPos);

		char str[10] = {0};

		if(tower1 && tower1->isCanSelect() && tower1->_sprite_nor->getBoundingBox().containsPoint(pointInNode1)){
			
			//添加炮塔  塔编号	金钱 塔的等级
			Tower* tower = TowerFactory::createTower(level,tower1->_money,1);
			Point pos = this->getChildByTag(BUILD_TOWER_SELECT_TAG)->getPosition();
			tower->setPosition(pos);
			this->addChild(tower);
			GameData::getInstance()->_towersVector.pushBack(tower);
			
			//更新金币
			GameData::getInstance()->_currentMoney -= tower1->_money;
			sprintf(str,"%d",GameData::getInstance()->_currentMoney);
			((MainScene*)this->getParent())->_moneyLabel->setString(str);

			//移除选择框
			this->removeChildByTag(BUILD_TOWER_SELECT_TAG,true);
			this->removeChild(tower1,true);
			this->removeChild(tower2,true);
			this->removeChild(tower3,true);
			isBuildingTower = false;

			GameAuio::getInstance()->palyEffect(AUDIO_TOWER_BUILD);
			
			return;

		}else if(tower2 && tower2->isCanSelect() && tower2->_sprite_nor->getBoundingBox().containsPoint(pointInNode2)){
			
			//添加炮塔
			Tower* tower = TowerFactory::createTower(level + 1,tower2->_money,1);
			Point pos = this->getChildByTag(BUILD_TOWER_SELECT_TAG)->getPosition();
			tower->setPosition(pos);
			this->addChild(tower);
			GameData::getInstance()->_towersVector.pushBack(tower);
			
			//更新金币
			GameData::getInstance()->_currentMoney -= tower2->_money;
			sprintf(str,"%d",GameData::getInstance()->_currentMoney);
			((MainScene*)this->getParent())->_moneyLabel->setString(str);

			//移除选择框
			this->removeChildByTag(BUILD_TOWER_SELECT_TAG,true);
			this->removeChild(tower1,true);
			this->removeChild(tower2,true);
			this->removeChild(tower3,true);
			isBuildingTower = false;

			GameAuio::getInstance()->palyEffect(AUDIO_TOWER_BUILD);

			return;

		}else if(tower3 && tower3->isCanSelect() && tower3->_sprite_nor->getBoundingBox().containsPoint(pointInNode3)){
			
			//添加炮塔
			Tower* tower = TowerFactory::createTower(level + 2,tower3->_money,1);
			Point pos = this->getChildByTag(BUILD_TOWER_SELECT_TAG)->getPosition();
			tower->setPosition(pos);
			this->addChild(tower);
			GameData::getInstance()->_towersVector.pushBack(tower);

			//更新金币
			GameData::getInstance()->_currentMoney -= tower3->_money;
			sprintf(str,"%d",GameData::getInstance()->_currentMoney);
			((MainScene*)this->getParent())->_moneyLabel->setString(str);
			
			//移除选择框
			this->removeChildByTag(BUILD_TOWER_SELECT_TAG,true);
			this->removeChild(tower1,true);
			this->removeChild(tower2,true);
			this->removeChild(tower3,true);
			isBuildingTower = false;

			GameAuio::getInstance()->palyEffect(AUDIO_TOWER_BUILD);
			
			return;
		}

		//移除选择框
		this->removeChildByTag(BUILD_TOWER_SELECT_TAG,true);
		this->removeChild(tower1,true);
		this->removeChild(tower2,true);
		this->removeChild(tower3,true);
		isBuildingTower = false;
		return;
	}
	//表明当前状态为升级炮塔中，如果选中炮塔则升级炮塔
	else if(_isUpdatingTower){
		
		//获取towerUpdate
		TowerUpdate* update = (TowerUpdate*)this->getChildByTag(BUILD_TOWER_UPDATE_TAG);

		//获取remove信息
		Point touchPosInRemoveNode = update->convertToNodeSpace(touchPos);
		Sprite* reomveSprite = update->_remove;

		//获取update信息
		Point touchPosInUpdateNode;
		Sprite* updateSPrite = NULL;
		if(update->_level == 3)
		{
			touchPosInUpdateNode = update->convertToNodeSpace(touchPos);
			updateSPrite = update->_dingji;
		}
		else
		{
			touchPosInUpdateNode = update->convertToNodeSpace(touchPos);
			updateSPrite = update->_update_nor;
		}

		//触摸判断
		//更新
		char str[10] = {0};
		if(update->isCanUpdate() && updateSPrite->getBoundingBox().containsPoint(touchPosInUpdateNode))
		{
			//更新金币
			GameData::getInstance()->_currentMoney -= update->_updateMoney;
			sprintf(str,"%d",GameData::getInstance()->_currentMoney);
			((MainScene*)this->getParent())->_moneyLabel->setString(str);

			//塔参数
			Point towerPos = _towerUpdate->getPosition();
			int towerNo = _towerUpdate->_towerNo;
			int towerMoney = update->_updateMoney;
			int towerLevel = update->_level + 1;

			//移除旧塔
			_towerUpdate->_sprite->stopAllActions();
			_towerUpdate->removeChild(_towerUpdate->_sprite,true);
			this->removeChild(_towerUpdate,true);
			GameData::getInstance()->_towersVector.eraseObject(_towerUpdate);
			_towerUpdate = NULL;

			//添加新塔
			Tower* tower = TowerFactory::createTower(towerNo,towerMoney,towerLevel);
			tower->setPosition(towerPos);
			this->addChild(tower);
			GameData::getInstance()->_towersVector.pushBack(tower);
			
			GameAuio::getInstance()->palyEffect(AUDIO_TOWER_UPDATE);
		}
		//出售
		else if (reomveSprite->getBoundingBox().containsPoint(touchPosInRemoveNode))
		{
			//更新金币
			GameData::getInstance()->_currentMoney += update->_soldMoney;
			sprintf(str,"%d",GameData::getInstance()->_currentMoney);
			((MainScene*)this->getParent())->_moneyLabel->setString(str);

			//移除旧塔
			_towerUpdate->_sprite->stopAllActions();
			_towerUpdate->removeChild(_towerUpdate->_sprite,true);
			this->removeChild(_towerUpdate,true);
			GameData::getInstance()->_towersVector.eraseObject(_towerUpdate);
			_towerUpdate = NULL;

			GameAuio::getInstance()->palyEffect(AUDIO_TOWER_SELL);

		}

		//没有点中则移除
		this->removeChildByTag(BUILD_TOWER_UPDATE_TAG);
		_isUpdatingTower = false;
		return;
	}


	TouchType type = getTouchType(touchPos);
	switch (type)
	{
	case MENU://菜单，在mainScene中已处理
		CCLOG("touch MENU");
		break;
	case ROAD://路，不处理
		CCLOG("touch ROAD");
		GameAuio::getInstance()->palyEffect(AUDIO_SELECT_FAULT);
		break;
	case NONE:	//空地，创建塔
		{
			GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
			CCLOG("touch NONE");
			int build_gird_x = touchPos.x / 64 ;
			int build_gird_y = touchPos.y / 64 ;
			Point buildPos = Point(build_gird_x * 64 + 32,build_gird_y * 64 + 32);
			buildTowerSelect(buildPos);
			break;
		}
	case TOWER:	//升级
		CCLOG("touch TOWER");
		GameAuio::getInstance()->palyEffect(AUDIO_TOWER_SELECT);
		buildTowerUpdate();
		break;
	case ENEMY://优先攻击,在getTouchType中处理
		CCLOG("touch ENEMY");
		GameAuio::getInstance()->palyEffect(AUDIO_SHOOT_SELECT);
		break;
	case PLANT://优先攻击,在getTouchType中处理
		CCLOG("touch PLANT");
		GameAuio::getInstance()->palyEffect(AUDIO_SHOOT_SELECT);
		break;
	default:
		break;
	}
}

TouchType TowerLayer::getTouchType(Point point){

	//pixel : 892 x 512
	//gird  : 14  x 8
	//为了方便将左下角作为格子坐标原点（1,1)
	float girdWidth = 64;
	float girdHeight = 64;

	//将触摸点的坐标转化为Gird格子坐标
	int build_gird_x = point.x / girdWidth + 1;
	int build_gird_y = point.y / girdHeight + 1;

	//屏蔽顶端位置
	if(build_gird_y == 8){
		return MENU;
	}

	//循环遍历敌人，敌人在道路上，所以先遍历
	for(Enemy* enemy : GameData::getInstance()->_enemysVector){

		//触摸点 转换为节点坐标系 的点
		Point pointInNode = enemy->convertToNodeSpace(point);
		if(enemy->_sprite->getBoundingBox().containsPoint(pointInNode)){

			//先恢复所有的enemy优先攻击
			for(Enemy* e : GameData::getInstance()->_enemysVector){
				if (e->isPriorityAttact())
				{
					e->removeChild(e->_prioritySprite,true);
					e->_prioritySprite = NULL;
					e->_isPriorityAttact = false;
				}
			}

			//再恢复所有的plant优先攻击
			for(Plant* p : GameData::getInstance()->_plantsVector){
				if (p->isPriorityAttact())
				{
					p->removeChild(p->_prioritySprite,true);
					p->_prioritySprite = NULL;
					p->_isPriorityAttact = false;
				}
			}
			//创建优先攻击动画
			enemy->createPriorityPoint();
			return ENEMY;
		}
	}

	//循环遍历道路，即waypoints
	bool isFirstWayPos = true;
	int lastX = 0;
	int lastY = 0;
	for(WayPoint* waypoint : GameData::getInstance()->_pointsVector){

		Point pos = waypoint->getPosition();
		//转化为格子坐标
		int gird_x = pos.x / girdWidth;
		int gird_y = pos.y / girdHeight;
		if(pos.x > gird_x ){
			gird_x ++;
		}
		if(pos.y > gird_y){
			gird_y ++;
		}

		//先判断是否和当前waypoint点相等
		if(build_gird_x == gird_x && build_gird_y == gird_y){
			return ROAD;
		} 
		//再判断是否和上一个点连接的路径相等
		//第一个点
		if(isFirstWayPos){
			isFirstWayPos = false;
			lastX = gird_x;
			lastY = gird_y;
			continue;
		}
		//非第一个点
		else
		{
			int offsetX = gird_x - lastX;
			int offsetY = gird_y - lastY;

			//路径垂直
			if( offsetX == 0){
				//x轴相同
				if(build_gird_x == gird_x){
					//前一个点在下，当前点在上
					if(offsetY > 0){
						//y轴在垂直路径范围内
						if(lastY <= build_gird_y && build_gird_y <= gird_y ){
							return ROAD;
						}
					}
					//当前点在下，前一个点在上
					else if(offsetY < 0){
						//y轴在垂直路径范围内
						if(gird_y <= build_gird_y && build_gird_y <= lastY ){
							return ROAD;
						}
					}
				}
			}
			//路径水平
			if(offsetY == 0){
				//y轴相同
				if(build_gird_y == gird_y){
					//前一个点在左，当前点在右
					if(offsetX > 0){
						//x轴在水平路径范围内
						if(lastX <= build_gird_x && build_gird_x <= gird_x){
							return ROAD;
						}
					}
					//当前点在左，前一个点在右
					else if(offsetX < 0){
						//x轴在水平路径范围内
						if( gird_x <= build_gird_x && build_gird_x <= lastX){
							return ROAD;
						}
					}
				}
			}
		}//end else

		lastX = gird_x;
		lastY = gird_y;

	}//end for waypoint
	
	//循环遍历植物
	for(Plant* plant : GameData::getInstance()->_plantsVector){

		//转换为节点坐标系
		//即以plant左下角(0,0)为原点，定位point
		Point pointInNode = plant->convertToNodeSpace(point);
		
		if(plant->_sprite->getBoundingBox().containsPoint(pointInNode)){
			//先恢复所有的enemy优先攻击
			for(Enemy* e : GameData::getInstance()->_enemysVector){
				if (e->isPriorityAttact())
				{
					e->removeChild(e->_prioritySprite,true);
					e->_prioritySprite = NULL;
					e->_isPriorityAttact = false;
				}
			}

			//再恢复所有的plant优先攻击
			for(Plant* p : GameData::getInstance()->_plantsVector){
				if (p->isPriorityAttact())
				{
					p->removeChild(p->_prioritySprite,true);
					p->_prioritySprite = NULL;
					p->_isPriorityAttact = false;
				}
			}
			plant->createPriorityPoint();
			return PLANT;
		}
	}

	//循环遍历已经创建的塔
	for(Tower* tower : GameData::getInstance()->_towersVector){
		
		//触摸点 转换为节点坐标系 的点
		Point pointInNode = tower->convertToNodeSpace(point);
		if(tower->_sprite->getBoundingBox().containsPoint(pointInNode)){
			setUpdateTower(tower);
			return TOWER;
		}
	}

	return NONE;

}

void TowerLayer::buildTowerSelect(Point point){

	int level = GameData::getInstance()->_currentLevel;

	if(isBuildingTower)
	{
		this->removeChildByTag(BUILD_TOWER_SELECT_TAG,true);
		this->removeChildByTag(level,true);
		this->removeChildByTag(level + 1,true);
		this->removeChildByTag(level + 2,true);
		isBuildingTower = false;
		return;
	}

	auto winSize = Director::getInstance()->getWinSize();

	//select png
	auto select = Sprite::createWithSpriteFrameName("select_01.png");
	select->setTag(BUILD_TOWER_SELECT_TAG);
	select->setPosition(point);
	this->addChild(select,100);

	//animate
 	Animate* animate = AnimationUtil::getInstance()->getAnimate("select_0");
 	RepeatForever* repeteForever = RepeatForever::create(animate);
 	select->runAction(repeteForever);

	//towers select
	auto tower1 = TowerSelectFactory::createTowerSelct(level);
	auto tower2 = TowerSelectFactory::createTowerSelct(level + 1);
	auto tower3 = TowerSelectFactory::createTowerSelct(level + 2);
	tower1->setScale(0.8);
	tower2->setScale(0.8);
	tower3->setScale(0.8);
	//设置tower的tag和level对应
	tower1->setTag(level);
	tower2->setTag(level + 1);
	tower3->setTag(level + 2);
	//二分之一屏幕下方
	if(point.y <= winSize.height / 2){
		//最左
		if(point.x <= 64){
			tower1->setPosition(point.x, point.y + 60);
			tower2->setPosition(point.x + 60, point.y + 60);
			tower3->setPosition(point.x +120, point.y + 60);
		}
		//最右
		else if(point.x >= winSize.width - 64 ){
			tower1->setPosition(point.x - 120, point.y + 60);
			tower2->setPosition(point.x - 60, point.y + 60);
			tower3->setPosition(point.x, point.y + 60);
		}
		//正常
		else{
			tower1->setPosition(point.x - 60, point.y + 60);
			tower2->setPosition(point.x , point.y + 60);
			tower3->setPosition(point.x + 60, point.y + 60);
		}
	}
	//二分之一屏幕上方
	else if(point.y > winSize.height / 2){
		//最左
		if(point.x <= 64){
			tower1->setPosition(point.x, point.y - 60);
			tower2->setPosition(point.x + 60, point.y - 60);
			tower3->setPosition(point.x +120, point.y - 60);
		}
		//最右
		else if(point.x >= winSize.width - 64 ){
			tower1->setPosition(point.x - 120, point.y - 60);
			tower2->setPosition(point.x - 60, point.y - 60);
			tower3->setPosition(point.x, point.y - 60);
		}
		//正常
		else{
			tower1->setPosition(point.x - 60, point.y - 60);
			tower2->setPosition(point.x , point.y - 60);
			tower3->setPosition(point.x + 60, point.y - 60);
		}
	}
	this->addChild(tower1,100);
	this->addChild(tower2,100);
	this->addChild(tower3,100);

	//is building flag
	isBuildingTower = true;
}

void TowerLayer::update(float dt){

	char moneyStr[10] = {0};
	char bulletStr[10] = {0};

	//bullet
	for(Bullet* bullet : GameData::getInstance()->_bulletVector){

		 bool isToDel = false;

		Point bulletPos = bullet->getPosition();
		//plant
		for(Plant* plant : GameData::getInstance()->_plantsVector){
			
			if(isToDel)
				break;

			if(plant->_sprite->getBoundingBox().containsPoint(plant->convertToNodeSpace(bulletPos))){
				if(plant->getLife() > 0){
					plant->sliderShow();
					plant->getHurt(bullet->_attackValue);
					sprintf(bulletStr,"eff%d.png",bullet->_towerNo);
					plant->playAnimate(bulletStr);
				}else if(plant->getLife() == 0)
				{
					//更新主界面金币标签
					
					GameData::getInstance()->_currentMoney += plant->_money;
					sprintf(moneyStr,"%d",GameData::getInstance()->_currentMoney);
					((MainScene*)this->getParent())->_moneyLabel->setString(moneyStr);
					//die
					plant->die();
				}
				//不穿透子弹
				if(bullet->_type == BULLET_SINGLE){
					GameData::getInstance()->_bulletToDeleteVector.pushBack(bullet);
					isToDel = true;
				}
			}
		}

		if(isToDel)
			continue;
		//enemy
		for(Enemy* enemy : GameData::getInstance()->_enemysVector){
			if(isToDel)
				break;

			if(enemy->_sprite->getBoundingBox().containsPoint(enemy->convertToNodeSpace(bulletPos))){
				if(enemy->getLife() > 0){
					enemy->sliderShow();
					enemy->getHurt(bullet->_attackValue);
					sprintf(bulletStr,"eff%d.png",bullet->_towerNo);
					enemy->playAnimate(bulletStr);
				}else if(enemy->getLife() == 0)
				{
					//更新主界面金币标签
	
					GameData::getInstance()->_currentMoney += enemy->_money;
					sprintf(moneyStr,"%d",GameData::getInstance()->_currentMoney);
					((MainScene*)this->getParent())->_moneyLabel->setString(moneyStr);
					//die
					enemy->die();
				}
				//不穿透子弹
				if(bullet->_type == BULLET_SINGLE){
					GameData::getInstance()->_bulletToDeleteVector.pushBack(bullet);
					isToDel = true;
				}
			}
		}//end enemy for
		if(isToDel)
			continue;
	}//end bullet
	//遍历需要删除的子弹
	for(Bullet* bullet : GameData::getInstance()->_bulletToDeleteVector){
		if(bullet != NULL){
			bullet->_sprite->stopAllActions();
			bullet->removeChild(bullet->_sprite);
			bullet->getParent()->removeChild(bullet,true);
			GameData::getInstance()->_bulletVector.eraseObject(bullet);
		}
	}
	GameData::getInstance()->_bulletToDeleteVector.clear();
}

void TowerLayer::setUpdateTower(Tower* pTower){

	this->_towerUpdate = pTower;
}

void TowerLayer::buildTowerUpdate(){

	Point towerPos = _towerUpdate->getPosition();

	auto towerUpdate = TowerUpdate::create();
	towerUpdate->initTowerUpdate(_towerUpdate);
	towerUpdate->setPosition(towerPos);
	towerUpdate->setTag(BUILD_TOWER_UPDATE_TAG);
	this->addChild(towerUpdate,100);
	
	//正在升级塔
	_isUpdatingTower = true;
}