#pragma 


/**
 * @file         GameOverLayer.h    
 * @date         2014-6-21
 * @author       shun_fzll
 * @brief   	 ��Ϸ��������layer ʤ������ʧ��
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

	//touch�¼����� �������´���
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);

	//����button�ص��¼�
	void setCallbackFunc(Ref* target, SEL_CallFuncN callfun);
	//���button
	bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);
	//��ť�ص��¼�
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