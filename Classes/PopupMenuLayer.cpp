#include "PopupMenuLayer.h"

bool PopupMenuLayer::init(){
	if(!LayerColor::init()){
		return false;
	}

	_menu = Menu::create();

	//add layer touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(PopupMenuLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PopupMenuLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PopupMenuLayer::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	setColor(ccc3(0,0,0));  
	setOpacity(128);

	return true;
}

PopupMenuLayer* PopupMenuLayer::create(const char* backgroundImage){
	auto layer = PopupMenuLayer::create();
	layer->_background = Sprite::create(backgroundImage);
	layer->_backgroundSize = layer->_background->getContentSize();
	return layer;
}

bool PopupMenuLayer::onTouchBegan(Touch *touch, Event *event){
	return true;
}
void PopupMenuLayer::onTouchMoved(Touch *touch, Event *event){

}
void PopupMenuLayer::onTouchEnded(Touch* touch, Event* event){

}
bool PopupMenuLayer::addButton(const char* normalImage, const char* selectedImage, const char* title, int tag /* = 0 */){
	
	auto item = MenuItemImage::create(
		normalImage,
		selectedImage,
		CC_CALLBACK_1(PopupMenuLayer::buttonCallBack,this)
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

void PopupMenuLayer::setCallbackFunc(Ref* target, SEL_CallFuncN callfun){
	m_callbackListener = target;
	m_callback = callfun;    
}

void PopupMenuLayer::buttonCallBack(Ref* pSender){
	Node* node = dynamic_cast<Node*>(pSender);
//	CCLog("¡¾====PopupLayer::buttonCallBack====¡¿touch tag: %d", node->getTag());
	if (m_callback && m_callbackListener){
		(m_callbackListener->*m_callback)(node);
	}
	this->removeFromParent();
}

void PopupMenuLayer::onEnter(){
	LayerColor::onEnter();

	auto winSize = Director::getInstance()->getWinSize();

	//background
	_background->setPosition(winSize.width / 2, winSize.height / 2);
	this->addChild(_background);

	//menu
	_menu->setPosition(Point::ZERO);
	this->addChild(_menu);

	//menu  item
	float btnHeight = _backgroundSize.height / (_menu->getChildrenCount() + 1);
	Vector<Node*> vector = _menu->getChildren();
	int i = _menu->getChildrenCount();
	for(Node* pObj : vector){
		Node* node = dynamic_cast<Node*>(pObj);
		node->setPosition(Point(winSize.width / 2,
			winSize.height / 2 - _backgroundSize.height / 2 + btnHeight * i));
		i--;
	}


}

void PopupMenuLayer::onExit(){
	LayerColor::onExit();
}