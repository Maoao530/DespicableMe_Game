#include "MainScene.h"
#include "GameData.h"
#include "Resources.h"
#include "GameAudio.h"
#include "PopupMenuLayer.h"
#include "ChooseScene.h"
#include "WayPoint.h"
#include "EnemyLayer.h"
#include "XmlParser.h"
#include "StringUtil.h"
#include "PlantPoint.h"
#include "PlantLayer.h"
#include "TowerLayer.h"

MainScene::MainScene(){
	CCLOG("MainScene()");
	_map = NULL;
	_background = NULL;
	_road = NULL;
	_menubg = NULL;
	_pauseSprite = NULL;
	_moneyLabel = NULL;
	_waveLabel = NULL;	

	_speedSprite_1 = NULL;
	_speedSprite_2 = NULL;
	_pauseSprite = NULL;
	_resumeSprite = NULL;
	_menuSprite = NULL;
	
	//需要在场景开始前清空一下vector
	auto gd = GameData::getInstance() ;
	gd->_bulletVector.clear();
	gd->_enemysVector.clear();
	gd->_plantPointVector.clear();
	gd->_plantsVector.clear();
	gd->_pointsVector.clear();
	gd->_towersVector.clear();
	gd->_wavesVector.clear();
	gd->_enemyNumVector.clear();
	gd->_bulletToDeleteVector.clear();

	gd->_currentWave = 1;
	gd->_currentSpeed = 1;
	
};
MainScene::~MainScene(){
	CC_SAFE_RELEASE(_speedSprite_1);
	CC_SAFE_RELEASE(_speedSprite_2);
	CC_SAFE_RELEASE(_pauseSprite);
	CC_SAFE_RELEASE(_resumeSprite);
	CC_SAFE_RELEASE(_menuSprite);
	CCLOG("~~MainScene()");
	//释放

	if(GameData::getInstance()->_enemysVector.size() > 0){
		GameData::getInstance()->_enemysVector.clear();
	}
}

void MainScene::initGameParameters(int level){

	XMLParser *pXmlParser = NULL;

	GameData* gameData = GameData::getInstance();

	gameData->_currentWave = 1;
	gameData->_currentLevel = level;
	gameData->_currentSpeed = 1;
	gameData->_isPause = false;

	switch (level)
	{
	case 1:
		GameData::getInstance()->_currentMoney = 1000;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map1.xml");
		_map = TMXTiledMap::create("map1.tmx");
		break;
	case 2:
		GameData::getInstance()->_currentMoney = 1200;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map2.xml");
		_map = TMXTiledMap::create("map2.tmx");
		break;
	case 3:
		GameData::getInstance()->_currentMoney = 1500;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map3.xml");
		_map = TMXTiledMap::create("map3.tmx");
		break;
	case 4:
		GameData::getInstance()->_currentMoney = 1800;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map4.xml");
		_map = TMXTiledMap::create("map4.tmx");
		break;
	case 5:
		GameData::getInstance()->_currentMoney = 2000;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map5.xml");
		_map = TMXTiledMap::create("map5.tmx");
		break;
	case 6:
		GameData::getInstance()->_currentMoney = 2200;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map6.xml");
		_map = TMXTiledMap::create("map6.tmx");
		break;
	case 7:
		GameData::getInstance()->_currentMoney = 2500;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map7.xml");
		_map = TMXTiledMap::create("map7.tmx");
		break;
	case 8:
		GameData::getInstance()->_currentMoney = 2600;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map8.xml");
		_map = TMXTiledMap::create("map8.tmx");
		break;
	case 9:
		GameData::getInstance()->_currentMoney = 3000;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map9.xml");
		_map = TMXTiledMap::create("map9.tmx");
		break;
	case 10:
		GameData::getInstance()->_currentMoney = 3000;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map10.xml");
		_map = TMXTiledMap::create("map10.tmx");
		break;
	case 11:
		GameData::getInstance()->_currentMoney = 3100;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map11.xml");
		_map = TMXTiledMap::create("map11.tmx");
		break;
	case 12:
		GameData::getInstance()->_currentMoney = 3300;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map12.xml");
		_map = TMXTiledMap::create("map12.tmx");
		break;
	case 13:
		GameData::getInstance()->_currentMoney = 3500;
		//读取地图参数（敌人顺序）
		pXmlParser = XMLParser::parseWithFile("map13.xml");
		_map = TMXTiledMap::create("map13.tmx");
		break;
	}

	//总波数
	String *pTotalWave = pXmlParser->getString("total_wave");
	int totalWave = atoi(pTotalWave->getCString());
	GameData::getInstance()->_totalWave = totalWave;
	
	//获取每一波的怪物出场顺序（一串数字）保存到vector<int>中，将vector<int>放入_wavesVector中
	//形如:<wave id="1" >1,1,1,1,1,2,2,2,2,2</wave>
	char temp[5] = {0};
	for(int i = 1; i <= totalWave; i++){
		sprintf(temp,"%d",i);
		String* pStr = pXmlParser->getString(temp) ;
		std::vector<int> result = StringUtil::splitForInt(pStr->getCString(),",");
		gameData->_wavesVector.push_back(result);
	}
}

