#pragma once

/**
 * @file         ChooseScene.h    
 * @date         2014-6-3
 * @author       shun_fzll
 * @brief   	 choose game level and start the game
 * 
 */

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

class ChooseScene : public Layer{
public:
	ChooseScene(){}
	~ChooseScene();
	virtual bool init();
	CREATE_FUNC(ChooseScene);
	static Scene* createScene();
	//按钮回调事件
	void btnCallback(Ref *pSender, TouchEventType type);
	void getCurrentLevel();
	void popButtonCallback(Node *pNode);
	void btnExitCallback(Ref *pSender, TouchEventType type);
	//touch
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
	//
	virtual void onEnter();
	virtual void onExit();
	//键盘监听事件
	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event); 

private:
	Widget* _chooseUI;
	Button* _btnExit;

	int _currentPassLevel;

	Sprite* _girl;
	Repeat* _animate;
};