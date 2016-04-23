#include "Tower.h"
#include "GameData.h"
#include "AnimationUtil.h"
#include "Plant.h"
#include "Enemy.h"
#include "MainScene.h"
#include "GameAudio.h"

bool Tower::init(){
	if(!Node::init()){
		return false;
	}
	
	return true;
}

Enemy* Tower::getPriorityEnemy(){
	for(Enemy* e : GameData::getInstance()->_enemysVector){
		if (e->isPriorityAttact())
		{
			Point enemyPos = e->getPosition();
			Point towerPos = this->getPosition();
			int dis = ccpDistance(enemyPos,towerPos);
			if(dis < this->_attackDistance){
				return e;
			}
		}
	}
	return NULL;
}

Plant* Tower::getPriorityPlant(){

	for(Plant* p : GameData::getInstance()->_plantsVector){

		if (p->isPriorityAttact() )
		{
			//由于植物sprite锚点在左下角
			//为了对称，计算位置的时候选取sprite中点(0.5,0.5)
			Point plantPos = Point(
				p->getPositionX() + p->_sprite->getContentSize().width / 2,
				p->getPositionY() + p->_sprite->getContentSize().height / 2
				);
			Point towerPos = this->getPosition();
			int dis = ccpDistance(plantPos,towerPos);
			if(dis < this->_attackDistance){
				return p;
			}
		}
	}
	return NULL;
}

Enemy* Tower::getCloseTarget(){

	Enemy* closeEnemy = NULL;

	int minDistance = 9999;

	for(Enemy* enemy : GameData::getInstance()->_enemysVector){

		Point enemyPos = enemy->getPosition();
		Point towerPos = this->getPosition();

		int dis = ccpDistance(enemyPos,towerPos);
		
		if(dis < this->_attackDistance && dis <minDistance){
			minDistance = dis;
			closeEnemy = enemy;
		}
	}
	return closeEnemy;
}

Vector<Enemy*> Tower::getAllCanBeAttackEnemy(){

	_enemysCanBeAttack.clear();

	for(Enemy* e : GameData::getInstance()->_enemysVector){
		Point enemyPos = e->getPosition();
		Point towerPos = this->getPosition();
		int dis = ccpDistance(enemyPos,towerPos);
		if(dis < this->_attackDistance){
			_enemysCanBeAttack.pushBack(e);
		}
	}
	return _enemysCanBeAttack;
}
Vector<Plant*> Tower::getAllCanBeAttackPlant(){

	_plantsCanBeAttack.clear();

	for(Plant* p : GameData::getInstance()->_plantsVector){
		//由于植物sprite锚点在左下角
		//为了对称，计算位置的时候选取sprite中点(0.5,0.5)
		Point plantPos = Point(
			p->getPositionX() + p->_sprite->getContentSize().width / 2,
			p->getPositionY() + p->_sprite->getContentSize().height / 2
			);
		Point towerPos = this->getPosition();
		int dis = ccpDistance(plantPos,towerPos);
		if(dis < this->_attackDistance){
			_plantsCanBeAttack.pushBack(p);
		}
	}
	return _plantsCanBeAttack;
}
void Tower::initTower(int towerNo,int money,float attackValue,int distance,int level,int type)
{
	this->_towerNo = towerNo;
	this->_money = money;
	this->_attackValue = attackValue;
	this->_attackDistance = distance + 30 * (level - 1);
	this->_towerLevel = level;			
	this->_towerType = type;

	//由于线性塔没有攻击时间间隔，所以用伤害 x2 来替代
	if(_towerType == LINE_SINGLE)
	{
		this->_attackValue * GameData::getInstance()->_currentSpeed;
	}
	
	//攻击值随着塔等级提升而提升
	switch (_towerType)
	{
	case BULLET_AOE:
		this->_attackValue = this->_attackValue + (level - 1) * this->_attackValue;
		break;
	case BULLET_SINGLE:
		this->_attackValue = this->_attackValue + (level - 1) * this->_attackValue;
		break;
	case CIRCLE_AOE:
		this->_attackValue = this->_attackValue + (level - 1) * this->_attackValue;
		break;
	case LINE_SINGLE:
		this->_attackValue = this->_attackValue + (level - 1) * this->_attackValue;
		break;
	case LINE_AOE:
		this->_attackValue = this->_attackValue + (level - 1) * this->_attackValue;
		break;
	default:
		break;
	}

	char tempStr[15] = {0};
	sprintf(tempStr,"pt%d_%d.png",this->_towerNo,this->_towerLevel);
	this->_sprite = Sprite::createWithSpriteFrameName(tempStr);
	sprintf(tempStr,"dz%d_%d.png",this->_towerNo,this->_towerLevel);
	this->_dizuo = Sprite::createWithSpriteFrameName(tempStr);
	
	//子弹animation
	sprintf(tempStr,"zd%d_%d.png",this->_towerNo,this->_towerLevel);
	float animateTime = 0.5;
	float numOfpng = 5;
	if(this->_towerType == CIRCLE_AOE)
	{
		animateTime += 0.1;
		numOfpng += 1;
	}
	AnimationUtil::getInstance()->initAnimationBySplitIMG(tempStr,animateTime,numOfpng);

	//子弹攻击动画
	sprintf(tempStr,"eff%d.png",this->_towerNo);
	AnimationUtil::getInstance()->initAnimationBySplitIMG(tempStr,0.6,6);

	this->addChild(this->_dizuo,0);
	this->addChild(this->_sprite,1);

}

// ====================== TowerFactory ============================

Tower* TowerFactory::createTower(int towerNo,int money,int level){
	switch (towerNo)
	{
	case 1:
		return Tower1::createTower(towerNo,money,level);
		break;
	case 2:
		return Tower2::createTower(towerNo,money,level);
		break;
	case 3:
		return Tower3::createTower(towerNo,money,level);
		break;
	case 4:
		return Tower4::createTower(towerNo,money,level);
		break;
	case 5:
		return Tower5::createTower(towerNo,money,level);
		break;
	case 6:
		return Tower6::createTower(towerNo,money,level);
		break;
	case 7:
		return Tower7::createTower(towerNo,money,level);
		break;
	case 8:
		return Tower8::createTower(towerNo,money,level);
		break;
	case 9:
		return Tower9::createTower(towerNo,money,level);
		break;
	case 10:
		return Tower10::createTower(towerNo,money,level);
		break;
	case 11:
		return Tower11::createTower(towerNo,money,level);
		break;
	case 12:
		return Tower12::createTower(towerNo,money,level);
		break;
	case 13:
		return Tower13::createTower(towerNo,money,level);
		break;
	case 14:
		return Tower14::createTower(towerNo,money,level);
		break;
	case 15:
		return Tower15::createTower(towerNo,money,level);
		break;
	default:
		return NULL;
		break;
	}
}

