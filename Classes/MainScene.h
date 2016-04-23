#pragma once

/**
 * @file         MainScene.h    
 * @date         2014-5-24
 * @author       shun_fzll
 * @brief   	 game's main scene
 * 
 */

#include "cocos2d.h"

using namespace cocos2d;

//menutag
const int MENU_SPEED_TAG = 11;
const int MENU_PAUSE_TAG = 12;
const int MENU_MENU_TAG = 13;

//popup menu tag
const int POPMENU_RESUME_TAG = 21;
const int POPMENU_RESTART_TAG = 22;
const int POPMENU_SELECT_TAG = 23;

class MainScene : public Layer{
public :
	MainScene();
	~MainScene();

	virtual bool init(int flag);
	static MainScene* create(int flag);
	static Scene* createScene(int level);
	//初始化游戏参数
	void initGameParameters(int level);
	//菜单回调
	void menuCallback(Ref* pSender);
	//弹出菜单回调
	void popupMenuCallback(Node* pNode);
	//添加waypoint
	void addWayPoints();
	//添加plantPoint
	void addPlantPoint();
	//更改游戏速度
	void changeSpeedX(int speedX);
	//
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event); 
public:
	//tmx地图
	TMXTiledMap* _map;
	TMXLayer* _background;
	TMXLayer* _road;
	TMXObjectGroup* _object;
	//菜单背景图片
	Sprite* _menubg;
	//暂停标签图片
	Sprite* _pauseLabel;
	//money Label
	LabelTTF* _moneyLabel;
	//波 label
	LabelTTF* _waveLabel;

	//速度图片
	Sprite* _speedSprite_1;
	Sprite* _speedSprite_2;
	//暂停图片
	Sprite* _pauseSprite;
	Sprite* _resumeSprite;
	//菜单图片
	Sprite* _menuSprite;

	//菜单
	MenuItemSprite* _menuPause;
	MenuItemSprite* _menuSpeed;
	MenuItemSprite* _menuMenu;
	Menu* _menu;

	//血量
	Sprite* _hpSprite;
	LabelTTF* _hpLabel;
	int _hp;

};