#include "GameData.h"

GameData* GameData::_pInstance = NULL;

GameData* GameData::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new GameData();
	}
	return _pInstance;
}

void GameData::destroyInstance(){
	if(_pInstance != NULL){
		delete _pInstance;
		_pInstance = NULL;
	}
}

GameData::GameData(){
	_welcomeScene = NULL;
	_settingScene = NULL;
	_helpScene = NULL;
	_loadingScene = NULL;
	_chooseScene = NULL;
}

GameData::~GameData(){
	CC_SAFE_RELEASE(_welcomeScene);
	CC_SAFE_RELEASE(_settingScene);
	CC_SAFE_RELEASE(_helpScene);
	CC_SAFE_RELEASE(_loadingScene);
}