// ===================== Tower1 ============================


void Tower::changeTowerLogicTime(float time){
	this->unschedule(_schedule);
	this->schedule(_schedule,time);
}
Tower* Tower1::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,1,130,level,BULLET_AOE);

	tower->_logicTime = 1.0 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower1::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);

	return tower;

}

void Tower1::towerLogic(float dt){

	/*
	if(typeid(this) == typeid(Tower1*)){
		CCLOG("Tower1*");
	}
	if(typeid(this) == typeid(Tower*)){
		CCLOG("Tower*");
	}

	Tower* tower = this;
	*/

	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		//因为植物的sprite锚点设置为0，
		//所以当为植物的时候需要稍微改动一下射击方向为sprite中心(0.5,0.5)
		//所以先标记一下，下面处理
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}
		
	//发射子弹
	if(target != NULL){

		char str[15] = {0};
		sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);
		
		Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
		bullet->setPosition(this->getPosition());
		this->getParent()->addChild(bullet);
		GameData::getInstance()->_bulletVector.pushBack(bullet);

		bullet->playAnimate(str,5);
		
		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
		}
		//标准化向量(向量长度为1)
		Point normalizedVector = ccpNormalize(shootVector);
		Point overShootVector = normalizedVector * 900;
		//超出屏幕的点
		Point offScreenPoint = this->getPosition() + overShootVector;
		auto move = MoveTo::create(2.5,offScreenPoint);

		CallFunc* moveDone = CallFunc::create(CC_CALLBACK_0(Tower1::shootFinish,this,bullet));

		bullet->runAction(Sequence::create(move,moveDone,NULL));
	}

}

void Tower1::shootFinish(Node* pNode){
	Bullet* bullet = (Bullet*)pNode;
	if(bullet != NULL)
	{
		bullet->_sprite->stopAllActions();
		bullet->removeChild(bullet->_sprite);
		bullet->getParent()->removeChild(bullet,true);
		GameData::getInstance()->_bulletVector.eraseObject(bullet);
	}
}

// ===================== Tower2 ============================

Tower* Tower2::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,10,130,level,CIRCLE_AOE);
	tower->_isCreateBullet = false;
	tower->_logicTime = 1.3 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower2::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);

	return tower;

}

void Tower2::towerLogic(float dt){
	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		//因为植物的sprite锚点设置为0，
		//所以当为植物的时候需要稍微改动一下射击方向为sprite中心(0.5,0.5)
		//所以先标记一下，下面处理
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}

	//发射子弹
	if(target != NULL){

		char str[15] = {0};
		sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);

		//创建子弹
		if(this->_isCreateBullet == false){

			Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
			bullet->setTag(CIRCLE_AOE_TAG);
			this->addChild(bullet);
			bullet->playAnimate(str,1);
			this->_isCreateBullet = true;

		}else{
			((Bullet*)this->getChildByTag(CIRCLE_AOE_TAG))->playAnimate(str,1);
		}

		//因为是AOE伤害，所以遍历plant 和 enemy
		//plant
		for(Plant* p : GameData::getInstance()->_plantsVector)
		{
			Point plantPos = Point(
				p->getPositionX() + p->_sprite->getContentSize().width / 2,
				p->getPositionY() + p->_sprite->getContentSize().height / 2);
			Point towerPos = this->getPosition();
			int dis = ccpDistance(plantPos,towerPos);
			if(dis < this->_attackDistance)
			{
				if(p->getLife() > 0)
				{
					p->sliderShow();
					p->getHurt(this->_attackValue);
					sprintf(str,"eff%d.png",this->_towerNo);
					p->playAnimate(str);
				}
				else if(p->getLife() == 0)
				{
					//更新主界面金币标签
					GameData::getInstance()->_currentMoney += p->_money;
					sprintf(str,"%d",GameData::getInstance()->_currentMoney);
					((MainScene*) ( this->getParent()->getParent() ) )->_moneyLabel->setString(str);
					//die
					p->die();
				}	
			}
			
		}//end plant

		//enemy
		for(Enemy* e : GameData::getInstance()->_enemysVector)
		{
			Point enemyPos = e->getPosition();
			Point towerPos = this->getPosition();
			int dis = ccpDistance(enemyPos,towerPos);
			if(dis < this->_attackDistance)
			{
				if(e->getLife() > 0)
				{
					e->sliderShow();
					e->getHurt(this->_attackValue);
					sprintf(str,"eff%d.png",this->_towerNo);
					e->playAnimate(str);
				}
				else if(e->getLife() == 0)
				{
					//更新主界面金币标签
					GameData::getInstance()->_currentMoney += e->_money;
					sprintf(str,"%d",GameData::getInstance()->_currentMoney);
					((MainScene*) ( this->getParent()->getParent() ) )->_moneyLabel->setString(str);
					//die
					e->die();
				}
			}
		}//end enemy

	}
}

// ===================== Tower3 ============================
Tower* Tower3::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
 	tower->initTower(towerNo,money,10,130,level,BULLET_SINGLE);
	tower->_logicTime = 1.0 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower3::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);

	return tower;
}

void Tower3::towerLogic(float dt){
	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		//因为植物的sprite锚点设置为0，
		//所以当为植物的时候需要稍微改动一下射击方向为sprite中心(0.5,0.5)
		//所以先标记一下，下面处理
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}

	if(target != NULL)
	{
		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
		}
		
		//向量标准化(即向量长度为1)  
		Point normalizedVector = ccpNormalize(shootVector) ;  
		//算出旋转的弧度  
		float radians = atan2(normalizedVector.y, normalizedVector.x);  
		//将弧度转换成角度  
		float degree = CC_RADIANS_TO_DEGREES(radians); 

		//匀速旋转需要我们设置一下速度，这里假设旋转速度为 2π (rad/s)  
		float rotateSpeed = 4 * M_PI;  
		//那么旋转1弧度所用时间为  
		float rotate_1rad_time = 1 / rotateSpeed;  
		//所以旋转的时长为  
		float rotateDuration = fabs(radians * rotate_1rad_time);  

		auto rotate = RotateTo::create(rotateDuration,(degree- 90) * -1);
		auto rotateDone = CallFunc::create(CC_CALLBACK_0(Tower3::shootBullet,this,target,shootVector));

		_sprite->runAction(	Sequence::create(rotate,rotateDone,NULL));
	
	}
}