MainScene* MainScene::create(int level){
	MainScene* layer = new MainScene();
	if(layer && layer->init(level))
	{
		layer->autorelease();
		return layer;
	}
	else
	{
		delete layer;
		layer = NULL;
		return NULL;
	}

}

Scene* MainScene::createScene(int level){
	auto scene = Scene::create();
	auto layer = MainScene::create(level);
	scene->addChild(layer);
	return scene;
}

bool MainScene::init(int level){
	if(!Layer::init()){
		return false;
	}
	//parameters
	initGameParameters(level);

	auto winSize = Director::getInstance()->getWinSize();

	//add the tmxmap
	
	_background = _map->layerNamed(MAP_BACKGROUND);
	_road = _map->layerNamed(MAP_ROAD);
	_object = _map->objectGroupNamed(MAP_OBJECT);
	this->addChild(_map,0);
	Point mapAPos = _map->getAnchorPoint();
	Point mapPos = _map->getPosition();
	CCLOG("map an pos = (%f,%f) ",mapAPos.x,mapAPos.y);
	CCLOG("map pos = (%f,%f) ",mapPos.x,mapPos.y);

	//menubg
	_menubg = Sprite::create(IMG_MENU_BG);
	_menubg->setPosition(winSize.width / 2, winSize.height - _menubg->getContentSize().height / 2);
	this->addChild(_menubg,0);

	//moneylabel
	char moneyStr[10] = {0};
	sprintf(moneyStr,"%d",GameData::getInstance()->_currentMoney);
	_moneyLabel = LabelTTF::create(moneyStr,"Arial",24);
	_moneyLabel->setPosition(100, _menubg->getContentSize().height / 2);
	_menubg->addChild(_moneyLabel,0);

	//current wave
	char waveStr[10] = {0};
	sprintf(waveStr,"%d / %d",GameData::getInstance()->_currentWave,GameData::getInstance()->_totalWave);
	_waveLabel = LabelTTF::create(waveStr,"Arial",24);
	_waveLabel->setColor(Color3B::RED);
	_waveLabel->setPosition(_menubg->getContentSize().width / 2, _menubg->getContentSize().height / 2);
	_menubg->addChild(_waveLabel,0);

	//pause label
	_pauseLabel = Sprite::create(IMG_PAUSE_LABEL);
	_pauseLabel->setPosition(_menubg->getContentSize().width / 2, _menubg->getContentSize().height / 2);
	_menubg->addChild(_pauseLabel,1);
	_pauseLabel->setVisible(false);

	//menu sprite
	_speedSprite_1 = Sprite::create(IMG_MENU_SPEED_1);
	_speedSprite_1->retain();
	_speedSprite_2 = Sprite::create(IMG_MENU_SPEED_2);
	_speedSprite_2->retain();
	_pauseSprite = Sprite::create(IMG_MENU_PAUSE);
	_pauseSprite->retain();
	_resumeSprite = Sprite::create(IMG_MENU_RESUME);
	_resumeSprite->retain();
	_menuSprite = Sprite::create(IMG_MENU_MENUBTN);
	_menuSprite->retain();

	//menu
	_menuSpeed = MenuItemSprite::create(
		_speedSprite_1,
		_speedSprite_1,
		CC_CALLBACK_1(MainScene::menuCallback,this)
		);
	_menuPause = MenuItemSprite::create(
		_pauseSprite,
		_pauseSprite,
		CC_CALLBACK_1(MainScene::menuCallback,this)
		);

	_menuMenu = MenuItemSprite::create(
		_menuSprite,
		_menuSprite,
		CC_CALLBACK_1(MainScene::menuCallback,this)
		);

	_menuSpeed->setTag(MENU_SPEED_TAG);
	_menuPause->setTag(MENU_PAUSE_TAG);
	_menuMenu->setTag(MENU_MENU_TAG);

	_menu = Menu::create(_menuSpeed, _menuPause, _menuMenu, NULL);
	_menu->alignItemsHorizontallyWithPadding(10);
	_menu->setAnchorPoint(Point(1,0.5));
	_menu->setPosition(
		_menubg->getContentSize().width - 200,
		_menubg->getContentSize().height / 2);
	_menubg->addChild(_menu,0);

	

	//waypoints
	this->addWayPoints();
	//plantpoints
	this->addPlantPoint();

	//start
	auto start = Sprite::create("start.png");
	start->setPosition(GameData::getInstance()->_pointsVector.at(0)->getPosition());
	this->addChild(start,0);
	//end
	auto end = Sprite::create("end.png");
	end->setPosition(
		GameData::getInstance()->_pointsVector.at(
		GameData::getInstance()->_pointsVector.size() - 1)->getPosition());
	this->addChild(end,0);

	//hp
	_hpSprite = Sprite::create("HP.png");
	_hpSprite->setPosition(
		end->getPositionX() + 32 + _hpSprite->getContentSize().width / 2,
		end->getPositionY());
	this->addChild(_hpSprite,0);

	//hpLabel
	_hp = 10;
	char hpStr[10] = {0};
	sprintf(hpStr,"%d",_hp);
	_hpLabel = LabelTTF::create(hpStr,"",20);
	_hpLabel->setPosition(_hpSprite->getContentSize().width / 2 + 10, _hpSprite->getContentSize().height / 2);
	_hpSprite->addChild(_hpLabel);
	
	//plantlayer
	auto plantLayer = PlantLayer::create();
	this->addChild(plantLayer,1);

	//enemylayer
	auto enemyLayer = EnemyLayer::create();
	this->addChild(enemyLayer,1);

	//towerlayer
	auto towerLayer = TowerLayer::create();
	this->addChild(towerLayer,1);

	//播放游戏音乐
	if(GameAuio::getInstance()->getBackgroundMusicState() == true)
	{
		GameAuio::getInstance()->stopBackgroundMusic();
		GameAuio::getInstance()->playBackgroundMusic(AUDIO_GAMEBG);
		GameAuio::getInstance()->_musicType = GAME_MUSIC;
	}
	

	//注册捕捉监听  
	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);  

	return true;
}

