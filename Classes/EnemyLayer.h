#pragma once

/**
 * @file         EnemyLayer.h    
 * @date         2014-6-9
 * @author       shun_fzll
 * @brief   	 enemy's add and delete
 * 
 */

#include "cocos2d.h"
using namespace cocos2d;

const int ENEMY_ACTION_TAG = 101;

enum GameOverButtonTag{
	BTN_CHOOSE_LEVEL,	//�ؿ�ѡ��
	BTN_CUR_LEVEL,		//������ս
	BTN_NEXT_LEVEL		//��һ��
};

class EnemyLayer : public Layer{
public:
	EnemyLayer();
	~EnemyLayer();
	virtual bool init();
	CREATE_FUNC(EnemyLayer);
	//�жϲ��Ƿ������������һ������������Ӳ��е�һ��enemy
	void addWave(int currentWave);
	void addEnemy(int enemyType);
	void enemyBirth(int type);
	void enemyMove(Node* node);

	void removeEnemy(Node* pEnemy,Node* pSprite);
	void followPath(Node* node);
	/*
		1.ѡȡһ�����ʵ�ʱ�̿�����һ������������ʱ������ִ��createEnemys��
		2.��ôʲôʱ�����Ƚ�ǡ���أ�
		3.��Ҫ��֤��һ�����˳�����ϣ���Ҫ��֤enemyȫ�������ſ�����һ��
		4.������������һ�����һ�����˴�����ϵ�ʱ��ȡ����ʱ����Ȼ����update
		  �в��ϵ�ȥ�ж�enemy�Ƿ�ȫ����������ǣ�������һ��
	*/
	void update(float dt);
	//��ʱ����ԴԴ���ϵĴ���enemy
	void createEnemys(float dt);

	//��Ϸ��������layer
	void popupGameOverLayer(float dt);
	//��ť�ص�
	void popupGameOverCallback(Node* pNode);

public:
	
	int _enemyTotalNum ;
	int _currentEnemyNum ;//begin with 0

	SEL_SCHEDULE _schedule;
	bool _scheDuleFlag ;

	std::string _enemyStr;	//eg:EnemyList1.png

	int _dieWave;	//�����˵Ĳ���
};