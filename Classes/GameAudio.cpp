#include "GameAudio.h"
#include "GameData.h"
#include "Resources.h"

GameAuio* GameAuio::_pInstance = NULL;

GameAuio* GameAuio::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new GameAuio();
	}
	return _pInstance;
}

void GameAuio::destroyInstance(){
	if(_pInstance != NULL){
		delete _pInstance;
		_pInstance = NULL;
	}
}

void GameAuio::preloadMusic(){

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AUDIO_MAINBG);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(AUDIO_GAMEBG);


	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_BTNSELECT);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_ADDENEMY);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_FINAL_WAVE);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_JAMDIE);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_LOSE);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_WIN);

	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_SELECT_FAULT);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_SHOOT_SELECT);

	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_TOWER_SELECT);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_TOWER_BUILD);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_TOWER_SELL);
	SimpleAudioEngine::getInstance()->preloadEffect(AUDIO_TOWER_UPDATE);

	GameData::getInstance()->_music = true;
	GameData::getInstance()->_effect = true;

	//¼ÓÔØenemyÉùÒô
	char str[15] = {0};
	for(int i = 1; i <= 15; i++)
	{
		sprintf(str,"enemy%d.mp3",i);
		SimpleAudioEngine::getInstance()->preloadEffect(str);

	}
}

bool GameAuio::getBackgroundMusicState(){
	return GameData::getInstance()->_music ;
}

bool GameAuio::getEffectState(){
	return GameData::getInstance()->_effect;
}

void GameAuio::palyEffect(const char* filename){
	if( !GameData::getInstance()->_effect){
		return;
	}
	SimpleAudioEngine::getInstance()->playEffect(filename);
}


void GameAuio::playBackgroundMusic(const char* filename){
	SimpleAudioEngine::getInstance()->playBackgroundMusic(filename,true);
}

void GameAuio::stopBackgroundMusic(){
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void GameAuio::playOrPauseBackgroundMusic(){
	//music is not playing
	if( !GameData::getInstance()->_music){
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		return;
	}
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void GameAuio::changeBackgroundMusicState(){
	GameData::getInstance()->_music = !GameData::getInstance()->_music;
}

void GameAuio::changeEffectState(){
	GameData::getInstance()->_effect = !GameData::getInstance()->_effect;
}