void Tower3::shootBullet(Node* pNode,Point pos){
	
	Node* target = pNode;
	Point shootVector =pos;

	char str[15] = {0};
	sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);

	Bullet* bullet1 = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
	if(bullet1 == NULL)
		return;
	bullet1->setPosition(this->getPosition());
	this->getParent()->addChild(bullet1);
	GameData::getInstance()->_bulletVector.pushBack(bullet1);

	Bullet* bullet2 = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
	bullet2->setPosition(this->getPosition());
	this->getParent()->addChild(bullet2);
	GameData::getInstance()->_bulletVector.pushBack(bullet2);

	Bullet* bullet3 = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
	bullet3->setPosition(this->getPosition());
	this->getParent()->addChild(bullet3);
	GameData::getInstance()->_bulletVector.pushBack(bullet3);


	bullet1->playAnimate(str,5);
	bullet2->playAnimate(str,5);
	bullet3->playAnimate(str,5);

	//先算出敌人方向的向量
	Point normalizedVector = ccpNormalize(shootVector);
	float radians = atan2(normalizedVector.y,  normalizedVector.x);   
	float degree = CC_RADIANS_TO_DEGREES(radians); 

	//再算出子弹分别射击的向量点
	float degree1 = degree;
	float degree2 = degree + 20;
	float degree3 = degree - 20;
	float radians1 = CC_DEGREES_TO_RADIANS(degree1);
	float radians2 = CC_DEGREES_TO_RADIANS(degree2);
	float radians3 = CC_DEGREES_TO_RADIANS(degree3);
	float x1,x2,x3,y1,y2,y3;
	//degree1
	if(degree1 == 90 || degree1 == -90){
		x1 = 0;
		y1 = degree1 > 0 ? 1:-1 ;
	}else if(degree1 >= 0 && degree1 < 90 ){//象限1
		x1 = 1;
		y1 = tan(radians1);
	}
	else if(degree1 > 90 && degree1 <= 180 ){//象限2
		x1 = -1;
		y1 = tan(radians1) * -1;
	}
	else if(degree1 >= -180 && degree1 < -90 ){//象限3
		x1 = -1;
		y1 = tan(radians1) * -1;
	}
	else if(degree1 > -90 && degree1 < 0 ){//象限4
		x1 = 1;
		y1 = tan(radians1);
	}
	//degree2
	if(degree2 == 90 || degree2 == -90){
		x2 = 0;
		y2 = degree2 > 0 ? 1:-1 ;
	}
	else if(degree2 >= 0 && degree2 < 90 ){//象限1
		x2 = 1;
		y2 = tan(radians2);
	}
	else if(degree2 > 90 && degree2 <= 180 ){//象限2
		x2 = -1;
		y2 = tan(radians2) * -1;
	}
	else if(degree2 >= -180 && degree2 < -90 ){//象限3
		x2 = -1;
		y2 = tan(radians2) * -1;
	}
	else if(degree2 > -90 && degree2 < 0 ){//象限4
		x2 = 1;
		y2 = tan(radians2);
	}
	//degree3
	if(degree3 == 90 || degree3 == -90){
		x3 = 0;
		y3 = degree3 > 0 ? 1:-1 ;
	}
	else if(degree3 >= 0 && degree3 < 90 ){//象限1
		x3 = 1;
		y3 = tan(radians3);
	}
	else if(degree3 > 90 && degree3 <= 180 ){//象限2
		x3 = -1;
		y3 = tan(radians3) * -1;
	}
	else if(degree3 >= -180 && degree3 < -90 ){//象限3
		x3 = -1;
		y3 = tan(radians3) * -1;
	}
	else if(degree3 > -90 && degree3 < 0 ){//象限4
		x3 = 1;
		y3 = tan(radians3);
	}
	Point normalizedVector1 = ccpNormalize(Point(x1,y1));
	Point normalizedVector2 = ccpNormalize(Point(x2,y2));
	Point normalizedVector3 = ccpNormalize(Point(x3,y3));
	Point overShootVector1 = normalizedVector1 * 900;
	Point overShootVector2 = normalizedVector2 * 900;
	Point overShootVector3 = normalizedVector3 * 900;
	Point offScreenPoint1 = this->getPosition() + overShootVector1;
	Point offScreenPoint2 = this->getPosition() + overShootVector2;
	Point offScreenPoint3 = this->getPosition() + overShootVector3;

	auto move1 = MoveTo::create(2.5,offScreenPoint1);
	auto move2 = MoveTo::create(2.5,offScreenPoint2);
	auto move3 = MoveTo::create(2.5,offScreenPoint3);

	CallFunc* moveDone1 = CallFunc::create(CC_CALLBACK_0(Tower3::shootFinish,this,bullet1));
	CallFunc* moveDone2 = CallFunc::create(CC_CALLBACK_0(Tower3::shootFinish,this,bullet2));
	CallFunc* moveDone3 = CallFunc::create(CC_CALLBACK_0(Tower3::shootFinish,this,bullet3));

	bullet1->runAction(Sequence::create(move1,moveDone1,NULL));
	bullet2->runAction(Sequence::create(move2,moveDone2,NULL));
	bullet3->runAction(Sequence::create(move3,moveDone3,NULL));
	
}

void Tower3::shootFinish(Node* pNode){
	Bullet* bullet = (Bullet*)pNode;
	if(bullet != NULL){
		bullet->_sprite->stopAllActions();
		bullet->removeChild(bullet->_sprite);
		bullet->getParent()->removeChild(bullet,true);
		GameData::getInstance()->_bulletVector.eraseObject(bullet);
	}
}
// ===================== Tower4 ============================

Tower* Tower4::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,0.2,150,level,LINE_SINGLE);
	tower->_isCreateBullet = false;

	tower->_logicTime = 0.0 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower4::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);

	return tower;

}

