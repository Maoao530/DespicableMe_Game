#include "Bullet.h"
#include "AnimationUtil.h"

bool Bullet::init()
{
	if(!Node::init())
	{
		return false;
	}
	return true;
}

Bullet* Bullet::create(const char* name,float attackValue,int distance,int type,int towerNo)
{
	Bullet* bullet = Bullet::create();
	int numOfpng = 5;
	if(type ==  CIRCLE_AOE)
	{
		numOfpng ++ ;
	}
	bullet->_sprite = AnimationUtil::getInstance()->getSpriteBySplitIMG(name,1,numOfpng);
	if(bullet->_sprite == NULL)
	{
		return NULL;
	}
	strcpy(bullet->tempName,name);
	if(type == LINE_SINGLE)
	{
		auto size = bullet->_sprite->getContentSize();
		//sprite1
		bullet->_sprite->setTextureRect(Rect(0,40,size.width,size.height - 40));
		bullet->_sprite->setAnchorPoint(Point(0.5,0));
		bullet->_sprite->setPosition(Point::ZERO);

		bullet->schedule(schedule_selector(Bullet::updateSpriteState),0.25f);

	}
	else if(type == LINE_AOE)
	{
		auto size = bullet->_sprite->getContentSize();
		//sprite1
		bullet->_sprite->setAnchorPoint(Point(0.5,0));
		bullet->_sprite->setPosition(Point::ZERO);

	}
	bullet->addChild(bullet->_sprite);
	bullet->_playingAnimate = false;
	bullet->_sprite->setVisible(bullet->_playingAnimate);
	

	bullet->_attackValue = attackValue;
	bullet->_distance = distance;
	bullet->_type = type;
	bullet->_towerNo = towerNo;

	return bullet;
}

void Bullet::playAnimate(const char* name,int times)
{
	_playingAnimate = true;
	_sprite->setVisible(_playingAnimate);

	Animate* animate = AnimationUtil::getInstance()->getAnimate(name);
	auto repeat = Repeat::create(animate,times);

	CallFunc* repeatDone = CallFunc::create(CC_CALLBACK_0(Bullet::playAniamteFinish,this));

	this->_sprite->runAction(Sequence::create(repeat,repeatDone,NULL));
}

void Bullet::playAniamteFinish()
{
	_playingAnimate = false;
	_sprite->setVisible(_playingAnimate);
}


void Bullet::updateSpriteState(float dt)
{
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.05);
	Rect rect = _spriteRect;
	
	for(int i = 0; i < 5; i++)
	{
		auto frame = SpriteFrame::create(tempName,Rect(i*70,0,rect.size.width,rect.size.height));
		animation->addSpriteFrame(frame);
	}
	_sprite->setVisible(true);
	_sprite->stopAllActions();
	_sprite->runAction(Repeat::create(Animate::create(animation),5));
}


