#include "HelpScene.h"
#include "GameData.h"
#include "Resources.h"
#include "GameAudio.h"
#include "WelcomeScene.h"
#include <string>

HelpScene::HelpScene(){

	//menu image
	_menuHelpSprite_n = NULL;
	_menuHelpSprite_p = NULL;
	_menuEnemySprite_n = NULL;
	_menuEnemySprite_p = NULL;
	_menuTowerSprite_n = NULL;
	_menuTowerSprite_p = NULL;

}

HelpScene::~HelpScene(){

	//对于手动retain的对象需要手动release

	CC_SAFE_RELEASE(_menuHelpSprite_n);
	CC_SAFE_RELEASE(_menuHelpSprite_p);
	CC_SAFE_RELEASE(_menuEnemySprite_n);
	CC_SAFE_RELEASE(_menuEnemySprite_p);
	CC_SAFE_RELEASE(_menuTowerSprite_n);
	CC_SAFE_RELEASE(_menuTowerSprite_p);
	
	CCLog("HelpScene::~HelpScene(): relase");
}

bool HelpScene::init(){
	if(!Layer::init()){
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	//background
	auto background = Sprite::create(IMG_HELPBG);
	background->setAnchorPoint(Point::ZERO);
	this->addChild(background,0);

	//close button
	auto closeBtn = ui::Button::create(IMG_BTN_CLOSE);
	closeBtn->addTouchEventListener(this,toucheventselector(HelpScene::btnCloseCallback));
	closeBtn->setTag(BTN_CLOSE_TAG);
	closeBtn->setPosition(Point(winSize.width / 2 + 280,winSize.height / 2 + 150));
	this->addChild(closeBtn,10);

	//menu
	_menuHelpSprite_n = Sprite::create(IMG_MENU_HELP_N);
	_menuHelpSprite_n->retain();
	_menuHelpSprite_p = Sprite::create(IMG_MENU_HELP_P);
	_menuHelpSprite_p->retain();

	_menuEnemySprite_n = Sprite::create(IMG_MENU_ENEMY_N);
	_menuEnemySprite_n->retain();
	_menuEnemySprite_p = Sprite::create(IMG_MENU_ENEMY_P);
	_menuEnemySprite_p->retain();

	_menuTowerSprite_n = Sprite::create(IMG_MENU_TOWER_N);
	_menuTowerSprite_n->retain();
	_menuTowerSprite_p = Sprite::create(IMG_MENU_TOWER_P);
	_menuTowerSprite_p->retain();

	_menuHelp = MenuItemSprite::create(
		_menuHelpSprite_p,
		_menuHelpSprite_p,
		CC_CALLBACK_1(HelpScene::menuCallback,this));

	_menuEnemy = MenuItemSprite::create(
		_menuEnemySprite_n,
		_menuEnemySprite_n,
		CC_CALLBACK_1(HelpScene::menuCallback,this));

	_menuTower = MenuItemSprite::create(
		_menuTowerSprite_n,
		_menuTowerSprite_n,
		CC_CALLBACK_1(HelpScene::menuCallback,this));

	
	_menuHelp->setTag(MENU_HELP_TAG);
	_menuEnemy->setTag(MENU_ENEMY_TAG);
	_menuTower->setTag(MENU_TOWER_TAG);
	

	_menu = Menu::create(_menuHelp,_menuEnemy,_menuTower,NULL);
	_menu->alignItemsHorizontallyWithPadding(5);
	_menu->setPosition(winSize.width / 2 , winSize.height / 2 + 200);

	//set the menu localZOrder top
	this->addChild(_menu,10);		
	
	//set default menu tag
	_currentMenuTag = MENU_HELP_TAG;
	
	//set the default layer position
	_currentLayerPos = HELP_POS;


	//add the _helpLayer，_enemyLayer，_towerLayer

	_helpLayer = HelpLayer::create();
 	_helpLayer->setAnchorPoint(Point::ZERO);
 	_helpLayer->setPosition(Point::ZERO);

	_enemyLayer = HelpEnemyLayer::create();
	_enemyLayer->setAnchorPoint(Point::ZERO);
	_enemyLayer->setPosition(Point::ZERO);

	_towerLayer = HelpTowerLayer::create();
	_towerLayer->setAnchorPoint(Point::ZERO);
	_towerLayer->setPosition(Point::ZERO);

	_layerMuti = LayerMultiplex::create(_helpLayer,_enemyLayer,_towerLayer,NULL);
	_layerMuti->setAnchorPoint(Point::ZERO);
	_layerMuti->setPosition(Point::ZERO);
	_layerMuti->switchTo(_currentLayerPos);

	this->addChild(_layerMuti,1);

	//注册捕捉监听  
	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(HelpScene::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this); 
	
	return true;
}

Scene* HelpScene::createScene(){
	if(GameData::getInstance()->_helpScene == NULL){
		auto scene = Scene::create();
		auto layer = HelpScene::create();
		scene->addChild(layer);
		//save scene
		GameData::getInstance()->_helpScene = scene;
		//retaiin
		scene->retain();

		return scene;
	}
	return GameData::getInstance()->_helpScene;
}


void HelpScene::menuCallback(Ref* pSender){
	Node* item = (Node*)pSender;
	int tag = item->getTag();
	CCLog("menu tag : %d",tag);

	GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);

	switch (tag)
	{
	case MENU_HELP_TAG:
		if(_currentMenuTag == MENU_HELP_TAG)
			return;
		//change menu normal and selected image
		_menuHelp->setNormalImage(_menuHelpSprite_p);
		_menuHelp->setSelectedImage(_menuHelpSprite_p);

		//restore menu normal and selected image
		_menuEnemy->setNormalImage(_menuEnemySprite_n);
		_menuEnemy->setSelectedImage(_menuEnemySprite_n);
		_menuTower->setNormalImage(_menuTowerSprite_n);
		_menuTower->setSelectedImage(_menuTowerSprite_n);

		//change current menu tag
		_currentMenuTag = MENU_HELP_TAG;

		//change current layer pos
		_currentLayerPos = HELP_POS;
		_layerMuti->switchTo(_currentLayerPos);
		
		break;
	case MENU_ENEMY_TAG:
		if(_currentMenuTag == MENU_ENEMY_TAG)
			return;
		//change menu normal and selected image
		_menuEnemy->setNormalImage(_menuEnemySprite_p);
		_menuEnemy->setSelectedImage(_menuEnemySprite_p);

		//restore menu normal and selected image
		_menuHelp->setNormalImage(_menuHelpSprite_n);
		_menuHelp->setSelectedImage(_menuHelpSprite_n);
		_menuTower->setNormalImage(_menuTowerSprite_n);
		_menuTower->setSelectedImage(_menuTowerSprite_n);
		
		//change current menu tag
		_currentMenuTag = MENU_ENEMY_TAG;

		//change current layer pos
		_currentLayerPos = ENEMY_POS;
		_layerMuti->switchTo(_currentLayerPos);

		break;
	case MENU_TOWER_TAG:
		if(_currentMenuTag == MENU_TOWER_TAG)
			return;
		//change menu normal and selected image
		_menuTower->setNormalImage(_menuTowerSprite_p);
		_menuTower->setSelectedImage(_menuTowerSprite_p);

		//restore menu normal and selected image
		_menuHelp->setNormalImage(_menuHelpSprite_n);
		_menuHelp->setSelectedImage(_menuHelpSprite_n);
		_menuEnemy->setNormalImage(_menuEnemySprite_n);
		_menuEnemy->setSelectedImage(_menuEnemySprite_n);

		//change current menu tag
		_currentMenuTag = MENU_TOWER_TAG;

		//change current layer pos
		_currentLayerPos = TOWER_POS;
		_layerMuti->switchTo(_currentLayerPos);

		break;
	}
}

