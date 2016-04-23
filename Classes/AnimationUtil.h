#pragma once

/**
 * @file         AnimationUtil.h    
 * @date         2014-6-9
 * @author       shun_fzll
 * @brief   	 ֵ��һ�����ʹ��AnimationUtil��Ҫ�Ƚ�png����plist�����Ӧ��TextureCache����
 *				 SpriteFrameCache��
 */
#include "cocos2d.h"

using namespace cocos2d;

class AnimationUtil{
public:
	static AnimationUtil* getInstance();
	static void destroyInstance();

	//��TextureCache��ȡͼƬ���ָ����AnimationCache��
	void initAnimationBySplitIMG(const char* filename,float time,int numOfpng);
	//��SpriteFrameCache�л�ȡͼƬ
	//�ļ��������һ�����ɣ��� enemydie1.png enemydie2.png ...��Ӧfilename��enemydie
	void initAnimationBySpriteFrameName(const char* filename,float time,int numOfpng);
	
	//get the animate
	Animate* getAnimate(const char* keyForAnimation);
	
	//�ָ�ͼƬ��ͼƬ��Դ��TextureCache
	Sprite* getSpriteBySplitIMG(const char* filename,int index,int totalNum);

	
private:
	static AnimationUtil* _pInstance;
};