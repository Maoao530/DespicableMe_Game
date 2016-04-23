#include "WelcomeScene.h"
#include "GameData.h"
#include "Resources.h"
#include "SettingScene.h"
#include "GameAudio.h"
#include <vector>
#include "PopupLayer.h"
#include "XmlParser.h"
#include "HelpScene.h"
#include "LoadingScene.h"
#include "ChooseScene.h"
#include "StringUtil.h"


bool WelcomeScene::init(){
	if(!Layer::init()){
		return false;
	}
	CCLOG("init");
	//set search filepaths
	std::vector<std::string> vectorPath;
	for(std::string str : searchPaths){
		vectorPath.push_back(str);
	}
	FileUtils::getInstance()->setSearchResolutionsOrder(vectorPath);

	auto size = Director::getInstance()->getWinSize();

	//mainbg
// 	auto mainbg = Sprite::create(IMG_MAINBG);
// 	mainbg->setAnchorPoint(Point::ZERO);
// 	mainbg->setPosition(Point::ZERO);
// 	this->addChild(mainbg,0);

	//start 
// 	auto start = MenuItemImage::create(
// 		IMG_START_NORMAL,
// 		IMG_START_PRESSED,
// 		CC_CALLBACK_1(WelcomeScene::menuStartCallback,this));
// 	start->setAnchorPoint(Point::ZERO);
// 	start->setPosition(Point());

	//set 
// 	auto set = MenuItemImage::create(
// 		IMG_SET_NORMAL,
// 		IMG_SET_PRESSED,
// 		CC_CALLBACK_1(WelcomeScene::menuSetCallback,this));

	//set 
// 	auto help = MenuItemImage::create(
// 		IMG_HELP_NORMAL,
// 		IMG_HELP_PRESSED,
// 		CC_CALLBACK_1(WelcomeScene::menuSetCallback,this));

	_mainbgUI = GUIReader::getInstance()->widgetFromJsonFile(UI_MAINBG);
	this->addChild(_mainbgUI);

	_startBtn =  static_cast<Button*> (ui::Helper::seekWidgetByName(_mainbgUI,BTN_START));
	_startBtn->addTouchEventListener(this,toucheventselector(WelcomeScene::btnStartCallback));

	_setBtn =  static_cast<Button*> (ui::Helper::seekWidgetByName(_mainbgUI,BTN_SET));
	_setBtn->addTouchEventListener(this,toucheventselector(WelcomeScene::btnSetCallback));

	_helpBtn =  static_cast<Button*> (ui::Helper::seekWidgetByName(_mainbgUI,BTN_HELP));
	_helpBtn->addTouchEventListener(this,toucheventselector(WelcomeScene::btnHelpCallback));

	_exitBtn =  static_cast<Button*> (ui::Helper::seekWidgetByName(_mainbgUI,BTN_EXIT));
	_exitBtn->addTouchEventListener(this,toucheventselector(WelcomeScene::btnExitCallback));

	//music
	GameAuio::getInstance()->preloadMusic();
	GameAuio::getInstance()->playBackgroundMusic(AUDIO_MAINBG);
	GameAuio::getInstance()->_musicType = MAIN_MUSIC;

	
	//×¢²á²¶×½¼àÌý  
	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(WelcomeScene::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);  
	

	return true;
}

void WelcomeScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{

	PopupLayer* pl;

	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACKSPACE:   //·µ»Ø¼üÌý
		{
			GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);

			XMLParser *pXmlParser = XMLParser::parseWithFile("strings.xml");
			String *pTitle = pXmlParser->getString("exit_dialog_title");
			String *pText = pXmlParser->getString("exit_dialog_text");
			String *pBtnYes = pXmlParser->getString("exit_dialog_btn_yes");
			String *pBtnNo = pXmlParser->getString("exit_dialog_text_no");

			//pop up the dialog
			pl = PopupLayer::create("BackGround.png",Size(400,350));
			pl->setTitle(pTitle->getCString());
			pl->setContentText(pText->getCString(), 20, 60, 250);
			pl->setCallbackFunc(this, callfuncN_selector(WelcomeScene::popButtonCallback));
			pl->addButton("pop_button.png", "pop_button.png", pBtnYes->getCString(), 0);
			pl->addButton("pop_button.png", "pop_button.png", pBtnNo->getCString(), 1);
			this->addChild(pl);

			break;
		}
	case EventKeyboard::KeyCode::KEY_MENU:      //²Ëµ¥¼àÌý

		break;
	case::EventKeyboard::KeyCode::KEY_HOME:
		break;
	default:
		break;
	}
}

Scene* WelcomeScene::createScene(){
	if(GameData::getInstance()->_welcomeScene == NULL){
		auto scene = Scene::create();
		auto layer = WelcomeScene::create();
		scene->addChild(layer);

		//save scene
		GameData::getInstance()->_welcomeScene = scene;
		//retaiin
		scene->retain();

		return scene;
	}
	return GameData::getInstance()->_welcomeScene;
}

void WelcomeScene::btnStartCallback(Ref *pSender, TouchEventType type){
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		break;

	case TouchEventType::TOUCH_EVENT_ENDED:
	
		if(GameData::getInstance()->_loadingScene != NULL){
			Director::getInstance()->replaceScene(
				TransitionFade::create(0.5, ChooseScene::createScene()));
		}
		else
		{
			Director::getInstance()->replaceScene(
				TransitionFade::create(0.5, LoadingScene::createScene()));
		}
		break;

	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}

void WelcomeScene::btnSetCallback(Ref *pSender, TouchEventType type){

	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		break;

	case TouchEventType::TOUCH_EVENT_ENDED:
		
		Director::getInstance()->replaceScene(
			TransitionSlideInB::create(0.5, SettingScene::createScene()));
		break;

	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
	
}

void WelcomeScene::btnHelpCallback(Ref *pSender, TouchEventType type){

	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		break;

	case TouchEventType::TOUCH_EVENT_ENDED:

		Director::getInstance()->replaceScene(
			TransitionSlideInB::create(0.5, HelpScene::createScene()));
		break;

	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}

void WelcomeScene::btnExitCallback(Ref *pSender, TouchEventType type){

	PopupLayer* pl;

	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		break;

	case TouchEventType::TOUCH_EVENT_ENDED:
		{
		XMLParser *pXmlParser = XMLParser::parseWithFile("strings.xml");
		String *pTitle = pXmlParser->getString("exit_dialog_title");
		String *pText = pXmlParser->getString("exit_dialog_text");
		String *pBtnYes = pXmlParser->getString("exit_dialog_btn_yes");
		String *pBtnNo = pXmlParser->getString("exit_dialog_text_no");

		//pop up the dialog
		pl = PopupLayer::create("BackGround.png",Size(400,350));
		pl->setTitle(pTitle->getCString());
		pl->setContentText(pText->getCString(), 20, 60, 250);
		pl->setCallbackFunc(this, callfuncN_selector(WelcomeScene::popButtonCallback));
		pl->addButton("pop_button.png", "pop_button.png", pBtnYes->getCString(), 0);
		pl->addButton("pop_button.png", "pop_button.png", pBtnNo->getCString(), 1);
		this->addChild(pl);

		break;
		}
	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}

void WelcomeScene::popButtonCallback(Node *pNode){
	CCLog("¡¾=====WelcomeScene::popButtonCallback======¡¿button call back. tag: %d", pNode->getTag());
	GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
	//exit
	if(pNode->getTag() == 0){
		GameData::destroyInstance();
		Director::getInstance()->end();
	}
}




