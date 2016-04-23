#pragma once

/**
 * @file         GameAudio.h    
 * @date         2014-5-28
 * @author       shun_fzll
 * @brief   	 将音乐的控制集成一个类，避免代码重复
 * 
 */

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

enum MUSIC
{
	MAIN_MUSIC,	//0代表背景音乐，
	GAME_MUSIC	//1代表游戏音乐
};


class GameAuio{
public:

	static GameAuio* getInstance();
	static void destroyInstance();

	void preloadMusic();
	
	void playBackgroundMusic(const char* filename);
	void stopBackgroundMusic();
	void playOrPauseBackgroundMusic();

	void palyEffect(const char* filename);
	
	bool getBackgroundMusicState();
	bool getEffectState();

	void changeBackgroundMusicState();
	void changeEffectState();

	int _musicType;
private:
	static GameAuio* _pInstance;
};