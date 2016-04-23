#pragma once

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


using namespace cocos2d;
using namespace cocostudio;  
using namespace ui; 


class SettingScene : public Layer
{
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(SettingScene);

	void menuCallback(Ref* pSender);

	void btnEffectCallback(Ref *pSender, TouchEventType type);
	void btnMusicCallback(Ref *pSender, TouchEventType type);
	void btnCloseCallback(Ref *pSender, TouchEventType type);

	void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event); 

private:
	Widget* _setUI;
	Button* _effectBtn;
	Button* _musicBtn;
	Button* _closeBtn;


};