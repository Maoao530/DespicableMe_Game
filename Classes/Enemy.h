#pragma once

/**
 * @file         Enemy.h    
 * @date         2014-6-9
 * @author       shun_fzll
 * @brief   	 ����
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
	//Ѫ��
	void createSlider();	
	void sliderShow();	
	//���ȹ�������
	void createPriorityPoint();
	bool isPriorityAttact();
	//��TowerLayer���ӵ�����ʱ����
	void getHurt(float hp);	
	//����
	void slowDown();
	//��TowerLayer��hp��Ϊ0ʱ����
	void die();	
	//get life
	float getLife();
	//�Ƴ�enemyy
	void removeEnemy(Node* pEnemy,Node* pSprite);
	//·��
	WayPoint* getNextWaypoint();
	WayPoint* getCurrentWaypoint();
	//����Ч��
	void playAnimate(const char* name);
	void playAnimateFinish();
public:
	Sprite* _sprite;			//����sprite
	Sprite* _prioritySprite;	//���ȹ���sprite
	bool _isPriorityAttact;
	int _money;
	float _hp;
	int _speed;
	int _speed_X;				//�ٶ� x1 ���� x2
	int _currentWayPoint;
	ControlSlider* _hpSlider;	//Ѫ��
	
	bool _isHpSliderShow;
	bool _isAnimatePlaying;		//��ͨ���������Ƿ����

	Sprite* _animate;

	bool _isSlowDown;			//�Ƿ񱻼���
	bool _isSlowDownAnimatePlaying;	//���ٶ����Ƿ����

	int _enemyNo;
};

//�����������һ�¹�������

//�����ٶ�����
const float SPEED_LOW = 60.0; 
const float SPEED_NOR = 96.0 ;
const float SPEED_FAST = 150.0 ;
//hp����
const float HP_LOW = 60.0; 
const float HP_NOR = 100.0 ;
const float HP_HIGH = 200.0 ;

//boss 6 7 11 13
const float HP_BOSS1 = 800.0 ;
const float HP_BOSS2 = 1500.0 ;
const float HP_BOSS3 = 2000.0 ;
const float HP_BOSS4 = 3000.0 ;

//��hp ����speed
class Enemy1 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//����hp ��speed
class Enemy2 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//��hp ����speed
class Enemy3 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//����hp ����speed
class Enemy4 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//����hp ����speed
class Enemy5 : public Enemy
{
public:
	static Enemy* createEnemy();
};

//boss1 ��speed
class Enemy6 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//boss2 ��speed
class Enemy7 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//����hp ��speed
class Enemy8 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//��hp ����speed
class Enemy9 : public Enemy
{
public:
	static Enemy* createEnemy();
};

//��hp ��speed
class Enemy10 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//boss3  ����speed
class Enemy11 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//��hp ��speed
class Enemy12 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//boss4  ����speed
class Enemy13 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//����hp ��speed
class Enemy14 : public Enemy
{
public:
	static Enemy* createEnemy();
};
//��hp ����speed
class Enemy15 : public Enemy
{
public:
	static Enemy* createEnemy();
};


