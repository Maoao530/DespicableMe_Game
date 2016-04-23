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
	Enemy* getPriorityEnemy();	//��ȡ���ȹ������˶���
	Plant* getPriorityPlant();	//��ȡ���ȹ������˶���
	Vector<Enemy*> getAllCanBeAttackEnemy();		//��ȡ�����ڹ�����Χ�ڵĵ���
	Vector<Plant*> getAllCanBeAttackPlant();		//��ȡ�����ڹ��������ڵ�ֲ��
	Enemy* getCloseTarget();	//��ȡ�����Ŀ��
	void initTower(int towerNo,int money,float attackValue,int distance,int level,int type);
	void changeTowerLogicTime(float time);
	
public:
	int _money;				//������
	float _attackValue;		//�˺�ֵ
	int _attackDistance;	//�˺�����
	int _towerLevel;		//���ȼ� ��СΪ1 ���Ϊ3
	int _towerNo;			//�����
	int _towerType;			//������,���ӵ�����һһ��Ӧ
	Sprite* _dizuo;			//����
	Sprite* _sprite;		//��
//	Sprite* _bullet;		//�ӵ�

	bool _isCreateBullet;	//�Ƿ񴴽��ӵ�����������ֻ��һö�ӵ���������2����4��

	Vector<Enemy*> _enemysCanBeAttack;
	Vector<Plant*> _plantsCanBeAttack;

	SEL_SCHEDULE _schedule;   //����logic��ʱ��
	float _logicTime;			  //logic��ʱ����interval

}; 

class TowerFactory{
public:
	static Tower* createTower(int towerNo,int money,int level);

};

//���ȣ������ӵ�����͸
class Tower1 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootFinish(Node* pNode);
};

//̫�������ӵ�ΪȦȦ����Χ�˺�
class Tower2 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);

};
//�ʹڣ���ת����3ö�ӵ��ӵ�������͸
class Tower3 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pNode,Point pos);
	void shootFinish(Node* pNode);
};
//�ɴ������ߣ������˺�
class Tower4 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
};
//���������ת�����ӵ����ɴ�͸
class Tower5 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pTarget,Point pos);
	void shootFinish(Node* pNode);
};

//������360�ȷ���8ö�ӵ�������͸
class Tower6 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootFinish(Node* pNode);
};
//���أ���ת�����ӵ������ɴ�͸
class Tower7 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pNode,Point pos);
	void shootFinish(Node* pNode);
};
//��Ҷ�������ӵ����ɴ�͸
class Tower8 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootFinish(Node* pNode);
};
//ñ�ӣ���ת�����ӵ����ɴ�͸
class Tower9 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pTarget,Point pos);
	void shootFinish(Node* pNode);
};
//��ƿ����ת�����ߣ������˺�
class Tower10 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	
};

//ӣ�ң���ת�����ӵ����ӵ��ٶȽϿ죬aoe�˺�
class Tower11 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pNode,Point pos);
	void shootFinish(Node* pNode);
};
//�����ǣ���ת�����ӵ���aoe�˺�
class Tower12 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pNode,Point pos);
	void shootFinish(Node* pNode);
};
//���죬��ת�����ӵ��������ٶ��Կ죬aoe�˺�
class Tower13 : public Tower{
public :
	static Tower* createTower(int towerNo,int money,int level);
	void towerLogic(float dt);
	void shootBullet(Node* pNode,Point pos);
	void shootFinish(Node* pNode);
};
//����������һ���������ߣ�aoe�˺�
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