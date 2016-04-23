#include "Enemy.h"
#include "GameData.h"
#include "AnimationUtil.h"
#include "EnemyLayer.h"
#include "GameAudio.h"

bool Enemy::init()
{
	if(!Node::init())
	{
		return false;
	}
	_currentWayPoint = 0;
	_isPriorityAttact = false;
	_prioritySprite = NULL;
	_isAnimatePlaying = false;
	_isSlowDown = false;
	_isSlowDownAnimatePlaying = false;
	_speed_X = GameData::getInstance()->_currentSpeed;
	
	return true;
}

void Enemy::createSlider()
{
	_hpSlider = ControlSlider::create("EnemyHPBg.png","EnemyHP.png","EnemyHpthumb.png");
	_hpSlider->setPosition(
		_sprite->getPositionX(),
		_sprite->getPositionY() + _sprite->getContentSize().height / 2 + 10);
	_hpSlider->setTouchEnabled(false);
	_hpSlider->setMinimumValue(0);
	_hpSlider->setMaximumValue(_hp);
	_hpSlider->setValue(_hp );
	_hpSlider->setVisible(false);
	_isHpSliderShow = false;
	addChild(_hpSlider);
}

void Enemy::sliderShow()
{
	if(_hpSlider && !_isHpSliderShow )
	{
		_hpSlider->setVisible(true);
		_isHpSliderShow = true;
	}
}

void Enemy::createPriorityPoint()
{
	//图片
	_prioritySprite = Sprite::createWithSpriteFrameName("point01.png");
	_prioritySprite->setPosition(0,_sprite->getContentSize().height / 2 + 25);
	this->addChild(_prioritySprite);

	//动画
	auto animate = AnimationUtil::getInstance()->getAnimate("point0");
	auto repete = RepeatForever::create(animate);
	_prioritySprite->runAction(repete);

	_isPriorityAttact = true;
}

bool Enemy::isPriorityAttact()
{
	return _isPriorityAttact;
}

void Enemy::getHurt(float hp){
	_hp = _hp - hp;
	if(_hp <= 0)
	{
		_hp = 0;

	}
	if(_hpSlider)
		_hpSlider->setValue(_hp);
}

void Enemy::slowDown()
{
	if(_isSlowDown == false)
	{
		Sequence* sequence1 =  (Sequence*)this->getActionByTag(ENEMY_MOVE_ACTION_TAG1);
		Sequence* sequence2 =  (Sequence*)this->getActionByTag(ENEMY_MOVE_ACTION_TAG2);
		if(sequence1 != NULL)
		{
			this->stopActionByTag(ENEMY_MOVE_ACTION_TAG1);
			this->_currentWayPoint--;
			this->_speed /= 2;
			_isSlowDown = true;
			((EnemyLayer*)this->getParent())->enemyMove(this);

		}
		else if(sequence2 != NULL)
		{
			this->stopActionByTag(ENEMY_MOVE_ACTION_TAG2);
			this->_speed /= 2;
			this->_currentWayPoint--;
			_isSlowDown = true;
			((EnemyLayer*)this->getParent())->followPath(this);
		}
	}
}

float Enemy::getLife(){
	return _hp;
}

void Enemy::die()
{
	_hp = -1;
	if(_hpSlider)
		_hpSlider->setValue(0);
	if(this->isPriorityAttact())
	{
		this->removeChild(this->_prioritySprite);
		this->_prioritySprite = NULL;
		this->_isPriorityAttact = false;
	}

	//移除后_hpSlider不会立马为空，只会在下一帧为空
	//在这里手动置空可以解决bug
	//enemy走到终点（enemy执行die移除hpSlider）且受子弹攻击（getHurt中hpSlider不为空的异常）
	this->removeChild(_hpSlider);
	_hpSlider = NULL;

	this->stopActionByTag(101);//在enemyLayer中定义 move Action
	this->_sprite->stopAllActions();
	auto die = AnimationUtil::getInstance()->getAnimate("enemydie");
	auto dieDone = CallFunc::create(CC_CALLBACK_0(Enemy::removeEnemy,this,this,_sprite));
	_sprite->runAction(Sequence::createWithTwoActions(die,dieDone));

	//播放死亡effect
	char str[15] = {0};
	sprintf(str,"enemy%d.mp3",this->_enemyNo);
	GameAuio::getInstance()->palyEffect(str);
}

void Enemy::removeEnemy(Node* pEnemy,Node* pSprite)
{
	Enemy* enemy = (Enemy*)pEnemy;
	Sprite* sprite = (Sprite*)pSprite;
	if(enemy != NULL )
	{
		sprite->stopAllActions();
		this->removeChild(sprite);
		this->removeAllChildrenWithCleanup(true);
		GameData::getInstance()->_enemysVector.eraseObject(this);
		this->getParent()->removeChild(this,true);
	}
}

