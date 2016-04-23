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
		//ȡ���һ����
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
	
	//ʸ��
	Point wayPointVector = this->getCurrentWaypoint()->getPosition() - this->getPosition();
	//ʸ�� - > ����
	float wayPointAngle = ccpToAngle(wayPointVector);
	//���� -> �Ƕ�
	float cocosAngle = CC_RADIANS_TO_DEGREES(wayPointAngle * -1);

	float rotateSpeed = 0.5 / M_PI;
	float rotateDuration = fabs(wayPointAngle * rotateSpeed);
	
	//��ת
	this->runAction(Sequence::create(RotateTo::create(rotateDuration,cocosAngle),NULL));

}
*/