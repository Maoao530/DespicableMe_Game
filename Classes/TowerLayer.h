#pragma once

/**
 * @file         TowerLayer.h    
 * @date         2014-6-13
 * @author       shun_fzll
 * @brief   	 
 * 
 */

#include "cocos2d.h"
#include "Tower.h"

using namespace cocos2d;

const int BUILD_TOWER_SELECT_TAG = 101;
const int BUILD_TOWER_UPDATE_TAG = 151;

enum TouchType
{
	MENU  = -2,	//导航菜单
	ROAD  = -1,	//路
	NONE  = 0,	//空地
	TOWER = 1,	//塔，升级或移除
	ENEMY = 2,	//敌人，优先攻击
	PLANT = 3	//植物，优先攻击
};
class TowerLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(TowerLayer);
	
	//touch 
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);

	//判断返回的触摸类型
	TouchType getTouchType(Point point);
	//创建塔选择图片
	void buildTowerSelect(Point point);
	//在update中处理子弹碰撞
	void update(float dt);

	//设置要升级的塔
	void setUpdateTower(Tower* pTower);
	//创建塔升级图片
	void buildTowerUpdate();

private:
	//判断是否正在创建塔
	bool isBuildingTower;

	//判断是否正在升级塔
	bool _isUpdatingTower;
	Tower* _towerUpdate;
};