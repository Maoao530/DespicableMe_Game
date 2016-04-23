/*

#include "GameScene.h"

bool GameScene::init(){
	if(!Scene::init()){
		return false;
	}

	auto gameHUD = GameHUD::create();
	auto gameLayer = GameLayer::create();

	
	this->addChild(gameLayer,1);
	this->addChild(gameHUD,1);

	DataModel::getInstance()->_gameHUD = gameHUD;
	DataModel::getInstance()->_gameLayer = gameLayer;

	return true;
}

*/