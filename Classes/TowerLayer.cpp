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
	//����
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);//��Ҫ���´��ݴ���
	listener->onTouchBegan = CC_CALLBACK_2(TowerLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(TowerLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(TowerLayer::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//�Ƿ��ڴ�����
	isBuildingTower = false;
	_isUpdatingTower = false;

	//��update�д����ӵ���ײ
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

	//������ǰ״̬Ϊ���������У����ѡ�������򴴽�����
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
			
			//�������  �����	��Ǯ ���ĵȼ�
			Tower* tower = TowerFactory::createTower(level,tower1->_money,1);
			Point pos = this->getChildByTag(BUILD_TOWER_SELECT_TAG)->getPosition();
			tower->setPosition(pos);
			this->addChild(tower);
			GameData::getInstance()->_towersVector.pushBack(tower);
			
			//���½��
			GameData::getInstance()->_currentMoney -= tower1->_money;
			sprintf(str,"%d",GameData::getInstance()->_currentMoney);
			((MainScene*)this->getParent())->_moneyLabel->setString(str);

			//�Ƴ�ѡ���
			this->removeChildByTag(BUILD_TOWER_SELECT_TAG,true);
			this->removeChild(tower1,true);
			this->removeChild(tower2,true);
			this->removeChild(tower3,true);
			isBuildingTower = false;

			GameAuio::getInstance()->palyEffect(AUDIO_TOWER_BUILD);
			
			return;

		}else if(tower2 && tower2->isCanSelect() && tower2->_sprite_nor->getBoundingBox().containsPoint(pointInNode2)){
			
			//�������
			Tower* tower = TowerFactory::createTower(level + 1,tower2->_money,1);
			Point pos = this->getChildByTag(BUILD_TOWER_SELECT_TAG)->getPosition();
			tower->setPosition(pos);
			this->addChild(tower);
			GameData::getInstance()->_towersVector.pushBack(tower);
			
			//���½��
			GameData::getInstance()->_currentMoney -= tower2->_money;
			sprintf(str,"%d",GameData::getInstance()->_currentMoney);
			((MainScene*)this->getParent())->_moneyLabel->setString(str);

			//�Ƴ�ѡ���
			this->removeChildByTag(BUILD_TOWER_SELECT_TAG,true);
			this->removeChild(tower1,true);
			this->removeChild(tower2,true);
			this->removeChild(tower3,true);
			isBuildingTower = false;

			GameAuio::getInstance()->palyEffect(AUDIO_TOWER_BUILD);

			return;

		}else if(tower3 && tower3->isCanSelect() && tower3->_sprite_nor->getBoundingBox().containsPoint(pointInNode3)){
			
			//�������
			Tower* tower = TowerFactory::createTower(level + 2,tower3->_money,1);
			Point pos = this->getChildByTag(BUILD_TOWER_SELECT_TAG)->getPosition();
			tower->setPosition(pos);
			this->addChild(tower);
			GameData::getInstance()->_towersVector.pushBack(tower);

			//���½��
			GameData::getInstance()->_currentMoney -= tower3->_money;
			sprintf(str,"%d",GameData::getInstance()->_currentMoney);
			((MainScene*)this->getParent())->_moneyLabel->setString(str);
			
			//�Ƴ�ѡ���
			this->removeChildByTag(BUILD_TOWER_SELECT_TAG,true);
			this->removeChild(tower1,true);
			this->removeChild(tower2,true);
			this->removeChild(tower3,true);
			isBuildingTower = false;

			GameAuio::getInstance()->palyEffect(AUDIO_TOWER_BUILD);
			
			return;
		}

		//�Ƴ�ѡ���
		this->removeChildByTag(BUILD_TOWER_SELECT_TAG,true);
		this->removeChild(tower1,true);
		this->removeChild(tower2,true);
		this->removeChild(tower3,true);
		isBuildingTower = false;
		return;
	}
	//������ǰ״̬Ϊ���������У����ѡ����������������
	else if(_isUpdatingTower){
		
		//��ȡtowerUpdate
		TowerUpdate* update = (TowerUpdate*)this->getChildByTag(BUILD_TOWER_UPDATE_TAG);

		//��ȡremove��Ϣ
		Point touchPosInRemoveNode = update->convertToNodeSpace(touchPos);
		Sprite* reomveSprite = update->_remove;

		//��ȡupdate��Ϣ
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

		//�����ж�
		//����
		char str[10] = {0};
		if(update->isCanUpdate() && updateSPrite->getBoundingBox().containsPoint(touchPosInUpdateNode))
		{
			//���½��
			GameData::getInstance()->_currentMoney -= update->_updateMoney;
			sprintf(str,"%d",GameData::getInstance()->_currentMoney);
			((MainScene*)this->getParent())->_moneyLabel->setString(str);

			//������
			Point towerPos = _towerUpdate->getPosition();
			int towerNo = _towerUpdate->_towerNo;
			int towerMoney = update->_updateMoney;
			int towerLevel = update->_level + 1;

			//�Ƴ�����
			_towerUpdate->_sprite->stopAllActions();
			_towerUpdate->removeChild(_towerUpdate->_sprite,true);
			this->removeChild(_towerUpdate,true);
			GameData::getInstance()->_towersVector.eraseObject(_towerUpdate);
			_towerUpdate = NULL;

			//�������
			Tower* tower = TowerFactory::createTower(towerNo,towerMoney,towerLevel);
			tower->setPosition(towerPos);
			this->addChild(tower);
			GameData::getInstance()->_towersVector.pushBack(tower);
			
			GameAuio::getInstance()->palyEffect(AUDIO_TOWER_UPDATE);
		}
		//����
		else if (reomveSprite->getBoundingBox().containsPoint(touchPosInRemoveNode))
		{
			//���½��
			GameData::getInstance()->_currentMoney += update->_soldMoney;
			sprintf(str,"%d",GameData::getInstance()->_currentMoney);
			((MainScene*)this->getParent())->_moneyLabel->setString(str);

			//�Ƴ�����
			_towerUpdate->_sprite->stopAllActions();
			_towerUpdate->removeChild(_towerUpdate->_sprite,true);
			this->removeChild(_towerUpdate,true);
			GameData::getInstance()->_towersVector.eraseObject(_towerUpdate);
			_towerUpdate = NULL;

			GameAuio::getInstance()->palyEffect(AUDIO_TOWER_SELL);

		}

		//û�е������Ƴ�
		this->removeChildByTag(BUILD_TOWER_UPDATE_TAG);
		_isUpdatingTower = false;
		return;
	}


	TouchType type = getTouchType(touchPos);
	switch (type)
	{
	case MENU://�˵�����mainScene���Ѵ���
		CCLOG("touch MENU");
		break;
	case ROAD://·��������
		CCLOG("touch ROAD");
		GameAuio::getInstance()->palyEffect(AUDIO_SELECT_FAULT);
		break;
	case NONE:	//�յأ�������
		{
			GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
			CCLOG("touch NONE");
			int build_gird_x = touchPos.x / 64 ;
			int build_gird_y = touchPos.y / 64 ;
			Point buildPos = Point(build_gird_x * 64 + 32,build_gird_y * 64 + 32);
			buildTowerSelect(buildPos);
			break;
		}
	case TOWER:	//����
		CCLOG("touch TOWER");
		GameAuio::getInstance()->palyEffect(AUDIO_TOWER_SELECT);
		buildTowerUpdate();
		break;
	case ENEMY://���ȹ���,��getTouchType�д���
		CCLOG("touch ENEMY");
		GameAuio::getInstance()->palyEffect(AUDIO_SHOOT_SELECT);
		break;
	case PLANT://���ȹ���,��getTouchType�д���
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
	//Ϊ�˷��㽫���½���Ϊ��������ԭ�㣨1,1)
	float girdWidth = 64;
	float girdHeight = 64;

	//�������������ת��ΪGird��������
	int build_gird_x = point.x / girdWidth + 1;
	int build_gird_y = point.y / girdHeight + 1;

	//���ζ���λ��
	if(build_gird_y == 8){
		return MENU;
	}

	//ѭ���������ˣ������ڵ�·�ϣ������ȱ���
	for(Enemy* enemy : GameData::getInstance()->_enemysVector){

		//������ ת��Ϊ�ڵ�����ϵ �ĵ�
		Point pointInNode = enemy->convertToNodeSpace(point);
		if(enemy->_sprite->getBoundingBox().containsPoint(pointInNode)){

			//�Ȼָ����е�enemy���ȹ���
			for(Enemy* e : GameData::getInstance()->_enemysVector){
				if (e->isPriorityAttact())
				{
					e->removeChild(e->_prioritySprite,true);
					e->_prioritySprite = NULL;
					e->_isPriorityAttact = false;
				}
			}

			//�ٻָ����е�plant���ȹ���
			for(Plant* p : GameData::getInstance()->_plantsVector){
				if (p->isPriorityAttact())
				{
					p->removeChild(p->_prioritySprite,true);
					p->_prioritySprite = NULL;
					p->_isPriorityAttact = false;
				}
			}
			//�������ȹ�������
			enemy->createPriorityPoint();
			return ENEMY;
		}
	}

	//ѭ��������·����waypoints
	bool isFirstWayPos = true;
	int lastX = 0;
	int lastY = 0;
	for(WayPoint* waypoint : GameData::getInstance()->_pointsVector){

		Point pos = waypoint->getPosition();
		//ת��Ϊ��������
		int gird_x = pos.x / girdWidth;
		int gird_y = pos.y / girdHeight;
		if(pos.x > gird_x ){
			gird_x ++;
		}
		if(pos.y > gird_y){
			gird_y ++;
		}

		//���ж��Ƿ�͵�ǰwaypoint�����
		if(build_gird_x == gird_x && build_gird_y == gird_y){
			return ROAD;
		} 
		//���ж��Ƿ����һ�������ӵ�·�����
		//��һ����
		if(isFirstWayPos){
			isFirstWayPos = false;
			lastX = gird_x;
			lastY = gird_y;
			continue;
		}
		//�ǵ�һ����
		else
		{
			int offsetX = gird_x - lastX;
			int offsetY = gird_y - lastY;

			//·����ֱ
			if( offsetX == 0){
				//x����ͬ
				if(build_gird_x == gird_x){
					//ǰһ�������£���ǰ������
					if(offsetY > 0){
						//y���ڴ�ֱ·����Χ��
						if(lastY <= build_gird_y && build_gird_y <= gird_y ){
							return ROAD;
						}
					}
					//��ǰ�����£�ǰһ��������
					else if(offsetY < 0){
						//y���ڴ�ֱ·����Χ��
						if(gird_y <= build_gird_y && build_gird_y <= lastY ){
							return ROAD;
						}
					}
				}
			}
			//·��ˮƽ
			if(offsetY == 0){
				//y����ͬ
				if(build_gird_y == gird_y){
					//ǰһ�������󣬵�ǰ������
					if(offsetX > 0){
						//x����ˮƽ·����Χ��
						if(lastX <= build_gird_x && build_gird_x <= gird_x){
							return ROAD;
						}
					}
					//��ǰ������ǰһ��������
					else if(offsetX < 0){
						//x����ˮƽ·����Χ��
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
	
	//ѭ������ֲ��
	for(Plant* plant : GameData::getInstance()->_plantsVector){

		//ת��Ϊ�ڵ�����ϵ
		//����plant���½�(0,0)Ϊԭ�㣬��λpoint
		Point pointInNode = plant->convertToNodeSpace(point);
		
		if(plant->_sprite->getBoundingBox().containsPoint(pointInNode)){
			//�Ȼָ����е�enemy���ȹ���
			for(Enemy* e : GameData::getInstance()->_enemysVector){
				if (e->isPriorityAttact())
				{
					e->removeChild(e->_prioritySprite,true);
					e->_prioritySprite = NULL;
					e->_isPriorityAttact = false;
				}
			}

			//�ٻָ����е�plant���ȹ���
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

	//ѭ�������Ѿ���������
	for(Tower* tower : GameData::getInstance()->_towersVector){
		
		//������ ת��Ϊ�ڵ�����ϵ �ĵ�
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
	//����tower��tag��level��Ӧ
	tower1->setTag(level);
	tower2->setTag(level + 1);
	tower3->setTag(level + 2);
	//����֮һ��Ļ�·�
	if(point.y <= winSize.height / 2){
		//����
		if(point.x <= 64){
			tower1->setPosition(point.x, point.y + 60);
			tower2->setPosition(point.x + 60, point.y + 60);
			tower3->setPosition(point.x +120, point.y + 60);
		}
		//����
		else if(point.x >= winSize.width - 64 ){
			tower1->setPosition(point.x - 120, point.y + 60);
			tower2->setPosition(point.x - 60, point.y + 60);
			tower3->setPosition(point.x, point.y + 60);
		}
		//����
		else{
			tower1->setPosition(point.x - 60, point.y + 60);
			tower2->setPosition(point.x , point.y + 60);
			tower3->setPosition(point.x + 60, point.y + 60);
		}
	}
	//����֮һ��Ļ�Ϸ�
	else if(point.y > winSize.height / 2){
		//����
		if(point.x <= 64){
			tower1->setPosition(point.x, point.y - 60);
			tower2->setPosition(point.x + 60, point.y - 60);
			tower3->setPosition(point.x +120, point.y - 60);
		}
		//����
		else if(point.x >= winSize.width - 64 ){
			tower1->setPosition(point.x - 120, point.y - 60);
			tower2->setPosition(point.x - 60, point.y - 60);
			tower3->setPosition(point.x, point.y - 60);
		}
		//����
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
					//�����������ұ�ǩ
					
					GameData::getInstance()->_currentMoney += plant->_money;
					sprintf(moneyStr,"%d",GameData::getInstance()->_currentMoney);
					((MainScene*)this->getParent())->_moneyLabel->setString(moneyStr);
					//die
					plant->die();
				}
				//����͸�ӵ�
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
					//�����������ұ�ǩ
	
					GameData::getInstance()->_currentMoney += enemy->_money;
					sprintf(moneyStr,"%d",GameData::getInstance()->_currentMoney);
					((MainScene*)this->getParent())->_moneyLabel->setString(moneyStr);
					//die
					enemy->die();
				}
				//����͸�ӵ�
				if(bullet->_type == BULLET_SINGLE){
					GameData::getInstance()->_bulletToDeleteVector.pushBack(bullet);
					isToDel = true;
				}
			}
		}//end enemy for
		if(isToDel)
			continue;
	}//end bullet
	//������Ҫɾ�����ӵ�
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
	
	//����������
	_isUpdatingTower = true;
}