#pragma once

/**
 * @file         HelpScene.h    
 * @date         2014-5-28
 * @author       shun_fzll
 * @brief   	 HelpUI 
 *				 include "HelpLayer" "HelpTowerLayer" "HelpEnemyLayer"
 */

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace ui;


enum LayerPos
{
	HELP_POS,
	ENEMY_POS,
	TOWER_POS
};
//menu tag
const int MENU_HELP_TAG = 0;
const int MENU_ENEMY_TAG = 1;
const int MENU_TOWER_TAG = 2;

const int BTN_CLOSE_TAG = 3;

//point tag
const int POINT_TAG = 100;



//---------------------- HelpLayer ------------------------

class HelpLayer : public Layer, public cocos2d::extension::ScrollViewDelegate{
public:
	virtual bool init();
	CREATE_FUNC(HelpLayer);
public:
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);
public:
	virtual void onEnter();
	virtual void onExit();
	
	//touch event , set touch not pass down
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
	//adjust scrollview's position
	void adjustScrollView(float offset);
	
private:
	EventListenerTouchOneByOne* _listener;
	cocos2d::extension::ScrollView *  _scrollView;
	Layer* _containLayer;
	Point _touchPoint;
	int _currentPage;
	int _pageCount;
	
};

//---------------------- HelpEnemyLayer ------------------------

class HelpEnemyLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(HelpEnemyLayer);
private:
	
};

//---------------------- HelpTowerLayer ------------------------

class HelpTowerLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(HelpTowerLayer);

public:
	virtual void onEnter();
	virtual void onExit();

	//touch event , set touch not pass down
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);

	//adjust scrollview's position
	void adjustScrollView(float offset);

private:
	EventListenerTouchOneByOne* _listener;
	cocos2d::extension::ScrollView *  _scrollView;
	Layer* _containLayer;
	Point _touchPoint;
	int _currentPage;
	int _pageCount;

};


//---------------------- HelpScene ------------------------
class HelpScene : Layer{
public:
	HelpScene();
	~HelpScene();
	virtual bool init();
	CREATE_FUNC(HelpScene);
	static Scene* createScene();
	//menu's callback function
	void menuCallback(Ref* pSender);
	//Close button's callback function
	void btnCloseCallback(Ref *pSender, ui::TouchEventType type);
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event); 
	
private:
	//layer
	LayerMultiplex* _layerMuti;
	int _currentLayerPos;
	HelpLayer* _helpLayer;
	HelpEnemyLayer* _enemyLayer;
	HelpTowerLayer* _towerLayer;

	//menu
	MenuItemSprite* _menuHelp;
	MenuItemSprite* _menuEnemy;
	MenuItemSprite* _menuTower;
	MenuItemImage* _menuClose;
	Menu* _menu;
	int _currentMenuTag;

	//menu image
	Node* _menuHelpSprite_n;
	Node* _menuHelpSprite_p;
	Node* _menuEnemySprite_n;
	Node* _menuEnemySprite_p;
	Node* _menuTowerSprite_n;
	Node* _menuTowerSprite_p;
};

