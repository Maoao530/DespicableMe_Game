#pragma 


/**
 * @file         GameOverLayer.h    
 * @date         2014-6-21
 * @author       shun_fzll
 * @brief   	 游戏结束弹出layer 胜利或者失败
 * 
 */

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class GameOverLayer : public LayerColor{
public:
	virtual bool init();
	CREATE_FUNC(GameOverLayer);
	static GameOverLayer* create(const char* backgroundImage,int wave,int level);

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

	LabelTTF* _waveLabel;
	LabelTTF* _levelLabel;
};