void MainScene::menuCallback(Ref* pSender){
	Node* node = (Node*)pSender;
	int tag = node->getTag();
	PopupMenuLayer* pml;
	switch (tag)
	{
	case MENU_SPEED_TAG:
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		if(GameData::getInstance()->_currentSpeed == 1){
			_menuSpeed->setNormalImage(_speedSprite_2);
			_menuSpeed->setSelectedImage(_speedSprite_2);
			GameData::getInstance()->_currentSpeed = 2;
			//change enemy and tower's speed to x2
			changeSpeedX(2);

		}else
		{
			_menuSpeed->setNormalImage(_speedSprite_1);
			_menuSpeed->setSelectedImage(_speedSprite_1);
			GameData::getInstance()->_currentSpeed = 1;
			changeSpeedX(1);
		}
		break;
	case MENU_PAUSE_TAG:
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		if(GameData::getInstance()->_isPause){
			_menuPause->setNormalImage(_pauseSprite);
			_menuPause->setSelectedImage(_pauseSprite);
			_pauseLabel->setVisible(false);
			GameData::getInstance()->_isPause = false;
			Director::getInstance()->resume();
		}else
		{
			_menuPause->setNormalImage(_resumeSprite);
			_menuPause->setSelectedImage(_resumeSprite);
			_pauseLabel->setVisible(true);
			GameData::getInstance()->_isPause = true;
			Director::getInstance()->pause();
		}
		break;
	case MENU_MENU_TAG:
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		if(!Director::getInstance()->isPaused() ){
			Director::getInstance()->pause();
		}

		//pop up the menu layer
		pml = PopupMenuLayer::create(IMG_POP_MENU_BG);
		pml->setCallbackFunc(this,callfuncN_selector(MainScene::popupMenuCallback));
		pml->addButton(IMG_POP_MENU_RESUME_N,IMG_POP_MENU_RESUME_P,NULL,POPMENU_RESUME_TAG);
		pml->addButton(IMG_POP_MENU_RESTART_N,IMG_POP_MENU_RESTART_P,NULL,POPMENU_RESTART_TAG);
		pml->addButton(IMG_POP_MENU_SELECT_N,IMG_POP_MENU_SELECT_P,NULL,POPMENU_SELECT_TAG);
		this->addChild(pml,1);
		break;
	}
}