WayPoint* Enemy::getCurrentWaypoint()
{
	return GameData::getInstance()->_pointsVector.at(this->_currentWayPoint);
}

WayPoint* Enemy::getNextWaypoint()
{
	this->_currentWayPoint++;
	return GameData::getInstance()->_pointsVector.at(this->_currentWayPoint);
}

void Enemy::playAnimate(const char* name)
{
	if(_isAnimatePlaying)
	{
		return;
	}
	//减速的时候我们多添加一个animate，使得减速动画一直存在
	if(_isSlowDown && !_isSlowDownAnimatePlaying)
	{
		_animate = AnimationUtil::getInstance()->getSpriteBySplitIMG(name,1,6);
		this->addChild(_animate,10);
		auto animate = AnimationUtil::getInstance()->getAnimate(name);
		_animate->runAction(animate);
		_isAnimatePlaying = true;
		_isSlowDownAnimatePlaying = true;
	}
	_animate = AnimationUtil::getInstance()->getSpriteBySplitIMG(name,1,6);
	this->addChild(_animate,10);
	
	auto animate = AnimationUtil::getInstance()->getAnimate(name);
	auto animateDone = CallFunc::create(CC_CALLBACK_0(Enemy::playAnimateFinish,this));

	_isAnimatePlaying = true;

	_animate->runAction(Sequence::create(animate,animateDone,NULL));
}

void Enemy::playAnimateFinish()
{
	if(_isAnimatePlaying && _animate)
	{
		this->removeChild(_animate,true);
		_animate = NULL;
		_isAnimatePlaying = false;
	}
}

Enemy* Enemy1::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 1;
	enemy->_hp = HP_LOW;
	enemy->_speed = SPEED_NOR * enemy->_speed_X ;
	enemy->_money = 25;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy1.png");
	enemy->addChild(enemy->_sprite);
	
	return enemy;
}

Enemy* Enemy2::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 2;
	enemy->_hp = HP_NOR ;
	enemy->_speed = SPEED_LOW * enemy->_speed_X;
	enemy->_money = 35;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy2.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}

Enemy* Enemy3::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 3;
	enemy->_hp = HP_LOW;
	enemy->_speed = SPEED_NOR * enemy->_speed_X;
	enemy->_money = 40;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy3.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}

Enemy* Enemy4::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 4;
	enemy->_hp = HP_NOR;
	enemy->_speed = SPEED_NOR * enemy->_speed_X;
	enemy->_money = 40;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy4.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}


Enemy* Enemy5::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 5;
	enemy->_hp = HP_NOR;
	enemy->_speed = SPEED_NOR * enemy->_speed_X;
	enemy->_money = 50;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy5.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}


Enemy* Enemy6::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 6;
	enemy->_hp = HP_BOSS1;
	enemy->_speed = SPEED_LOW * enemy->_speed_X;
	enemy->_money = 200;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy6.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}


Enemy* Enemy7::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 7;
	enemy->_hp = HP_BOSS2;
	enemy->_speed = SPEED_LOW * enemy->_speed_X;
	enemy->_money = 250;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy7.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}


Enemy* Enemy8::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 8;
	enemy->_hp = HP_NOR;
	enemy->_speed = SPEED_FAST * enemy->_speed_X;
	enemy->_money = 50;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy8.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}


Enemy* Enemy9::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 9;
	enemy->_hp = HP_HIGH;
	enemy->_speed = SPEED_NOR * enemy->_speed_X;
	enemy->_money = 50;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy9.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}


Enemy* Enemy10::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 10;
	enemy->_hp = HP_LOW;
	enemy->_speed = SPEED_FAST * enemy->_speed_X;
	enemy->_money = 50;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy10.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}

Enemy* Enemy11::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 11;
	enemy->_hp = HP_BOSS3;
	enemy->_speed = SPEED_LOW * enemy->_speed_X;
	enemy->_money = 300;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy11.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}

Enemy* Enemy12::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 12;
	enemy->_hp = HP_HIGH;
	enemy->_speed = SPEED_FAST * enemy->_speed_X;
	enemy->_money = 50;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy12.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}

Enemy* Enemy13::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 13;
	enemy->_hp = HP_BOSS4;
	enemy->_speed = SPEED_LOW * enemy->_speed_X;
	enemy->_money = 350;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy13.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}

Enemy* Enemy14::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 14;
	enemy->_hp = HP_NOR;
	enemy->_speed = SPEED_FAST * enemy->_speed_X;
	enemy->_money = 30;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy14.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}

Enemy* Enemy15::createEnemy()
{
	auto enemy = Enemy::create();
	enemy->_enemyNo = 15;
	enemy->_hp = HP_HIGH;
	enemy->_speed = SPEED_NOR * enemy->_speed_X;
	enemy->_money = 50;
	enemy->_sprite = Sprite::createWithSpriteFrameName("Enemy15.png");
	enemy->addChild(enemy->_sprite);
	return enemy;
}


