#include "GameOverLayer.h"

bool GameOverLayer::init(){
	if(!LayerColor::init()){
		return false;
	}

	_menu = Menu::create();

	//add layer touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameOverLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameOverLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameOverLayer::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	setColor(ccc3(0,0,0));  
	setOpacity(128);

	return true;
}

GameOverLayer* GameOverLayer::create(const char* backgroundImage,int wave,int level){
	auto layer = GameOverLayer::create();
	layer->_background = Sprite::create(backgroundImage);
	layer->_backgroundSize = layer->_background->getContentSize();

	//wave
	char str[15] = {0};
	sprintf(str,"%d  %d",wave / 10, wave % 10);
	layer->_waveLabel = LabelTTF::create(str,"",25);
	layer->_waveLabel->setColor(Color3B(255,0,0));
	//level
	sprintf(str,"%d",level);
	layer->_levelLabel = LabelTTF::create(str,"",25);
	layer->_levelLabel->setColor(Color3B(255,0,0));
	return layer;
}

bool GameOverLayer::onTouchBegan(Touch *touch, Event *event){
	return true;
}
void GameOverLayer::onTouchMoved(Touch *touch, Event *event){

}
void GameOverLayer::onTouchEnded(Touch* touch, Event* event){

}
bool GameOverLayer::addButton(const char* normalImage, const char* selectedImage, const char* title, int tag /* = 0 */){

	auto item = MenuItemImage::create(
		normalImage,
		selectedImage,
		CC_CALLBACK_1(GameOverLayer::buttonCallBack,this)
		);
	item->setTag(tag);

	if(title){
		Size itemSize = item->getContentSize();
		LabelTTF* ttf = LabelTTF::create(title, "", 20);
		ttf->setColor(Color3B(0, 0, 0));
		ttf->setPosition(Point(itemSize.width / 2, itemSize.height / 2));
		item->addChild(ttf);
	}

	_menu->addChild(item);
	return true;

}

void GameOverLayer::setCallbackFunc(Ref* target, SEL_CallFuncN callfun){
	m_callbackListener = target;
	m_callback = callfun;    
}

void GameOverLayer::buttonCallBack(Ref* pSender){
	Node* node = dynamic_cast<Node*>(pSender);
	CCLog("¡¾====GameOverLayer::buttonCallBack====¡¿touch tag: %d", node->getTag());
	if (m_callback && m_callbackListener){
		(m_callbackListener->*m_callback)(node);
	}
	this->removeFromParent();
}

void GameOverLayer::onEnter(){
	LayerColor::onEnter();

	auto winSize = Director::getInstance()->getWinSize();

	//background
	_background->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(_background);

	//menu
	_menu->setPosition(Point::ZERO);
	this->addChild(_menu);

	//menu  item
	float btnWidth = _backgroundSize.width / (_menu->getChildrenCount() + 1);
	Vector<Node*> vector = _menu->getChildren();
	int i = 1;
	for(Node* pObj : vector){
		Node* node = dynamic_cast<Node*>(pObj);
		node->setPosition(Point(winSize.width / 2 - _backgroundSize.width / 2 + i * btnWidth,
			winSize.height / 2 - _backgroundSize.height / 2 + 50 ));
		i++;
	}

	//wave
	_waveLabel->setPosition(winSize.width / 2, winSize.height / 2 + 30);
	this->addChild(_waveLabel);
	//level
	_levelLabel->setPosition(winSize.width / 2, winSize.height / 2 - 20);
	this->addChild(_levelLabel);


}

void GameOverLayer::onExit(){
	LayerColor::onExit();
}