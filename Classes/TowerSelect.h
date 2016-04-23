#pragma once

/**
 * @file         TowerSelect.h    
 * @date         2014-6-19
 * @author       shun_fzll
 * @brief   	 塔创建时候的图片，与Tower一一对应
 * 

 */

#include "cocos2d.h"

using namespace cocos2d;

class TowerSelect : public Node{
public:
	virtual bool init();
	CREATE_FUNC(TowerSelect);
	//塔的index和money
	void initTowerSelect(int index,int money);

	//用于更新是否可以点击
	void TowerSelectLoagic(float dt);

	bool isCanSelect();

public:
	int _money;
	Sprite* _sprite_nor; //正常可以显示可点击的图片
	Sprite* _sprite_dis; //不可点击的图片
	Sprite* _moneySprite;//moeny bg
	LabelTTF* _moneyLabel;
	//是否可以选择
	bool _isCanSelect;
	int _towerType;
};

class TowerSelectFactory{
public:
	static TowerSelect* createTowerSelct(int type);

};

