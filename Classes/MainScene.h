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
	//��ʼ����Ϸ����
	void initGameParameters(int level);
	//�˵��ص�
	void menuCallback(Ref* pSender);
	//�����˵��ص�
	void popupMenuCallback(Node* pNode);
	//���waypoint
	void addWayPoints();
	//���plantPoint
	void addPlantPoint();
	//������Ϸ�ٶ�
	void changeSpeedX(int speedX);
	//
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event); 
public:
	//tmx��ͼ
	TMXTiledMap* _map;
	TMXLayer* _background;
	TMXLayer* _road;
	TMXObjectGroup* _object;
	//�˵�����ͼƬ
	Sprite* _menubg;
	//��ͣ��ǩͼƬ
	Sprite* _pauseLabel;
	//money Label
	LabelTTF* _moneyLabel;
	//�� label
	LabelTTF* _waveLabel;

	//�ٶ�ͼƬ
	Sprite* _speedSprite_1;
	Sprite* _speedSprite_2;
	//��ͣͼƬ
	Sprite* _pauseSprite;
	Sprite* _resumeSprite;
	//�˵�ͼƬ
	Sprite* _menuSprite;

	//�˵�
	MenuItemSprite* _menuPause;
	MenuItemSprite* _menuSpeed;
	MenuItemSprite* _menuMenu;
	Menu* _menu;

	//Ѫ��
	Sprite* _hpSprite;
	LabelTTF* _hpLabel;
	int _hp;

};