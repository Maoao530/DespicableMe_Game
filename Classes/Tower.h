#pragma once

/**
 * @file         Tower.h    
 * @date         2014-6-17
 * @author       shun_fzll
 * @brief   	 
 * 
 */


#include "cocos2d.h"
#include "Enemy.h"
#include "Plant.h"
#include "Bullet.h"

using namespace cocos2d;

const int CIRCLE_AOE_TAG = 55;
const int LINE_SINGLE_TAG = 56;
const int LINE_AOE_TAG = 57;

class Tower : public Node{
public:
	virtual bool init();
	CREATE_FUNC(Tower);
	Enemy* getPriorityEnemy();	//获取优先攻击敌人对象
	Plant* getPriorityPlant();	//获取优先攻击敌人对象
	Vector<Enemy*> getAllCanBeAttackEnemy();		//获取所有在攻击范围内的敌人
	Vector<Plant*> getAllCanBeAttackPlant();		//获取所有在攻击返回内的植物
	Enemy* getCloseTarget();	//获取最近的目标
	void initTower(int towerNo,int money,float attackValue,int distance,int level,int type);
	void changeTowerLogicTime(float time);
	
public:
	int _money;				//建造金币
	float _attackValue;		//伤害值
	int _attackDistance;	//伤害距离
	int _towerLevel;		//塔等级 最小为1 最大为3
	int _towerNo;			//塔编号
	int _towerType;			//塔类型,与子弹类型一一对应
	Sprite* _dizuo;			//底座
	Sprite* _sprite;		//塔
//	Sprite* _bullet;		//子弹

	bool _isCreateBullet;	//是否创建子弹，对于有且只有一枚子弹的塔（塔2，塔4）

	Vector<Enemy*> _enemysCanBeAttack;
	Vector<Plant*> _plantsCanBeAttack;

	SEL_SCHEDULE _schedule;   //塔的logic定时器
	float _logicTime;			  //logic的时间间隔interval

}; 

class TowerFactory{
public:
	static Tower* createTower(int towerNo,int money,int level);

};

//风扇，发射子弹，穿透
class Tower1 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootFinish(Node* pNode);
};

//太阳花，子弹为圈圈，范围伤害
class Tower2 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);

};
//皇冠，旋转后发射3枚子弹子弹，不穿透
class Tower3 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pNode,Point pos);
	void shootFinish(Node* pNode);
};
//飞船，连线，单体伤害
class Tower4 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
};
//火箭塔，旋转后发射子弹，可穿透
class Tower5 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pTarget,Point pos);
	void shootFinish(Node* pNode);
};

//灯塔，360度发射8枚子弹，不穿透
class Tower6 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootFinish(Node* pNode);
};
//毒素，旋转后发射子弹，不可穿透
class Tower7 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pNode,Point pos);
	void shootFinish(Node* pNode);
};
//树叶，发射子弹，可穿透
class Tower8 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootFinish(Node* pNode);
};
//帽子，旋转发射子弹，可穿透
class Tower9 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pTarget,Point pos);
	void shootFinish(Node* pNode);
};
//奶瓶，旋转后连线，单体伤害
class Tower10 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	
};

//樱桃，旋转后发射子弹，子弹速度较快，aoe伤害
class Tower11 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pNode,Point pos);
	void shootFinish(Node* pNode);
};
//棒棒糖，旋转后发射子弹，aoe伤害
class Tower12 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pNode,Point pos);
	void shootFinish(Node* pNode);
};
//奶嘴，旋转后发射子弹，轻巧速度略快，aoe伤害
class Tower13 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pNode,Point pos);
	void shootFinish(Node* pNode);
};
//闪电塔，往一个方向连线，aoe伤害
class Tower14 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
};

class Tower15 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
};