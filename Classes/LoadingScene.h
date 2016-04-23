#pragma once

/**
 * @file         LoadingScene.h    
 * @date         2014-6-1
 * @author       shun_fzll
 * @brief   	 preload the game's resources
 * 
 */

#include "cocos2d.h"
#include "extensions/cocos-ext.h"  

using namespace cocos2d::extension;
using namespace cocos2d;

class LoadingScene : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(LoadingScene);
	static Scene* createScene();

	virtual void onEnter();
	virtual void onExit();
	//更新进度条
	void loadingLogic(float dt);
	void loadingCallback();

private:
	ControlSlider* _progressBar;
	Sprite* _barTip;
	LabelTTF* _barTipLabel;
	LabelTTF* _loadingLabel;
	int _curProgress;
};