void HelpScene::btnCloseCallback(Ref *pSender, ui::TouchEventType type){
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		break;

	case TouchEventType::TOUCH_EVENT_ENDED:
		
		Director::getInstance()->replaceScene(
			TransitionSlideInT::create(0.5f,WelcomeScene::createScene()));
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}

void HelpScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACKSPACE:   //返回键听
		{
			GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
			Director::getInstance()->replaceScene(
				TransitionSlideInT::create(0.5f,WelcomeScene::createScene()));
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


//---------------------- HelpLayer ------------------------

bool HelpLayer::init(){
	if(!Layer::init()){
		return false;
	}
	//set default page
	_currentPage = 0;
	_pageCount = 4;


	Size winSize = Director::getInstance()->getWinSize();

	//containLayer
	_containLayer = Layer::create();
	_containLayer->setAnchorPoint(Point::ZERO);
	_containLayer->setPosition(Point::ZERO);
	_containLayer->setContentSize(Size(winSize.width * _pageCount  ,winSize.height));

	 char str[30] = {0};
	 for(int i = 1; i <= _pageCount; i++){
		sprintf(str,"help_introduce%d.png",i);
		auto img = Sprite::create(str);
		img->setPosition(winSize.width * (i - 0.5) , winSize.height / 2);
		img->setScale(0.65f);
		_containLayer->addChild(img);
	 }
	
	//scrollview (notice :need to set viewsize )
	_scrollView = cocos2d::extension::ScrollView::create(this->getContentSize());
	_scrollView->setAnchorPoint(Point::ZERO);
	_scrollView->setPosition(Point::ZERO);
	_scrollView->setContainer(_containLayer);
	_scrollView->setTouchEnabled(false);
	_scrollView->setDelegate(this);

	_scrollView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);

	this->addChild(_scrollView);

	//point image
	SpriteFrameCache::getInstance()->addSpriteFrame(SpriteFrame::create(IMG_POINT_N,Rect(0,0,32,32)),IMG_POINT_N);
	SpriteFrameCache::getInstance()->addSpriteFrame(SpriteFrame::create(IMG_POINT_P,Rect(0,0,32,32)),IMG_POINT_P);

	for(int i = 0; i < _pageCount; i++){
		auto sprite = Sprite::createWithSpriteFrameName(IMG_POINT_N);
		sprite->setTag(POINT_TAG + i);
		sprite->setPosition(Point(winSize.width / 2 - 70 + i * 40,60));
		this->addChild(sprite);
	}
	((Sprite*)this->getChildByTag(POINT_TAG))->setDisplayFrame(
		SpriteFrameCache::getInstance()->spriteFrameByName(IMG_POINT_P));
	

	return true;
}