void Tower4::towerLogic(float dt){

	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}

	//发射子弹
	if(target != NULL){

		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		//距离
		float bulletAttackDis = ccpDistance(target->getPosition() , this->getPosition());
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
			bulletAttackDis = ccpDistance(target->getPosition() + spriteCenterPos , this->getPosition());
		}

		//向量标准化(即向量长度为1)  
		Point normalizedVector = ccpNormalize(shootVector) ;  
		//算出旋转的弧度  
		float radians = atan2(normalizedVector.y, normalizedVector.x);  
		//将弧度转换成角度  
		float degree = CC_RADIANS_TO_DEGREES(radians); 

		char str[15] = {0};
		sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);

		//将敌人和塔的距离设置为子弹的长度 bulletAttackDis
		
		//创建子弹
		if(this->_isCreateBullet == false){
			Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
			bullet->setTag(LINE_SINGLE_TAG);
			this->addChild(bullet);
			_isCreateBullet = true;

		}

		Bullet* bullet = ((Bullet*)this->getChildByTag(LINE_SINGLE_TAG));
		bullet->setVisible(true);
		
		//更新子弹动画长度
		auto size = ((Bullet*)this->getChildByTag(LINE_SINGLE_TAG))->_sprite->getContentSize();
		Rect rect = Rect(
			0,0,size.width,bulletAttackDis + 30);
		bullet->_spriteRect = rect;
		
		//旋转
		this->getChildByTag(LINE_SINGLE_TAG)->setRotation((degree- 90) * -1);

		//计算伤害
		if (plantFlag){
			Plant* p = ((Plant*)target);
			if(p->getLife() > 0)
			{
				p->sliderShow();
				p->getHurt(this->_attackValue);
				sprintf(str,"eff%d.png",this->_towerNo);
				p->playAnimate(str);
			}
			else if(p->getLife() == 0)
			{
				//更新主界面金币标签
				GameData::getInstance()->_currentMoney += p->_money;
				sprintf(str,"%d",GameData::getInstance()->_currentMoney);
				((MainScene*) ( this->getParent()->getParent() ) )->_moneyLabel->setString(str);
				//die
				p->die();
			}	
		}
		//enemy
		else
		{
			Enemy* e = ((Enemy*)target);
			if(e->getLife() > 0)
			{
				e->sliderShow();
				e->getHurt(this->_attackValue);
				sprintf(str,"eff%d.png",this->_towerNo);
				e->playAnimate(str);
			}
			else if(e->getLife() == 0)
			{
				//更新主界面金币标签
				GameData::getInstance()->_currentMoney += e->_money;
				sprintf(str,"%d",GameData::getInstance()->_currentMoney);
				((MainScene*) ( this->getParent()->getParent() ) )->_moneyLabel->setString(str);
				//die
				e->die();
			}
		}

		
	}else{
		//创建子弹
		if(this->_isCreateBullet == true){
			Bullet* bullet = ((Bullet*)this->getChildByTag(LINE_SINGLE_TAG));
			bullet->setVisible(false);
		}
	}
}

// ===================== Tower5 ============================

Tower* Tower5::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,1,150,level,BULLET_AOE);
	tower->_logicTime = 1.0 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower5::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);
	return tower;

}

void Tower5::towerLogic(float dt){
	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}
	//发射子弹
	if(target != NULL){

		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
		}

		//向量标准化(即向量长度为1)  
		Point normalizedVector = ccpNormalize(shootVector) ;  
		//算出旋转的弧度  
		float radians = atan2(normalizedVector.y, normalizedVector.x);  
		//将弧度转换成角度  
		float degree = CC_RADIANS_TO_DEGREES(radians); 

		//匀速旋转需要我们设置一下速度，这里假设旋转速度为 2π (rad/s)  
		float rotateSpeed = 4 * M_PI;  
		//那么旋转1弧度所用时间为  
		float rotate_1rad_time = 1 / rotateSpeed;  
		//所以旋转的时长为  
		float rotateDuration = fabs(radians * rotate_1rad_time);  

		auto rotate = RotateTo::create(rotateDuration,(degree- 90) * -1);
		
		auto rotateDone = CallFunc::create(CC_CALLBACK_0(Tower5::shootBullet,this,target,shootVector));
		
		_sprite->runAction(	Sequence::create(rotate,rotateDone,NULL));
	}
}

void Tower5::shootBullet(Node* pTarget,Point pos){

	//敌人
	Node* target = pTarget;

	//旋转角度
	Point shootVector =pos;
	Point normalizedVector = ccpNormalize(shootVector) ;  
	float radians = atan2(normalizedVector.y, normalizedVector.x);  
	float degree = CC_RADIANS_TO_DEGREES(radians); 

	char str[15] = {0};
	sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);
	
	Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
	if(bullet == NULL )
		return;
	bullet->setPosition(this->getPosition());
	bullet->setRotation((degree- 90) * -1);
	this->getParent()->addChild(bullet);
	GameData::getInstance()->_bulletVector.pushBack(bullet);
	
	bullet->playAnimate(str,5);

	Point overShootVector = normalizedVector * 900;
	Point offScreenPoint = this->getPosition() + overShootVector;

	auto move = MoveTo::create(2.5,offScreenPoint);
	CallFunc* moveDone = CallFunc::create(CC_CALLBACK_0(Tower5::shootFinish,this,bullet));

	bullet->runAction(Sequence::create(move,moveDone,NULL));
}

void Tower5::shootFinish(Node* pNode){
	Bullet* bullet = (Bullet*)pNode;
	if(bullet != NULL)
	{
		bullet->_sprite->stopAllActions();
		bullet->removeChild(bullet->_sprite);
		bullet->getParent()->removeChild(bullet,true);
		GameData::getInstance()->_bulletVector.eraseObject(bullet);
	}
}

// ===================== Tower6 ============================

Tower* Tower6::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,5,150,level,BULLET_SINGLE);
	tower->_logicTime = 1.0 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower6::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);

	return tower;
}

void Tower6::towerLogic(float dt){
	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}
	if(target != NULL)
	{
		char str[15] = {0};
		sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);
	
		for(int i = 0; i < 8; i++)
		{
			Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
			if(bullet == NULL){
				return;
			}
			bullet->setPosition(this->getPosition());
			this->getParent()->addChild(bullet);
			GameData::getInstance()->_bulletVector.pushBack(bullet);

			float degree = i * 45.0;
			bullet->setRotation((degree - 90)*-1);
			bullet->playAnimate(str,5);

			//计算向量
			float radians = CC_DEGREES_TO_RADIANS(degree);
			float x,y;
			if(degree >= 0 && degree < 90 ){			//象限1
				x = 1;
				y = tan(radians);	
			}
			else if (degree == 90){						//90
				x = 0;
				y = 1;
			}
			else if(degree > 90 && degree <= 180 ){		//象限2
				x = -1;
				y = tan(radians) * -1;
			}
			else if(degree > 180 && degree < 270 ){		//象限3
				x = -1;
				y = tan(radians) * -1;
			}
			else if(degree == 270){                     //270
				x = 0;
				y = -1;
			}
			else if(degree > 270 && degree < 360 ){		//象限4
				x = 1;
				y = tan(radians);
			}

			Point shootVector = Point(x,y);
			Point normalizedVector = ccpNormalize(shootVector); 
			Point overShootVector = normalizedVector * 900;
			Point offScreenPoint = this->getPosition() + overShootVector;

			auto move = MoveTo::create(2.5,offScreenPoint);
			auto moveDone = CallFunc::create(CC_CALLBACK_0(Tower6::shootFinish,this,bullet));

			bullet->runAction(Sequence::create(move,moveDone,NULL));
		}
		
	}

}

void Tower6::shootFinish(Node* pNode){
	Bullet* bullet = (Bullet*)pNode;
	if(bullet != NULL){
		bullet->_sprite->stopAllActions();
		bullet->removeChild(bullet->_sprite);
		bullet->getParent()->removeChild(bullet,true);
		GameData::getInstance()->_bulletVector.eraseObject(bullet);
	}
}

