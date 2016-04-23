#include "LoadingScene.h"
#include "Resources.h"
#include "GameData.h"
#include "ChooseScene.h"
#include "AnimationUtil.h"


bool LoadingScene::init(){
	if(!Layer::init()){
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();
	
	//background
	auto background = Sprite::create(IMG_LOADINGBG);
	background->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(background,0);

	//loading label
	_loadingLabel = LabelTTF::create("Loading...", "Arial", 25);
	_loadingLabel->setPosition(winSize.width / 2, winSize.height / 2 - 50);
	this->addChild(_loadingLabel);

	//progress bar
	_curProgress = 0;
	_progressBar = ControlSlider::create(
		IMG_LOADING_BAR_BG,
		IMG_LOADING_BAR,
		IMG_LOADING_BAR_THUMB
		);
	_progressBar->setPosition(winSize.width / 2, winSize.height / 2);
	_progressBar->setTouchEnabled(false);
	_progressBar->setMinimumValue(0);
	_progressBar->setMaximumValue(100);
	_progressBar->setValue(_curProgress);
	this->addChild(_progressBar,1);

	_barTip = Sprite::create(IMG_LOADING_BAR_TIP);
	_barTip->setPosition(
		winSize.width / 2 -  _progressBar->getContentSize().width / 2,
		winSize.height / 2 + 50);
	this->addChild(_barTip,1);

	_barTipLabel = LabelTTF::create("0%", "Arial", 20);
	_barTipLabel->setPosition(
		_barTip->getContentSize().width / 2,_barTip->getContentSize().height / 2
		);

	_barTip->addChild(_barTipLabel);
	
	//interval,repeat,delay
	this->schedule(schedule_selector(LoadingScene::loadingLogic),1.0 / 100 ,100,0.2f);

	
	return true;
}

Scene* LoadingScene::createScene(){
	if(GameData::getInstance()->_loadingScene == NULL){
		auto scene = Scene::create();
		auto layer = LoadingScene::create();
		scene->addChild(layer);
		//save scene
		GameData::getInstance()->_loadingScene = scene;
		//retaiin
		scene->retain();

		return scene;
	}
	return GameData::getInstance()->_loadingScene;
}

void LoadingScene::onEnter(){
	Layer::onEnter();
	//===========================ChooseScene======================
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(IMG_GIRL_PLIST,IMG_GIRL_PNG);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(IMG_CHOOSE_PLIST,IMG_CHOOSE_PNG);

	//===========================EnemyLayer======================
	//enemyÍ¼Æ¬
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(IMG_ENEMY_PLIST,IMG_ENEMY_PNG);
	//enemy birth and die ¶¯»­Í¼Æ¬
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(IMG_ENEMY_BD_PLIST,IMG_ENEMY_BD_PNG);
	//birthºÍdie¶¯»­
	AnimationUtil::getInstance()->initAnimationBySpriteFrameName("enemydie",0.5,5);
	AnimationUtil::getInstance()->initAnimationBySpriteFrameName("enemybirth",0.2,2);
	

	//===========================TowerLayer======================
	//towerlayerÍ¼Æ¬£¬Éý¼¶µÈÍ¼±ê
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(IMG_TOWER_LAYER_PLIST,IMG_TOWER_LAYER_PNG);
	//Ëþµ××ù
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(IMG_TOWERS_DZ_PLIST,IMG_TOWERS_DZ_PNG);
	//ËþÍ¼Æ¬
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(IMG_TOWERS_PLIST,IMG_TOWERS_PNG);
	//ËþÑ¡ÔñÍ¼Æ¬
	TextureCache::getInstance()->addImage(IMG_TOWERS_N);
	TextureCache::getInstance()->addImage(IMG_TOWERS_D);
	//Ñ¡Ôñ¿ò¶¯»­
	AnimationUtil::getInstance()->initAnimationBySpriteFrameName("select_0",0.4,4);
	//ÓÅÏÈ¹¥»÷¶¯»­
	AnimationUtil::getInstance()->initAnimationBySpriteFrameName("point0",0.3,3);

	//===========================PlantLayer======================
	//Ö²ÎïÍ¼Æ¬
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(IMG_PLANT_PLIST,IMG_PLANT_PNG);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(IMG_PLANT2_PLIST,IMG_PLANT2_PNG);
	
}

void LoadingScene::onExit(){
	Layer::onExit();
}


void LoadingScene::loadingCallback(){

}

void LoadingScene::loadingLogic(float dt){
	_curProgress ++;
	if(_curProgress > 100){
		//begin the game choose scene
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f,ChooseScene::createScene()));
		return;
	}
	_progressBar->setValue(_curProgress);

	int startX = _progressBar->getPositionX() - _progressBar->getContentSize().width / 2 +10 ;
	int unitX = _progressBar->getContentSize().width / 100;

	_barTip->setPositionX(startX + _curProgress * unitX);
	char str[10] = {0};
	sprintf(str,"%d%",_curProgress);

	_barTipLabel->setString(str);

}