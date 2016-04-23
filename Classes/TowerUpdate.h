#pragma once

/**
 * @file         TowerUpdate.h    
 * @date         2014-6-22
 * @author       shun_fzll
 * @brief   	 塔升级图片
 * 
 */

#include "cocos2d.h"
#include "Tower.h"

using namespace cocos2d;

class TowerUpdate : public Node{
public:
	virtual bool init();
	CREATE_FUNC(TowerUpdate);
	void initTowerUpdate(Tower* pTower);
	//用于更新是否可以点击
	void TowerUpdateLoagic(float dt);
	//是否可更更新
	bool isCanUpdate();
public:
	Sprite* _updateBG;

	//update
	Sprite* _update_nor;
	Sprite* _update_dis;
	Sprite* _dingji;
	Sprite* _updateMoneyBG;
	LabelTTF* _updateLabel;
	int _updateMoney;
	bool _isCanUpdate;	//是否可以升级

	//remove
	Sprite* _remove;
	Sprite* _removeMoneyBG;
	LabelTTF* _removeLabel;
	int _soldMoney;

	int _level;			//塔等级

};