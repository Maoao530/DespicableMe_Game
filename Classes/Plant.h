#pragma once

/**
 * @file         Plant.h    
 * @date         2014-6-12
 * @author       shun_fzll
 * @brief   	 植物，障碍物
 * 
 */

#include "cocos2d.h"
#include "PlantPoint.h"
#include "extensions/cocos-ext.h"  

using namespace cocos2d::extension;
using namespace cocos2d;

class Plant : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(Plant);
	//优先攻击动画
	void createPriorityPoint();
	bool isPriorityAttact();
	//血条
	void createSlider();
	void sliderShow();
	void getHurt(float hp);
	void die();
	float getLife();
	void removePlant(Node* pEnemy,Node* pSprite);

	//攻击效果
	void playAnimate(const char* name);
	void playAnimateFinish();

public:
	Sprite* _sprite;
	float _hp;
	int _money;
	ControlSlider* _hpSlider;

	Sprite* _prioritySprite;	//优先攻击的标志sprite
	bool _isPriorityAttact;

	bool _isAnimatePlaying;		
	Sprite* _animate;		//攻击效果
};

class Honglan : public Plant
{
public:
	static Plant* createPlant();
};

class Quan : public Plant
{
public:
	static Plant* createPlant();
};

class Hua : public Plant
{
public:
	static Plant* createPlant();
};

class Lanjuan : public Plant
{
public:
	static Plant* createPlant();
};

class Honglv : public Plant
{
public:
	static Plant* createPlant();
};

class Lvjuan : public Plant
{
public:
	static Plant* createPlant();
};

class Damo : public Plant{
public:
	static Plant* createPlant();
};

class Fang : public Plant
{
public:
	static Plant* createPlant();
};

class Huangci : public Plant
{
public:
	static Plant* createPlant();
};

class Huanggan : public Plant
{
public:
	static Plant* createPlant();
};

class Huigan : public Plant
{
public:
	static Plant* createPlant();
};

class Xiaocao : public Plant
{
public:
	static Plant* createPlant();
};

class Xiaomo : public Plant
{
public:
	static Plant* createPlant();
};

class Zhuang : public Plant
{
public:
	static Plant* createPlant();
};

//jam2

class Yuanxrz : public Plant
{
public:
	static Plant* createPlant();
};

class Gu : public Plant
{
public:
	static Plant* createPlant();
};

class Box : public Plant
{
public:
	static Plant* createPlant();
};

class Shenshu : public Plant
{
public:
	static Plant* createPlant();
};

class Qianshu : public Plant
{
public:
	static Plant* createPlant();
};

class Z : public Plant
{
public:
	static Plant* createPlant();
};


class H : public Plant
{
public:
	static Plant* createPlant();
};

class Huaxrz : public Plant
{
public:
	static Plant* createPlant();
};

class Xiaoxrz : public Plant
{
public:
	static Plant* createPlant();
};

class Shenshugan : public Plant
{
public:
	static Plant* createPlant();
};

class Jiancao : public Plant
{
public:
	static Plant* createPlant();
};

class Qianshugan : public Plant
{
public:
	static Plant* createPlant();
};