void HelpLayer::onEnter(){
	Layer::onEnter();
	//add touch event
	_listener = EventListenerTouchOneByOne::create();
	_listener->setSwallowTouches(true);
	_listener->onTouchBegan = CC_CALLBACK_2(HelpLayer::onTouchBegan, this);
	_listener->onTouchMoved = CC_CALLBACK_2(HelpLayer::onTouchMoved, this);
	_listener->onTouchEnded = CC_CALLBACK_2(HelpLayer::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void HelpLayer::onExit(){
	Layer::onExit();
	//remove touch event
	Director::getInstance()->getEventDispatcher()->removeEventListener(_listener);
}

bool HelpLayer::onTouchBegan(Touch *touch, Event *event){
	//get the screen coordinate
	//chage to OpenGL coordiante
	_touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());

	CCLOG("onTouchBegan x:%f",_touchPoint.x);
	return true;
}

void HelpLayer::onTouchMoved(Touch *touch, Event *event){

}

void HelpLayer::onTouchEnded(Touch* touch, Event* event){
	Point endPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
	CCLOG(" onTouchEnded x:%f",endPoint.x);

	//adjust the scrollview's position
	adjustScrollView(endPoint.x - _touchPoint.x);
}



void HelpLayer::scrollViewDidScroll(cocos2d::extension::ScrollView* view){

}

void HelpLayer::scrollViewDidZoom(cocos2d::extension::ScrollView* view){

}

void HelpLayer::adjustScrollView(float offset){

	CCLOG("offset :  %f" ,offset);
	CCLOG("curPage :  %d" ,_currentPage);

	GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);

	auto winSize = Director::getInstance()->getWinSize();

	//restore the point iamge's  state to normal
	((Sprite*)this->getChildByTag(POINT_TAG + _currentPage))->setDisplayFrame(
		SpriteFrameCache::getInstance()->spriteFrameByName(IMG_POINT_N));

	if(offset < 0)
		_currentPage ++;
	if(offset > 0)
		_currentPage --;

	if(_currentPage < 0)
		_currentPage = 0 ;
	if(_currentPage >= _pageCount)
		_currentPage = _pageCount - 1;

	CCLOG("curPage after :  %d" ,_currentPage);

	//change the point image's state to selected
	((Sprite*)this->getChildByTag(POINT_TAG + _currentPage))->setDisplayFrame(
		SpriteFrameCache::getInstance()->spriteFrameByName(IMG_POINT_P));

	//set scrollview's content offset
	auto adjustPoint = Point(-winSize.width * _currentPage ,0);
	_scrollView->setContentOffset(adjustPoint,true);
}


//---------------------- HelpEnemyLayer ------------------------

