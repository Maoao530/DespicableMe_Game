#pragma once

/**
 * @file         WelcomeScene.h    
 * @date         2014-5-24
 * @author       shun_fzll
 * @brief   	 welcome ui 
 * 
 */

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace cocostudio;  
using namespace ui; 
using namespace CocosDenshion;


class WelcomeScene : public Layer{
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(WelcomeScene);

//	void onEnter();

//	void preloadMusic();

	void btnStartCallback(Ref *pSender, TouchEventType type);
	void btnSetCallback(Ref *pSender, TouchEventType type);
	void btnHelpCallback(Ref *pSender, TouchEventType type);
	void btnExitCallback(Ref *pSender, TouchEventType type);

	void popButtonCallback(cocos2d::CCNode *pNode);

	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event); 

private:
	Widget* _mainbgUI;
	Button* _startBtn;
	Button* _setBtn;
	Button* _helpBtn;
	Button* _exitBtn;
};