//===================== Tower7 =============================

Tower* Tower7::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,10,150,level,BULLET_SINGLE);
	tower->_logicTime = 1.0 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower7::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);
	return tower;
}

void Tower7::towerLogic(float dt){
	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}

	if(target != NULL)
	{
		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
		}

		//向量标准化(即向量长度为1)  
		Point normalizedVector = ccpNormalize(shootVector) ;  
		//算出旋转的弧度  
		float radians = atan2(normalizedVector.y, normalizedVector.x);  
		//将弧度转换成角度  
		float degree = CC_RADIANS_TO_DEGREES(radians); 

		//匀速旋转需要我们设置一下速度，这里假设旋转速度为 2π (rad/s)  
		float rotateSpeed = 4 * M_PI;  
		//那么旋转1弧度所用时间为  
		float rotate_1rad_time = 1 / rotateSpeed;  
		//所以旋转的时长为  
		float rotateDuration = fabs(radians * rotate_1rad_time);  

		auto rotate = RotateTo::create(rotateDuration,(degree- 90) * -1);
		auto rotateDone = CallFunc::create(CC_CALLBACK_0(Tower7::shootBullet,this,target,shootVector));

		_sprite->runAction(	Sequence::create(rotate,rotateDone,NULL));
	}
}

void Tower7::shootBullet(Node* pNode,Point pos){

	Node* target = pNode;
	Point shootVector =pos;

	char str[15] = {0};
	sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);

	Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
	if(bullet == NULL)
		return;
	bullet->setPosition(this->getPosition());
	this->getParent()->addChild(bullet);
	GameData::getInstance()->_bulletVector.pushBack(bullet);
	bullet->playAnimate(str,5);
	
	Point normalizedVector = ccpNormalize(shootVector);
	Point overShootVector = normalizedVector * 900;
	Point offScreenPoint = this->getPosition() + overShootVector;
	
	auto move = MoveTo::create(2.5,offScreenPoint);
	CallFunc* moveDone = CallFunc::create(CC_CALLBACK_0(Tower7::shootFinish,this,bullet));
	
	bullet->runAction(Sequence::create(move,moveDone,NULL));
}

void Tower7::shootFinish(Node* pNode){
	Bullet* bullet = (Bullet*)pNode;
	if(bullet != NULL){
		bullet->_sprite->stopAllActions();
		bullet->removeChild(bullet->_sprite);
		bullet->getParent()->removeChild(bullet,true);
		GameData::getInstance()->_bulletVector.eraseObject(bullet);
	}
}

//===================== Tower8 =============================

Tower* Tower8::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,1,150,level,BULLET_AOE);
	tower->_logicTime = 1.0 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower8::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);

	return tower;

}
void Tower8::towerLogic(float dt){

	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}
		
	//发射子弹
	if(target != NULL){

		auto rotate1 = RotateTo::create(0.2f,20);
		auto rotate2 = RotateTo::create(0.2f,-20);
		_sprite->runAction(Sequence::create(rotate1,rotate2,NULL));
		
		char str[15] = {0};
		sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);
		
		Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
		bullet->setPosition(this->getPosition());
		this->getParent()->addChild(bullet);
		GameData::getInstance()->_bulletVector.pushBack(bullet);

		bullet->playAnimate(str,5);
		
		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
		}
		//标准化向量(向量长度为1)
		Point normalizedVector = ccpNormalize(shootVector);
		Point overShootVector = normalizedVector * 900;
		//超出屏幕的点
		Point offScreenPoint = this->getPosition() + overShootVector;
		auto move = MoveTo::create(2.5,offScreenPoint);

		CallFunc* moveDone = CallFunc::create(CC_CALLBACK_0(Tower8::shootFinish,this,bullet));

		bullet->runAction(Sequence::create(move,moveDone,NULL));
	}

}

void Tower8::shootFinish(Node* pNode){
	Bullet* bullet = (Bullet*)pNode;
	if(bullet != NULL)
	{
		bullet->_sprite->stopAllActions();
		bullet->removeChild(bullet->_sprite);
		bullet->getParent()->removeChild(bullet,true);
		GameData::getInstance()->_bulletVector.eraseObject(bullet);
	}
}

//===================== Tower9 =============================

Tower* Tower9::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,1,150,level,BULLET_AOE);
	tower->_logicTime = 1.0 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower9::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);

	return tower;

}

void Tower9::towerLogic(float dt){
	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}
	//发射子弹
	if(target != NULL){

		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
		}

		//向量标准化(即向量长度为1)  
		Point normalizedVector = ccpNormalize(shootVector) ;  
		//算出旋转的弧度  
		float radians = atan2(normalizedVector.y, normalizedVector.x);  
		//将弧度转换成角度  
		float degree = CC_RADIANS_TO_DEGREES(radians); 

		//匀速旋转需要我们设置一下速度，这里假设旋转速度为 2π (rad/s)  
		float rotateSpeed = 4 * M_PI;  
		//那么旋转1弧度所用时间为  
		float rotate_1rad_time = 1 / rotateSpeed;  
		//所以旋转的时长为  
		float rotateDuration = fabs(radians * rotate_1rad_time);  

		auto rotate = RotateTo::create(rotateDuration,(degree- 90) * -1);

		auto rotateDone = CallFunc::create(CC_CALLBACK_0(Tower9::shootBullet,this,target,shootVector));

		_sprite->runAction(	Sequence::create(rotate,rotateDone,NULL));
	}
}

void Tower9::shootBullet(Node* pTarget,Point pos){

	//敌人
	Node* target = pTarget;

	//旋转角度
	Point shootVector =pos;
	Point normalizedVector = ccpNormalize(shootVector) ;  
	float radians = atan2(normalizedVector.y, normalizedVector.x);  
	float degree = CC_RADIANS_TO_DEGREES(radians); 

	char str[15] = {0};
	sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);

	Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
	if(bullet == NULL )
		return;
	bullet->setPosition(this->getPosition());
	bullet->setRotation((degree- 90) * -1);
	this->getParent()->addChild(bullet);
	GameData::getInstance()->_bulletVector.pushBack(bullet);

	bullet->playAnimate(str,5);

	Point overShootVector = normalizedVector * 900;
	Point offScreenPoint = this->getPosition() + overShootVector;

	auto move = MoveTo::create(2.5,offScreenPoint);
	CallFunc* moveDone = CallFunc::create(CC_CALLBACK_0(Tower9::shootFinish,this,bullet));

	bullet->runAction(Sequence::create(move,moveDone,NULL));
}

