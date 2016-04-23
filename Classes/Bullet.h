#pragma once

/**
 * @file         Bullet.h    
 * @date         2014-6-23
 * @author       shun_fzll
 * @brief   	 子弹
 * 
 */

#include "cocos2d.h"

using namespace cocos2d;

//按攻击效果把不同的塔的分类 
enum BulletType
{
	BULLET_AOE,			//类似子弹的aoe伤害(可穿透)
	BULLET_SINGLE,		//类似子弹的单体伤害（不可穿透）
	CIRCLE_AOE,			//圈圈行单体伤害
	LINE_SINGLE,			//点对点连线伤害
	LINE_AOE
};

class Bullet : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(Bullet);
	static Bullet* create(const char* name,float attackValue,int distance,int type,int towerNo);
	void playAnimate(const char* name,int times);
	void playAniamteFinish();
	//不断的更新sprite的状态，线性的子弹才有的
	void updateSpriteState(float dt);
public:
	Sprite* _sprite;

	float _attackValue;
	int _distance;	
	int _type;		//子弹类型
	int _towerNo;	//对应塔的类型

	bool _playingAnimate;//是否播放结束

	Rect _spriteRect;	//实时更新

	char tempName[20] ;
	
};



