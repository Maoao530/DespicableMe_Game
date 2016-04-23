/*
#include "Creep.h"
#include "DataModel.h"

bool Creep::init(){
	if(!Sprite::init()){
		return false;
	}
	return true;
}

WayPoint* Creep::getCurrentWaypoint(){
	return DataModel::getInstance()->wayPoints.at(this->curWaypoint);
}

WayPoint* Creep::getNextWaypoint(){
	int lastWayPoint = DataModel::getInstance()->wayPoints.size();
	this->curWaypoint++;
	if(this->curWaypoint >= lastWayPoint){
		//取最后一个点
		this->curWaypoint = lastWayPoint - 1;
	}
	return DataModel::getInstance()->wayPoints.at(this->curWaypoint);
}



Creep* FastRedCreep::creep(){

	auto creep = Creep::create();
	
	creep->sprite = Sprite::create("Enemy1.png");
	creep->addChild(creep->sprite,0);
	
	creep->curHp = 5;
	creep->moveDuration = 4;
	creep->curWaypoint = 0;

	return creep;
}

Creep* StrongGreenCheep::creep(){
	
	auto creep = Creep::create();

	creep->sprite = Sprite::create("Enemy2.png");
	creep->addChild(creep->sprite,0);

	creep->curHp = 10;
	creep->moveDuration = 8;
	creep->curWaypoint = 0;

	return creep;
}

void Creep::creepLogic(float dt){
	
	//矢量
	Point wayPointVector = this->getCurrentWaypoint()->getPosition() - this->getPosition();
	//矢量 - > 弧度
	float wayPointAngle = ccpToAngle(wayPointVector);
	//弧度 -> 角度
	float cocosAngle = CC_RADIANS_TO_DEGREES(wayPointAngle * -1);

	float rotateSpeed = 0.5 / M_PI;
	float rotateDuration = fabs(wayPointAngle * rotateSpeed);
	
	//旋转
	this->runAction(Sequence::create(RotateTo::create(rotateDuration,cocosAngle),NULL));

}
*/