void Tower9::shootFinish(Node* pNode){
	Bullet* bullet = (Bullet*)pNode;
	if(bullet != NULL)
	{
		bullet->_sprite->stopAllActions();
		bullet->removeChild(bullet->_sprite);
		bullet->getParent()->removeChild(bullet,true);
		GameData::getInstance()->_bulletVector.eraseObject(bullet);
	}
}

//===================== Tower10 =============================

Tower* Tower10::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,0.2,150,level,LINE_SINGLE);
	tower->_isCreateBullet = false;
	tower->_logicTime = 0.0 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower10::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);
	
	return tower;
}

void Tower10::towerLogic(float dt){

	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}
	//发射子弹
	if(target != NULL){

		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		//距离
		float bulletAttackDis = ccpDistance(target->getPosition() , this->getPosition());
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
			bulletAttackDis = ccpDistance(target->getPosition() + spriteCenterPos , this->getPosition());
		}

		//向量标准化(即向量长度为1)  
		Point normalizedVector = ccpNormalize(shootVector) ;  
		//算出旋转的弧度  
		float radians = atan2(normalizedVector.y, normalizedVector.x);  
		//将弧度转换成角度  
		float degree = CC_RADIANS_TO_DEGREES(radians); 

		char str[15] = {0};
		sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);

		//将敌人和塔的距离设置为子弹的长度 bulletAttackDis

		//创建子弹
		if(this->_isCreateBullet == false){
			Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
			bullet->setTag(LINE_SINGLE_TAG);
			this->addChild(bullet);
			_isCreateBullet = true;

		}
		
		_sprite->setRotation( (degree - 90) * -1);

		Bullet* bullet = ((Bullet*)this->getChildByTag(LINE_SINGLE_TAG));
		bullet->setVisible(true);


		//更新子弹动画长度
		auto size = ((Bullet*)this->getChildByTag(LINE_SINGLE_TAG))->_sprite->getContentSize();
		Rect rect = Rect(
			0,0,size.width,bulletAttackDis + 30);
		bullet->_spriteRect = rect;

		//旋转
		this->getChildByTag(LINE_SINGLE_TAG)->setRotation((degree- 90) * -1);

		//计算伤害
		if (plantFlag){
			Plant* p = ((Plant*)target);
			if(p->getLife() > 0)
			{
				p->sliderShow();
				p->getHurt(this->_attackValue);
				sprintf(str,"eff%d.png",this->_towerNo);
				p->playAnimate(str);
			}
			else if(p->getLife() == 0)
			{
				//更新主界面金币标签
				GameData::getInstance()->_currentMoney += p->_money;
				sprintf(str,"%d",GameData::getInstance()->_currentMoney);
				((MainScene*) ( this->getParent()->getParent() ) )->_moneyLabel->setString(str);
				//die
				p->die();
			}	
		}
		//enemy
		else
		{
			Enemy* e = ((Enemy*)target);
			if(e->getLife() > 0)
			{
				e->sliderShow();
				e->getHurt(this->_attackValue);
				sprintf(str,"eff%d.png",this->_towerNo);
				e->playAnimate(str);
			}
			else if(e->getLife() == 0)
			{
				//更新主界面金币标签
				GameData::getInstance()->_currentMoney += e->_money;
				sprintf(str,"%d",GameData::getInstance()->_currentMoney);
				((MainScene*) ( this->getParent()->getParent() ) )->_moneyLabel->setString(str);
				//die
				e->die();
			}
		}


	}else{
		//创建子弹
		if(this->_isCreateBullet == true){
			Bullet* bullet = ((Bullet*)this->getChildByTag(LINE_SINGLE_TAG));
			bullet->setVisible(false);
		}
	}
}

//===================== Tower11 =============================

Tower* Tower11::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,5,150,level,BULLET_AOE);
	tower->_logicTime = 1.0 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower11::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);

	return tower;

}

void Tower11::towerLogic(float dt){
	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}
	//发射子弹
	if(target != NULL){

		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
		}

		//向量标准化(即向量长度为1)  
		Point normalizedVector = ccpNormalize(shootVector) ;  
		//算出旋转的弧度  
		float radians = atan2(normalizedVector.y, normalizedVector.x);  
		//将弧度转换成角度  
		float degree = CC_RADIANS_TO_DEGREES(radians); 

		//匀速旋转需要我们设置一下速度，这里假设旋转速度为 2π (rad/s)  
		float rotateSpeed = 4 * M_PI;  
		//那么旋转1弧度所用时间为  
		float rotate_1rad_time = 1 / rotateSpeed;  
		//所以旋转的时长为  
		float rotateDuration = fabs(radians * rotate_1rad_time);  

		auto rotate = RotateTo::create(rotateDuration,(degree- 90) * -1);

		auto rotateDone = CallFunc::create(CC_CALLBACK_0(Tower11::shootBullet,this,target,shootVector));

		_sprite->runAction(	Sequence::create(rotate,rotateDone,NULL));
	}
}

void Tower11::shootBullet(Node* pTarget,Point pos){

	//敌人
	Node* target = pTarget;

	//旋转角度
	Point shootVector =pos;
	Point normalizedVector = ccpNormalize(shootVector) ;  
	float radians = atan2(normalizedVector.y, normalizedVector.x);  
	float degree = CC_RADIANS_TO_DEGREES(radians); 

	char str[15] = {0};
	sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);

	Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
	if(bullet == NULL )
		return;
	bullet->setPosition(this->getPosition());
	bullet->setRotation((degree- 90) * -1);
	this->getParent()->addChild(bullet);
	GameData::getInstance()->_bulletVector.pushBack(bullet);

	bullet->playAnimate(str,5);

	Point overShootVector = normalizedVector * 900;
	Point offScreenPoint = this->getPosition() + overShootVector;

	auto move = MoveTo::create(1.5,offScreenPoint);
	CallFunc* moveDone = CallFunc::create(CC_CALLBACK_0(Tower11::shootFinish,this,bullet));

	bullet->runAction(Sequence::create(move,moveDone,NULL));
}

void Tower11::shootFinish(Node* pNode){
	Bullet* bullet = (Bullet*)pNode;
	if(bullet != NULL){
		bullet->_sprite->stopAllActions();
		bullet->removeChild(bullet->_sprite);
		bullet->getParent()->removeChild(bullet,true);
		GameData::getInstance()->_bulletVector.eraseObject(bullet);
	}
}

//===================== Tower12 =============================

Tower* Tower12::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,1,150,level,BULLET_AOE);
	tower->_logicTime = 1.0 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower12::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);

	return tower;

}

