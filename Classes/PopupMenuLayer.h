#pragma once

/**
 * @file         PopupMenuLayer.h    
 * @date         2014-6-8
 * @author       shun_fzll
 * @brief   	 popup menu layer
 * 
 */

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class PopupMenuLayer : public LayerColor{
public:

	virtual bool init();
	CREATE_FUNC(PopupMenuLayer);
	static PopupMenuLayer* create(const char* backgroundImage);

	//touch事件监听 屏蔽向下触摸
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);

	//设置button回调事件
	void setCallbackFunc(Ref* target, SEL_CallFuncN callfun);
	//添加button
	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);
	//按钮回调事件
	void buttonCallBack(Ref* pSender);

	virtual void onEnter();
	virtual void onExit();

private:
	Menu* _menu;

	Sprite* _background;
	Size _backgroundSize;

	Ref* m_callbackListener;
	SEL_CallFuncN m_callback;
};