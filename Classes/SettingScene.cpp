#include "SettingScene.h"
#include "GameData.h"
#include "Resources.h"
#include "GameAudio.h"

bool SettingScene::init(){
	if(!Layer::init()){
		return false;
	}
	
	_setUI = GUIReader::getInstance()->widgetFromJsonFile(UI_SETTING);
	this->addChild(_setUI);

	_effectBtn =  static_cast<Button*> (ui::Helper::seekWidgetByName(_setUI,BTN_SET_EFFECT));
	_effectBtn->addTouchEventListener(this,toucheventselector(SettingScene::btnEffectCallback));

	_closeBtn =  static_cast<Button*> (ui::Helper::seekWidgetByName(_setUI,BTN_SET_CLOSE));
	_closeBtn->addTouchEventListener(this,toucheventselector(SettingScene::btnCloseCallback));

	_musicBtn =  static_cast<Button*> (ui::Helper::seekWidgetByName(_setUI,BTN_SET_BGMUSIC));
	_musicBtn->addTouchEventListener(this,toucheventselector(SettingScene::btnMusicCallback));

	//×¢²á²¶×½¼àÌý  
	auto listenerkeyPad = EventListenerKeyboard::create();  
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(SettingScene::onKeyReleased, this);  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);  

	return true;
}

Scene* SettingScene::createScene(){
	if(GameData::getInstance()->_settingScene == NULL){
		auto scene = Scene::create();

		SettingScene* layer = SettingScene::create();
		scene->addChild(layer);

		//save the scene
		GameData::getInstance()->_settingScene = scene ;

		scene->retain();

		return scene;
	}
	return GameData::getInstance()->_settingScene;
}


void SettingScene::btnCloseCallback(Ref *pSender, TouchEventType type){
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

void SettingScene::btnEffectCallback(Ref *pSender, TouchEventType type){
	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		break;

	case TouchEventType::TOUCH_EVENT_ENDED:

		//button state
		_effectBtn->setBright( !GameAuio::getInstance()->getEffectState() );

		//save
		GameAuio::getInstance()->changeEffectState();
		break;

	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
	
}

void SettingScene::btnMusicCallback(Ref *pSender, TouchEventType type){

	switch (type)
	{
	case TouchEventType::TOUCH_EVENT_BEGAN:
		GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
		break;
		
	case TouchEventType::TOUCH_EVENT_ENDED:

		//button state
		_musicBtn->setBright( !GameAuio::getInstance()->getBackgroundMusicState() );

		//music state
		GameAuio::getInstance()->playOrPauseBackgroundMusic();

		//change state
		GameAuio::getInstance()->changeBackgroundMusicState();
		break;

	case TouchEventType::TOUCH_EVENT_CANCELED:
		break;
	}
}

void SettingScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{

	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_BACKSPACE:   //·µ»Ø¼üÌý
		{
			GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
			Director::getInstance()->replaceScene(
				TransitionSlideInT::create(0.5f,WelcomeScene::createScene()));
			
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