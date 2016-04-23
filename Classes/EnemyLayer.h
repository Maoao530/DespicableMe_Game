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
	BTN_CHOOSE_LEVEL,	//关卡选择
	BTN_CUR_LEVEL,		//重新挑战
	BTN_NEXT_LEVEL		//下一关
};

class EnemyLayer : public Layer{
public:
	EnemyLayer();
	~EnemyLayer();
	virtual bool init();
	CREATE_FUNC(EnemyLayer);
	//判断波是否结束，是则下一波，不是则添加波中的一个enemy
	void addWave(int currentWave);
	void addEnemy(int enemyType);
	void enemyBirth(int type);
	void enemyMove(Node* node);

	void removeEnemy(Node* pEnemy,Node* pSprite);
	void followPath(Node* node);
	/*
		1.选取一个合适的时刻开启下一波（即开启定时器不断执行createEnemys）
		2.那么什么时候开启比较恰当呢？
		3.既要保证这一波敌人出现完毕，又要保证enemy全部死亡才开启下一波
		4.所以我们在这一波最后一个敌人创建完毕的时候取消定时器，然后在update
		  中不断的去判断enemy是否全部消灭，如果是，则开启下一波
	*/
	void update(float dt);
	//定时器，源源不断的创建enemy
	void createEnemys(float dt);

	//游戏结束弹出layer
	void popupGameOverLayer(float dt);
	//按钮回调
	void popupGameOverCallback(Node* pNode);

public:
	
	int _enemyTotalNum ;
	int _currentEnemyNum ;//begin with 0

	SEL_SCHEDULE _schedule;
	bool _scheDuleFlag ;

	std::string _enemyStr;	//eg:EnemyList1.png

	int _dieWave;	//所击退的波数
};