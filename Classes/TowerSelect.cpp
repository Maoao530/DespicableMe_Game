#include "TowerSelect.h"
#include "AnimationUtil.h"
#include "Resources.h"
#include "GameData.h"

bool TowerSelect::init(){
	if(!Node::init()){
		return false;
	}
	return true;
}

void TowerSelect::initTowerSelect(int index,int money){

	//塔的种类
	_towerType = index;

	//形如Node.addChild(sprite)
	//默认Node节点锚点为坐标原点
	//默认sprite的添加的坐标为Point(0,0)
	//即什么坐标也不设置的话sprite的锚点和Node的锚点重合

	//塔选择图片，灰色在下，正常在上
	_sprite_nor = AnimationUtil::getInstance()->getSpriteBySplitIMG(IMG_TOWERS_N,index,15);
	_sprite_dis = AnimationUtil::getInstance()->getSpriteBySplitIMG(IMG_TOWERS_D,index,15);
	this->addChild(_sprite_dis,0);
	this->addChild(_sprite_nor,1);
	
	//金币bg
	_moneySprite = Sprite::createWithSpriteFrameName("CoinBg.png");
	_moneySprite->setPosition(Point(0, - _sprite_nor->getContentSize().height / 2));
	this->addChild(_moneySprite,10);
	
	//金币label
	_money = money;
	char str[10] = {0};
	sprintf(str,"%d",_money);
	_moneyLabel =  LabelTTF::create(str, "", 15);
	_moneyLabel->setPosition(_moneySprite->getContentSize().width / 2 , _moneySprite->getContentSize().height / 2);
	_moneySprite->addChild(_moneyLabel);


	//塔选择图片，默认可以创建
	_isCanSelect = true;
	
	//如果钱少于创建金币则不能创建
	if(GameData::getInstance()->_currentMoney < _money){
		_isCanSelect = false;
		_sprite_nor->setVisible(_isCanSelect);
	}

	
	this->schedule(schedule_selector(TowerSelect::TowerSelectLoagic));
}

void TowerSelect::TowerSelectLoagic(float dt){
	//如果钱少于创建金币则修改
	if(GameData::getInstance()->_currentMoney < _money){
		_isCanSelect = false;
		_sprite_nor->setVisible(_isCanSelect);
	}
	else{
		_isCanSelect = true;
		_sprite_nor->setVisible(_isCanSelect);
	}
}

bool TowerSelect::isCanSelect(){
	return _isCanSelect;
}

// ============================ 创建工厂 =================================

TowerSelect* TowerSelectFactory::createTowerSelct(int type){

	TowerSelect* select = TowerSelect::create();
	switch (type)
	{
	case 1 :
		select->initTowerSelect(1,160);
		break;
	case 2 :
		select->initTowerSelect(2,180);
		break;
	case 3 :
		select->initTowerSelect(3,220);
		break;
	case 4 :
		select->initTowerSelect(4,160);
		break;
	case 5 :
		select->initTowerSelect(5,220);
		break;
	case 6 :
		select->initTowerSelect(6,220);
		break;
	case 7 :
		select->initTowerSelect(7,160);
		break;
	case 8 :
		select->initTowerSelect(8,100);
		break;
	case 9 :
		select->initTowerSelect(9,160);
		break;
	case 10 :
		select->initTowerSelect(10,160);
		break;
	case 11 :
		select->initTowerSelect(11,220);
		break;
	case 12 :
		select->initTowerSelect(12,160);
		break;
	case 13 :
		select->initTowerSelect(13,220);
		break;
	case 14 :
		select->initTowerSelect(14,160);
		break;
	case 15 :
		select->initTowerSelect(15,100);
		break;
	}
	return select;
}