void Tower12::towerLogic(float dt){
	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}
	//发射子弹
	if(target != NULL){

		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
		}

		//向量标准化(即向量长度为1)  
		Point normalizedVector = ccpNormalize(shootVector) ;  
		//算出旋转的弧度  
		float radians = atan2(normalizedVector.y, normalizedVector.x);  
		//将弧度转换成角度  
		float degree = CC_RADIANS_TO_DEGREES(radians); 

		//匀速旋转需要我们设置一下速度，这里假设旋转速度为 2π (rad/s)  
		float rotateSpeed = 4 * M_PI;  
		//那么旋转1弧度所用时间为  
		float rotate_1rad_time = 1 / rotateSpeed;  
		//所以旋转的时长为  
		float rotateDuration = fabs(radians * rotate_1rad_time);  

		auto rotate = RotateTo::create(rotateDuration,(degree- 90) * -1);

		auto rotateDone = CallFunc::create(CC_CALLBACK_0(Tower12::shootBullet,this,target,shootVector));

		_sprite->runAction(	Sequence::create(rotate,rotateDone,NULL));
	}
}

void Tower12::shootBullet(Node* pTarget,Point pos){

	//敌人
	Node* target = pTarget;

	//旋转角度
	Point shootVector =pos;
	Point normalizedVector = ccpNormalize(shootVector) ;  
	float radians = atan2(normalizedVector.y, normalizedVector.x);  
	float degree = CC_RADIANS_TO_DEGREES(radians); 

	char str[15] = {0};
	sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);

	Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
	if(bullet == NULL )
		return;
	bullet->setPosition(this->getPosition());
	bullet->setRotation((degree- 90) * -1);
	this->getParent()->addChild(bullet);
	GameData::getInstance()->_bulletVector.pushBack(bullet);

	bullet->playAnimate(str,5);

	Point overShootVector = normalizedVector * 900;
	Point offScreenPoint = this->getPosition() + overShootVector;

	auto move = MoveTo::create(2.5,offScreenPoint);
	CallFunc* moveDone = CallFunc::create(CC_CALLBACK_0(Tower12::shootFinish,this,bullet));

	bullet->runAction(Sequence::create(move,moveDone,NULL));
}

void Tower12::shootFinish(Node* pNode){
	Bullet* bullet = (Bullet*)pNode;
	if(bullet != NULL){
		bullet->_sprite->stopAllActions();
		bullet->removeChild(bullet->_sprite);
		bullet->getParent()->removeChild(bullet,true);
		GameData::getInstance()->_bulletVector.eraseObject(bullet);
	}
}

//===================== Tower13 =============================

Tower* Tower13::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,5,150,level,BULLET_SINGLE);
	tower->_logicTime = 0.6 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower13::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);

	return tower;

}

void Tower13::towerLogic(float dt){
	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}
	//发射子弹
	if(target != NULL){

		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
		}

		//向量标准化(即向量长度为1)  
		Point normalizedVector = ccpNormalize(shootVector) ;  
		//算出旋转的弧度  
		float radians = atan2(normalizedVector.y, normalizedVector.x);  
		//将弧度转换成角度  
		float degree = CC_RADIANS_TO_DEGREES(radians); 

		//匀速旋转需要我们设置一下速度，这里假设旋转速度为 2π (rad/s)  
		float rotateSpeed = 4 * M_PI;  
		//那么旋转1弧度所用时间为  
		float rotate_1rad_time = 1 / rotateSpeed;  
		//所以旋转的时长为  
		float rotateDuration = fabs(radians * rotate_1rad_time);  

		auto rotate = RotateTo::create(rotateDuration,(degree- 90) * -1);

		auto rotateDone = CallFunc::create(CC_CALLBACK_0(Tower13::shootBullet,this,target,shootVector));

		_sprite->runAction(	Sequence::create(rotate,rotateDone,NULL));
	}
}

void Tower13::shootBullet(Node* pTarget,Point pos){

	//敌人
	Node* target = pTarget;

	//旋转角度
	Point shootVector =pos;
	Point normalizedVector = ccpNormalize(shootVector) ;  
	float radians = atan2(normalizedVector.y, normalizedVector.x);  
	float degree = CC_RADIANS_TO_DEGREES(radians); 

	char str[15] = {0};
	sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);

	Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
	if(bullet == NULL )
		return;
	bullet->setPosition(this->getPosition());
	bullet->setRotation((degree- 90) * -1);
	this->getParent()->addChild(bullet);
	GameData::getInstance()->_bulletVector.pushBack(bullet);

	bullet->playAnimate(str,5);

	Point overShootVector = normalizedVector * 900;
	Point offScreenPoint = this->getPosition() + overShootVector;

	auto move = MoveTo::create(2.0,offScreenPoint);
	CallFunc* moveDone = CallFunc::create(CC_CALLBACK_0(Tower13::shootFinish,this,bullet));

	bullet->runAction(Sequence::create(move,moveDone,NULL));
}

void Tower13::shootFinish(Node* pNode){
	Bullet* bullet = (Bullet*)pNode;
	if(bullet != NULL){
		bullet->_sprite->stopAllActions();
		bullet->removeChild(bullet->_sprite);
		bullet->getParent()->removeChild(bullet,true);
		GameData::getInstance()->_bulletVector.eraseObject(bullet);
	}
}

//===================== Tower14 =============================

Tower* Tower14::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,15,200,level,LINE_AOE);
	tower->_isCreateBullet = false;
	tower->_logicTime = 1.5 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower14::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);

	return tower;
}

