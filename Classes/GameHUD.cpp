/*

#include "GameHUD.h"
#include "DataModel.h"

bool GameHUD::init(){
	if(!Layer::init()){
		return false;
	}

	_selSprite = NULL;
	auto size = Director::getInstance()->getWinSize();

	//add background 
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGB565);
	_background = Sprite::create("hud.png");
	_background->setScaleX(2.f);
	_background->setAnchorPoint(Point::ZERO);
	this->addChild(_background);
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::DEFAULT);

	//load tower iamge
	for(int i = 0; i <= 4; i++){
		auto sprite = Sprite::create("MachineGunTurret.png");
		float offset = ((float)(i + 1)) / (4 + 1);
		sprite->setPosition(size.width * offset - 30, 35);
		this->addChild(sprite);
		_movableSprites.pushBack(sprite);
	}
	return true;
}

void GameHUD::onEnter(){

	Layer::onEnter();

	//add layer touch event
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameHUD::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameHUD::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameHUD::onTouchEnded, this);

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool GameHUD::onTouchBegan(Touch *touch, Event *event){
	
	Point touchLoaction = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));

	Sprite* newSprite = NULL;

	for(Sprite* sprite : _movableSprites){

		Point pos = sprite->getPosition();
		Size contentSize = sprite->getContentSize();

		Rect pos_rect = Rect(
			pos.x - contentSize.width / 2,
			pos.y - contentSize.height / 2,
			contentSize.width,
			contentSize.height);

		if(pos_rect.containsPoint(touchLoaction))
		{
			_selSpriteRange = Sprite::create("Range.png");
			_selSpriteRange->setScale(4.f);
			this->addChild(_selSpriteRange,-1);
			_selSpriteRange->setPosition(sprite->getPosition());

			
			newSprite = Sprite::createWithTexture(sprite->getTexture()); //sprite;
			newSprite->setPosition(sprite->getPosition());
			_selSprite = newSprite;
			this->addChild(newSprite);
		}
	}
	return true;

}

void GameHUD::onTouchMoved(Touch* touch, Event* event){

	Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));

	Point oldTouchLocation = touch->getPreviousLocationInView();

	oldTouchLocation = Director::getInstance()->convertToGL(oldTouchLocation);
	oldTouchLocation = this->convertToNodeSpace(oldTouchLocation);

	Point translation = ccpSub(touchLocation,oldTouchLocation);

	if(_selSprite != NULL){
		
		Point newPoint = _selSprite->getPosition() + translation;
		_selSprite->setPosition(newPoint);
		_selSpriteRange->setPosition(newPoint);

		Point touchLoactionInGameLayer = DataModel::getInstance()->_gameLayer->convertTouchToNodeSpace(touch);
		
		//不透明度 （0为完全透明）
		if(DataModel::getInstance()->_gameLayer->canBuildOnTilePosition(touchLoactionInGameLayer)){
			_selSprite->setOpacity(200);	
		}
		else
		{
			_selSprite->setOpacity(50);	
		}
	}
}

void GameHUD::onTouchEnded(Touch* touch, Event* event){
	Point touchLocation = this->convertTouchToNodeSpace(touch);
	DataModel* dataModel = DataModel::getInstance();
	if(_selSprite){
		Rect backgroundRect = Rect(_background->getPositionX(),
			_background->getPositionY(),
			_background->getContentSize().width,
			_background->getContentSize().height);
		if(!backgroundRect.containsPoint(touchLocation)   && dataModel->_gameLayer->canBuildOnTilePosition(touchLocation)){
			Point touchLocationInGameLayer = dataModel->_gameLayer->convertTouchToNodeSpace(touch);
			DataModel::getInstance()->_gameLayer->addTower(touchLocationInGameLayer);
		}
		this->removeChild(_selSprite,true);
		_selSprite = NULL;
		this->removeChild(_selSpriteRange,true);
		_selSpriteRange = NULL;
	}
}
*/