void MainScene::popupMenuCallback(Node* pNode){
	int tag = pNode->getTag();
//	CCLog("【=====MainScene::popButtonCallback======】button call back. tag: %d",tag);
	GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
	switch (tag)
	{
	case POPMENU_RESUME_TAG:	//resume
		if(GameData::getInstance()->_isPause){
			return;
		}
		if(Director::getInstance()->isPaused()){
			Director::getInstance()->resume();
		}
		break;
	case POPMENU_RESTART_TAG:	//restart
		if(Director::getInstance()->isPaused()){
			Director::getInstance()->resume();
		}
		
		Director::getInstance()->replaceScene(
			TransitionFade::create(1.f,MainScene::createScene(GameData::getInstance()->_currentLevel)));
		break;
	case POPMENU_SELECT_TAG:	//return choose scene
		if(Director::getInstance()->isPaused()){
			Director::getInstance()->resume();
		}
		Director::getInstance()->replaceScene(
			TransitionFade::create(1.f,ChooseScene::createScene()));
		break;
	}
}


void MainScene::addWayPoints()
{
	WayPoint* wayPoint = NULL;

	char str[10] = {0};
	int i = 0;
	sprintf(str,"points%d",i);

	//key-value 
	ValueMap wayPoint_Map = _object->objectNamed(str);
	while (!wayPoint_Map.empty())
	{
		//get the position in opengl coordination,but why?
		float x = wayPoint_Map.at("x").asInt();
		float y = wayPoint_Map.at("y").asInt();

		std::string isEnd = wayPoint_Map.at("type").asString();
//		CCLog("%s:(%f,%f)==type:%s",str,x,y,isEnd.c_str());

		wayPoint = WayPoint::create();
		wayPoint->setPosition(Point(x,y));
		if(isEnd == "end"){
			wayPoint->setEnd(true);
		}
		//添加到gamedata中
		GameData::getInstance()->_pointsVector.pushBack(wayPoint);

		sprintf(str,"points%d",++i);
		wayPoint_Map = _object->objectNamed(str);
	}
	wayPoint = NULL;
}

void MainScene::addPlantPoint(){

	PlantPoint* plantPoint = NULL;
	ValueMap plantPoint_Map = _object->objectNamed("jam");

	ValueVector vector = _object->getObjects();
	for(const Value& value : vector){
		const ValueMap& valueMap = value.asValueMap();

		if (valueMap.at("name").asString() == "jam")
		{
			//get the position in opengl coordination,but why?
			float x = valueMap.at("x").asInt();
			float y = valueMap.at("y").asInt();
			
			plantPoint = PlantPoint::create();
			plantPoint->setPosition(Point(x,y));

			//set plant type
			std::string type = valueMap.at("type").asString();

			CCLog("jam:(%f,%f)==type:%s",x,y,type.c_str());
			if(type == "honglan"){
				plantPoint->setPlantType(HONGLAN);
			}else if(type == "hua"){
				plantPoint->setPlantType(HUA);
			}else if(type == "quan"){
				plantPoint->setPlantType(QUAN);
			}else if(type == "lanjuan"){
				plantPoint->setPlantType(LANJUAN);
			}
			else if(type == "honglv"){
				plantPoint->setPlantType(HONGLV);
			}
			else if(type == "lvjuan"){
				plantPoint->setPlantType(LVJUAN);
			}
			else if(type == "xiaomo"){
				plantPoint->setPlantType(XIAOMO);
			}
			else if(type == "xiaocao"){
				plantPoint->setPlantType(XIAOCAO);
			}
			else if(type == "huangci"){
				plantPoint->setPlantType(HUANGCI);
			}
			else if(type == "damo"){
				plantPoint->setPlantType(DAMO);
			}
			else if(type == "zhuang"){
				plantPoint->setPlantType(ZHUANG);
			}
			else if(type == "huigan"){
				plantPoint->setPlantType(HUIGAN);
			}
			else if(type == "fang"){
				plantPoint->setPlantType(FANG);
			}
			else if(type == "huanggan"){
				plantPoint->setPlantType(HUANGGAN);
			}
			//jam2
			else if(type == "yuanxrz"){
				plantPoint->setPlantType(YUANXRZ);
			}
			else if(type == "gu"){
				plantPoint->setPlantType(GU);
			}
			else if(type == "box"){
				plantPoint->setPlantType(BOX);
			}
			else if(type == "shenshu"){
				plantPoint->setPlantType(SHENSHU);
			}
			else if(type == "qianshu"){
				plantPoint->setPlantType(QIANSHU);
			}
			else if(type == "z"){
				plantPoint->setPlantType(Z);
			}
			else if(type == "h"){
				plantPoint->setPlantType(H);
			}
			else if(type == "huaxrz"){
				plantPoint->setPlantType(HUAXRZ);
			}
			else if(type == "xiaoxrz"){
				plantPoint->setPlantType(XIAOXRZ);
			}
			else if(type == "shenshugan"){
				plantPoint->setPlantType(SHENSHUGAN);
			}
			else if(type == "jiancao"){
				plantPoint->setPlantType(JIANCAO);
			}
			else if(type == "qianshugan"){
				plantPoint->setPlantType(QIANSHUGAN);
			}
			
			GameData::getInstance()->_plantPointVector.pushBack(plantPoint);
		}
	}
}