void Tower14::towerLogic(float dt){

	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}
	//发射子弹
	if(target != NULL){

		//射击方向向量
		Point shootVector = target->getPosition() - this->getPosition();
		//距离
		float bulletAttackDis = ccpDistance(target->getPosition() , this->getPosition());
		if (plantFlag)
		{
			//植物,重新设置shootVector
			Point spriteCenterPos = Point(
				((Plant*)target)->_sprite->getContentSize().width / 2,
				((Plant*)target)->_sprite->getContentSize().height / 2);

			shootVector = target->getPosition() + spriteCenterPos - this->getPosition();
			bulletAttackDis = ccpDistance(target->getPosition() + spriteCenterPos , this->getPosition());
		}

		//向量标准化(即向量长度为1)  
		Point normalizedVector = ccpNormalize(shootVector) ;  
		//算出旋转的弧度  
		float radians = atan2(normalizedVector.y, normalizedVector.x);  
		//将弧度转换成角度  
		float degree = CC_RADIANS_TO_DEGREES(radians); 

		_sprite->setRotation((degree - 90) * -1);

		char str[15] = {0};
		sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);


		//创建子弹
		if(this->_isCreateBullet == false){
			Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
			bullet->setTag(LINE_AOE_TAG);
			this->addChild(bullet);
			_isCreateBullet = true;

		}

		Bullet* bullet = ((Bullet*)this->getChildByTag(LINE_AOE_TAG));
		
		//旋转
		bullet->setRotation((degree- 90) * -1);
		//动画
		bullet->playAnimate(str,1);

		//重新设置子弹的宽度 ，为原来的一半，提高射击精确度
		Rect bulletRectTemp = bullet->_sprite->getBoundingBox();
		Rect bulletRect = Rect(
			bulletRectTemp.origin.x / 2,
			bulletRectTemp.origin.y,
			bulletRectTemp.size.width / 2,
			bulletRectTemp.size.height 
			);
		//遍历enemy 计算伤害
		for(Enemy* enemy : GameData::getInstance()->_enemysVector){

			//转为bullet节点坐标
			Point enemyPos = enemy->getPosition();
			Point posInNode = bullet->convertToNodeSpaceAR(enemyPos);
			Rect enemyRect = Rect(
				posInNode.x - enemy->_sprite->getContentSize().width / 2,
				posInNode.y - enemy->_sprite->getContentSize().height / 2,
				enemy->_sprite->getContentSize().width,
				enemy->_sprite->getContentSize().height
				);
			
			
			if(bulletRect.intersectsRect(enemyRect)){
				if(enemy->getLife() > 0)
				{
					enemy->sliderShow();
					enemy->getHurt(this->_attackValue);
					sprintf(str,"eff%d.png",this->_towerNo);
					enemy->playAnimate(str);
				}
				else if(enemy->getLife() == 0)
				{
					//更新主界面金币标签
					GameData::getInstance()->_currentMoney += enemy->_money;
					sprintf(str,"%d",GameData::getInstance()->_currentMoney);
					((MainScene*) ( this->getParent()->getParent() ) )->_moneyLabel->setString(str);
					//die
					enemy->die();
				}
			}
		}
		//遍历plant 计算伤害
		for(Plant* plant : GameData::getInstance()->_plantsVector){

			//取plant中心点
			Point plantPos = plant->getPosition();
			Point plantPosInCenter = Point(
				plantPos.x + plant->_sprite->getContentSize().width / 2,
				plantPos.y + plant->_sprite->getContentSize().height / 2);

			Point posInNode = bullet->convertToNodeSpaceAR(plantPosInCenter);
			
			Rect plantRect = Rect(
				posInNode.x - plant->_sprite->getContentSize().width / 2 ,
				posInNode.y - plant->_sprite->getContentSize().height / 2,
				plant->_sprite->getContentSize().width,
				plant->_sprite->getContentSize().height
				);
			
			if(bulletRect.intersectsRect(plantRect)){
				if(plant->getLife() > 0)
				{
					plant->sliderShow();
					plant->getHurt(this->_attackValue);
					sprintf(str,"eff%d.png",this->_towerNo);
					plant->playAnimate(str);
				}
				else if(plant->getLife() == 0)
				{
					//更新主界面金币标签
					GameData::getInstance()->_currentMoney += plant->_money;
					sprintf(str,"%d",GameData::getInstance()->_currentMoney);
					((MainScene*) ( this->getParent()->getParent() ) )->_moneyLabel->setString(str);
					//die
					plant->die();
				}	
			}
		}

	}
}

//===================== Tower15 =============================

Tower* Tower15::createTower(int towerNo,int money,int level){

	Tower* tower = Tower::create();
	//类型 金币 攻击值 攻击距离 塔的等级
	tower->initTower(towerNo,money,3,130,level,CIRCLE_AOE);
	tower->_isCreateBullet = false;
	tower->_logicTime = 1.4 / GameData::getInstance()->_currentSpeed;
	tower->_schedule = schedule_selector(Tower15::towerLogic);
	tower->schedule(tower->_schedule,tower->_logicTime);
	return tower;

}

void Tower15::towerLogic(float dt){
	Node* target = NULL;
	bool plantFlag = false;

	Enemy* enemy = this->getPriorityEnemy();
	Plant* plant = this->getPriorityPlant();

	if(enemy != NULL ){
		target = enemy;
	}else if(plant != NULL){
		target = plant;
		//因为植物的sprite锚点设置为0，
		//所以当为植物的时候需要稍微改动一下射击方向为sprite中心(0.5,0.5)
		//所以先标记一下，下面处理
		plantFlag = true;
	}else{
		target = (Node*) this->getCloseTarget();
	}

	//发射子弹
	if(target != NULL){

		char str[15] = {0};
		sprintf(str,"zd%d_%d.png",this->_towerNo,this->_towerLevel);

		//创建子弹
		if(this->_isCreateBullet == false){

			Bullet* bullet = Bullet::create(str,this->_attackValue,this->_attackDistance,this->_towerType,this->_towerNo);
			bullet->setTag(CIRCLE_AOE_TAG);
			this->addChild(bullet);
			bullet->playAnimate(str,1);
			this->_isCreateBullet = true;

		}else{
			((Bullet*)this->getChildByTag(CIRCLE_AOE_TAG))->playAnimate(str,1);
		}

		//因为是AOE伤害，所以遍历plant 和 enemy
		//plant
		for(Plant* p : GameData::getInstance()->_plantsVector)
		{
			Point plantPos = Point(
				p->getPositionX() + p->_sprite->getContentSize().width / 2,
				p->getPositionY() + p->_sprite->getContentSize().height / 2);
			Point towerPos = this->getPosition();
			int dis = ccpDistance(plantPos,towerPos);
			if(dis < this->_attackDistance)
			{
				if(p->getLife() > 0)
				{
					p->sliderShow();
					p->getHurt(this->_attackValue);
					sprintf(str,"eff%d.png",this->_towerNo);
					p->playAnimate(str);
				}
				else if(p->getLife() == 0)
				{
					//更新主界面金币标签
					GameData::getInstance()->_currentMoney += p->_money;
					sprintf(str,"%d",GameData::getInstance()->_currentMoney);
					((MainScene*) ( this->getParent()->getParent() ) )->_moneyLabel->setString(str);
					//die
					p->die();
				}	
			}

		}//end plant

		//enemy
		for(Enemy* e : GameData::getInstance()->_enemysVector)
		{
			Point enemyPos = e->getPosition();
			Point towerPos = this->getPosition();
			int dis = ccpDistance(enemyPos,towerPos);
			if(dis < this->_attackDistance)
			{
				if(e->getLife() > 0)
				{
					e->sliderShow();
					e->getHurt(this->_attackValue);
					//减速
					e->slowDown();

					sprintf(str,"eff%d.png",this->_towerNo);
					e->playAnimate(str);
				}
				else if(e->getLife() == 0)
				{
					//更新主界面金币标签
					GameData::getInstance()->_currentMoney += e->_money;
					sprintf(str,"%d",GameData::getInstance()->_currentMoney);
					((MainScene*) ( this->getParent()->getParent() ) )->_moneyLabel->setString(str);
					//die
					e->die();
				}
			}
		}//end enemy

	}
}
