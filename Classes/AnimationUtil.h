#pragma once

/**
 * @file         AnimationUtil.h    
 * @date         2014-6-9
 * @author       shun_fzll
 * @brief   	 值得一提的是使用AnimationUtil需要先将png或者plist加入对应的TextureCache或者
 *				 SpriteFrameCache中
 */
#include "cocos2d.h"

using namespace cocos2d;

class AnimationUtil{
public:
	static AnimationUtil* getInstance();
	static void destroyInstance();

	//从TextureCache获取图片，分割放入AnimationCache中
	void initAnimationBySplitIMG(const char* filename,float time,int numOfpng);
	//从SpriteFrameCache中获取图片
	//文件名须符合一定规律，如 enemydie1.png enemydie2.png ...对应filename：enemydie
	void initAnimationBySpriteFrameName(const char* filename,float time,int numOfpng);
	
	//get the animate
	Animate* getAnimate(const char* keyForAnimation);
	
	//分割图片，图片来源于TextureCache
	Sprite* getSpriteBySplitIMG(const char* filename,int index,int totalNum);

	
private:
	static AnimationUtil* _pInstance;
};