void MainScene::changeSpeedX(int speedX)
{
	//1x -> 2x
	if(speedX == 2)
	{
		//遍历enemy
		for(Enemy* enemy : GameData::getInstance()->_enemysVector)
		{
			Sequence* sequence1 =  (Sequence*)enemy->getActionByTag(ENEMY_MOVE_ACTION_TAG1);
			Sequence* sequence2 =  (Sequence*)enemy->getActionByTag(ENEMY_MOVE_ACTION_TAG2);
			if(sequence1 != NULL)
			{
				enemy->stopActionByTag(ENEMY_MOVE_ACTION_TAG1);
				enemy->_currentWayPoint--;
				enemy->_speed *= speedX;
				((EnemyLayer*)enemy->getParent())->enemyMove(enemy);

			}
			else if(sequence2 != NULL)
			{

				enemy->stopActionByTag(ENEMY_MOVE_ACTION_TAG2);
				enemy->_speed *= 2;
				enemy->_currentWayPoint--;
				((EnemyLayer*)enemy->getParent())->followPath(enemy);
			}
		}

		//遍历tower
		for(Tower* tower : GameData::getInstance()->_towersVector)
		{
			tower->_logicTime /= 2;
			if(tower->_towerType == LINE_SINGLE){
				tower->_attackValue *= 2;
			}
			tower->changeTowerLogicTime(tower->_logicTime);
		}
	}
	//2x -> 1x
	else if(speedX == 1)
	{
		//遍历enemy
		for(Enemy* enemy : GameData::getInstance()->_enemysVector)
		{
			Sequence* sequence1 =  (Sequence*)enemy->getActionByTag(ENEMY_MOVE_ACTION_TAG1);
			Sequence* sequence2 =  (Sequence*)enemy->getActionByTag(ENEMY_MOVE_ACTION_TAG2);
			if(sequence1 != NULL)
			{
				enemy->stopActionByTag(ENEMY_MOVE_ACTION_TAG1);
				enemy->_currentWayPoint--;
				enemy->_speed /= 2;
				((EnemyLayer*)enemy->getParent())->enemyMove(enemy);

			}
			else if(sequence2 != NULL)
			{

				enemy->stopActionByTag(ENEMY_MOVE_ACTION_TAG2);
				enemy->_speed /= 2;
				enemy->_currentWayPoint--;
				((EnemyLayer*)enemy->getParent())->followPath(enemy);
			}
		}

		//遍历tower
		for(Tower* tower : GameData::getInstance()->_towersVector)
		{
			tower->_logicTime *= 2;
			if(tower->_towerType == LINE_SINGLE){
				tower->_attackValue /= 2;
			}
			tower->changeTowerLogicTime(tower->_logicTime);
		}
	}
}

void MainScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACKSPACE:   //返回键听
		{
			GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
			Director::getInstance()->replaceScene(
				TransitionFade::create(0.5f,ChooseScene::createScene()));
			break;
		}
	case EventKeyboard::KeyCode::KEY_MENU:      //菜单监听

		break;
	case::EventKeyboard::KeyCode::KEY_HOME:
		break;
	default:
		break;
	}
}