bool HelpEnemyLayer::init(){
	if(!Layer::init()){
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	auto sprite = Sprite::create(IMG_HELP_ENEMY_INTRODUCE);
	sprite->setPosition(winSize.width / 2, winSize.height / 2);
	sprite->setScale(0.65);
	this->addChild(sprite);

	return true;
}



//---------------------- HelpTowerLayer ------------------------

bool HelpTowerLayer::init(){
	if(!Layer::init()){
		return false;
	}
	
	//default page
	_currentPage = 0;
	_pageCount = 15;

	Size winSize = Director::getInstance()->getWinSize();

	//containLayer
	_containLayer = Layer::create();
	_containLayer->setAnchorPoint(Point::ZERO);
	_containLayer->setPosition(Point::ZERO);
	_containLayer->setContentSize(Size(winSize.width * _pageCount  ,winSize.height));

	char str[30] = {0};
	for(int i = 1; i <= _pageCount; i++){
	sprintf(str,"ptintroduce%d.png",i);
	auto img = Sprite::create(str);
	img->setPosition(winSize.width * (i - 0.5) , winSize.height / 2);
	img->setScale(0.65f);
	_containLayer->addChild(img);
	}

	//scrollview (notice :need to set viewsize )
	_scrollView = cocos2d::extension::ScrollView::create(this->getContentSize());
	_scrollView->setAnchorPoint(Point::ZERO);
	_scrollView->setPosition(Point::ZERO);
	_scrollView->setContainer(_containLayer);
	_scrollView->setTouchEnabled(false);
	_scrollView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
	this->addChild(_scrollView);

	//point image
	SpriteFrameCache::getInstance()->addSpriteFrame(SpriteFrame::create(IMG_POINT_N,Rect(0,0,32,32)),IMG_POINT_N);
	SpriteFrameCache::getInstance()->addSpriteFrame(SpriteFrame::create(IMG_POINT_P,Rect(0,0,32,32)),IMG_POINT_P);

	for(int i = 0; i < _pageCount; i++){
	auto sprite = Sprite::createWithSpriteFrameName(IMG_POINT_N);
	sprite->setTag(POINT_TAG + i);
	sprite->setPosition(Point(winSize.width / 2 - 290 + i * 40,60));
	this->addChild(sprite);
	}
	((Sprite*)this->getChildByTag(POINT_TAG))->setDisplayFrame(
	SpriteFrameCache::getInstance()->spriteFrameByName(IMG_POINT_P));


	return true;
}

 void HelpTowerLayer::onEnter(){
	 Layer::onEnter();
	 //add touch event
	 _listener = EventListenerTouchOneByOne::create();
	 _listener->setSwallowTouches(true);
	 _listener->onTouchBegan = CC_CALLBACK_2(HelpTowerLayer::onTouchBegan, this);
	 _listener->onTouchMoved = CC_CALLBACK_2(HelpTowerLayer::onTouchMoved, this);
	 _listener->onTouchEnded = CC_CALLBACK_2(HelpTowerLayer::onTouchEnded, this);
	 auto dispatcher = Director::getInstance()->getEventDispatcher();
	 dispatcher->addEventListenerWithSceneGraphPriority(_listener, this);
}

void HelpTowerLayer::onExit(){
	Layer::onExit();
	//remove touch event
	Director::getInstance()->getEventDispatcher()->removeEventListener(_listener);
}

bool HelpTowerLayer::onTouchBegan(Touch *touch, Event *event){
	//get the screen coordinate
	//change to OpenGL coordiante
	_touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());

	CCLOG("onTouchBegan x:%f",_touchPoint.x);
	return true;
}

void HelpTowerLayer::onTouchMoved(Touch *touch, Event *event){

}

void HelpTowerLayer::onTouchEnded(Touch* touch, Event* event){
	Point endPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
	CCLOG(" onTouchEnded x:%f",endPoint.x);

	//adjust the scrollview's position
	adjustScrollView(endPoint.x - _touchPoint.x);
}

void HelpTowerLayer::adjustScrollView(float offset){

	CCLOG("offset :  %f" ,offset);
	CCLOG("curPage :  %d" ,_currentPage);

	GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);

	auto winSize = Director::getInstance()->getWinSize();

	//restore the point iamge's  state to normal
	((Sprite*)this->getChildByTag(POINT_TAG + _currentPage))->setDisplayFrame(
		SpriteFrameCache::getInstance()->spriteFrameByName(IMG_POINT_N));

	if(offset < 0)
		_currentPage ++;
	if(offset > 0)
		_currentPage --;

	if(_currentPage < 0)
		_currentPage = 0 ;
	if(_currentPage >= _pageCount)
		_currentPage = _pageCount - 1;

	CCLOG("curPage after :  %d" ,_currentPage);

	//change the point image's state to selected
	((Sprite*)this->getChildByTag(POINT_TAG + _currentPage))->setDisplayFrame(
		SpriteFrameCache::getInstance()->spriteFrameByName(IMG_POINT_P));

	//set scrollview's content offset
	auto adjustPoint = Point(-winSize.width * _currentPage ,0);
	_scrollView->setContentOffset(adjustPoint,true);
}