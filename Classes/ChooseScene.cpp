#include "ChooseScene.h"
#include "GameData.h"
#include "Resources.h"
#include "GameAudio.h"
#include "PopupLayer.h"
#include "XmlParser.h"
#include "WelcomeScene.h"
#include "MainScene.h"

bool ChooseScene::init(){
	if(!Layer::init()){
		return false;
	}

	//获取当前已经通过的关卡，默认初始化为0
	_currentPassLevel = UserDefault::getInstance()->getIntegerForKey("current_pass_level",-1);
	if(_currentPassLevel == -1){
		UserDefault::getInstance()->setIntegerForKey("current_pass_level",0);
		_currentPassLevel = 0;
	}
	GameData::getInstance()->_currentPassLevel = _currentPassLevel;


	auto winSize = Director::getInstance()->getWinSize();

	//UI
	_chooseUI = GUIReader::getInstance()->widgetFromJsonFile(UI_CHOOSE);
	this->addChild(_chooseUI);

	//button
	char str[10] = {0};
	for(int i = 1; i <= 13; i++ ){
		sprintf(str,"%s%d",BTN_CHOOSE,i);
		Button* btn =  static_cast<Button*> (ui::Helper::seekWidgetByName(_chooseUI,str));
		btn->addTouchEventListener(this,toucheventselector(ChooseScene::btnCallback));
		btn->setTag(i);
		if(i > _currentPassLevel + 1)
			//设置不可点击（小红旗显示）
			btn->setBright(false);
	}
	_btnExit = static_cast<Button*>(ui::Helper::seekWidgetByName(_chooseUI,BTN_CHOOSE_EXIT));
	_btnExit->addTouchEventListener(this,toucheventselector(ChooseScene::btnExitCallback));


	//add the girl's animation
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(IMG_GIRL_PLIST,IMG_GIRL_PNG);
	_girl = Sprite::createWithSpriteFrameName("girl1.png");
	_girl->setPosition(winSize.width - _girl->getContentSize().width / 2, _girl->getContentSize().height/ 2);
	this->addChild(_girl,1);

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.8f / 6.0);
	for(int i =1; i <= 6; i++){
		sprintf(str,"girl%d.png",i);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->spriteFrameByName(str));
	}
	auto animate = Animate::create(animation);
	_animate = Repeat::create(animate,2);
	_animate->retain();

	//背景音乐
	if(GameAuio::getInstance()->_musicType == MAIN_MUSIC)
		{
			//说明当前的背景音乐是主背景音乐，不需改变
		}
		else if(GameAuio::getInstance()->_musicType == GAME_MUSIC)
		{
			//说明当前的背景音乐是游戏音乐，需要停止后播放主背景音乐
			GameAuio::getInstance()->stopBackgroundMusic();
			GameAuio::getInstance()->playBackgroundMusic(AUDIO_MAINBG);
			GameAuio::getInstance()->_musicType = MAIN_MUSIC;
		}
		

	//注册捕捉监听  
	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ChooseScene::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);  

	return true;
}

Scene* ChooseScene::createScene(){

	auto scene = Scene::create();
	auto layer = ChooseScene::create();
	scene->addChild(layer);
	return scene;
}

void ChooseScene::btnCallback(Ref *pSender, TouchEventType type){

	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		{
			GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
			Button* btn = (Button*)pSender;
			int tag = btn->getTag();
//			CCLOG("ChooseScene::btnCallback=====%d",tag);
			break;
		}
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
		{
			
			Button* btn = (Button*)pSender;
			int tag = btn->getTag();
			int selectLevel = tag;

			//if selectLevel > _currentPassLevel + 1 ,lock and pop up a layer
			//_currentPassLevel : x
			//selectLevel:[1,x+1]
			if(selectLevel > _currentPassLevel + 1){

				XMLParser *pXmlParser = XMLParser::parseWithFile("strings.xml");
				String *pTitle = pXmlParser->getString("choose_tip_dialog_title");
				String *pText = pXmlParser->getString("choose_tip_dialog_text");
				String *pBtnYes = pXmlParser->getString("choose_tip_dialog_btn_yes");

				//弹出窗口
				PopupLayer* pl = PopupLayer::create("BackGround.png",Size(400,350));
				pl->setTitle(pTitle->getCString());
				pl->setContentText(pText->getCString(), 20, 60, 250);
				pl->setCallbackFunc(this, callfuncN_selector(ChooseScene::popButtonCallback));
				pl->addButton("pop_button.png", "pop_button.png", pBtnYes->getCString(), 0);
				this->addChild(pl);

				return;
			}
			//start new game
			else
			{
				Director::getInstance()->replaceScene(
					TransitionFade::create(0.5f,MainScene::createScene(selectLevel)));
			}

			break;
		}
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;

	}
}

void ChooseScene::popButtonCallback(Node *pNode){
	GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
	//tag为0的按钮响应事件
	if(pNode->getTag() == 0)
	{
		
	}
}

void ChooseScene::btnExitCallback(Ref *pSender, TouchEventType type){
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		break;
	case TouchEventType::TOUCH_EVENT_MOVED:
		break;
	case TouchEventType::TOUCH_EVENT_ENDED:
	
		Director::getInstance()->replaceScene(
			TransitionFade::create(0.5f,WelcomeScene::createScene()));
		break;
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;

	}
}

bool ChooseScene::onTouchBegan(Touch *touch, Event *event){

	return true;
}
void ChooseScene::onTouchMoved(Touch *touch, Event *event){

}

void ChooseScene::onTouchEnded(Touch* touch, Event* event){
	Point touchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
//	CCLOG("%f===%f",touchPoint.x,touchPoint.y);
	if(_girl->getBoundingBox().containsPoint(touchPoint)){
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		_girl->stopAllActions();
		_girl->runAction(_animate);
	}
}

void ChooseScene::onEnter(){
	Layer::onEnter();
	//add layer touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(ChooseScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(ChooseScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(ChooseScene::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


}
void ChooseScene::onExit(){
	Layer::onExit();

}

ChooseScene::~ChooseScene(){
	CC_SAFE_RELEASE(_animate);
}

void ChooseScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACKSPACE:   //返回键听
		{
			GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
			Director::getInstance()->replaceScene(
				TransitionFade::create(0.5f,WelcomeScene::createScene()));

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
