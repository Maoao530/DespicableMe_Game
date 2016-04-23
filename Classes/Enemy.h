#pragma once

/**
 * @file         Enemy.h    
 * @date         2014-6-9
 * @author       shun_fzll
 * @brief   	 怪物
 *				
 */

#include "cocos2d.h"
#include "WayPoint.h"
#include "extensions/cocos-ext.h"  

using namespace cocos2d::extension;
using namespace cocos2d;

const int ENEMY_MOVE_ACTION_TAG1 = 103;
const int ENEMY_MOVE_ACTION_TAG2 = 104;

class Enemy : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(Enemy);
	//血条
	void createSlider();	
	void sliderShow();	
	//优先攻击动画
	void createPriorityPoint();
	bool isPriorityAttact();
	//在TowerLayer受子弹攻击时调用
	void getHurt(float hp);	
	//减速
	void slowDown();
	//在TowerLayer中hp降为0时调用
	void die();	
	//get life
	float getLife();
	//移除enemyy
	void removeEnemy(Node* pEnemy,Node* pSprite);
	//路径
	WayPoint* getNextWaypoint();
	WayPoint* getCurrentWaypoint();
	//攻击效果
	void playAnimate(const char* name);
	void playAnimateFinish();
public:
	Sprite* _sprite;			//敌人sprite
	Sprite* _prioritySprite;	//优先攻击sprite
	bool _isPriorityAttact;
	int _money;
	float _hp;
	int _speed;
	int _speed_X;				//速度 x1 或者 x2
	int _currentWayPoint;
	ControlSlider* _hpSlider;	//血条
	
	bool _isHpSliderShow;
	bool _isAnimatePlaying;		//普通攻击动画是否被添加

	Sprite* _animate;

	bool _isSlowDown;			//是否被减速
	bool _isSlowDownAnimatePlaying;	//减速动画是否被添加

	int _enemyNo;
};

//在这里简单配置一下怪物属性

//怪物速度属性
const float SPEED_LOW = 60.0; 
const float SPEED_NOR = 96.0 ;
const float SPEED_FAST = 150.0 ;
//hp属性
const float HP_LOW = 60.0; 
const float HP_NOR = 100.0 ;
const float HP_HIGH = 200.0 ;

//boss 6 7 11 13
const float HP_BOSS1 = 800.0 ;
const float HP_BOSS2 = 1500.0 ;
const float HP_BOSS3 = 2000.0 ;
const float HP_BOSS4 = 3000.0 ;

//低hp 正常speed
class Enemy1 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//正常hp 低speed
class Enemy2 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//低hp 正常speed
class Enemy3 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//正常hp 正常speed
class Enemy4 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//正常hp 正常speed
class Enemy5 : public Enemy
{
public:
	static Enemy* createEnemy();
};

//boss1 低speed
class Enemy6 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//boss2 低speed
class Enemy7 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//正常hp 高speed
class Enemy8 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//高hp 正常speed
class Enemy9 : public Enemy
{
public:
	static Enemy* createEnemy();
};

//低hp 高speed
class Enemy10 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//boss3  正常speed
class Enemy11 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//高hp 高speed
class Enemy12 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//boss4  正常speed
class Enemy13 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//正常hp 高speed
class Enemy14 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//高hp 正常speed
class Enemy15 : public Enemy
{
public:
	static Enemy* createEnemy();
};


