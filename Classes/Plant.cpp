#include "Plant.h"
#include "AnimationUtil.h"
#include "GameData.h"
#include "GameAudio.h"
#include "Resources.h"

bool Plant::init()
{
	if( !Node::init())
	{
		return false;
	}
	_isPriorityAttact = false;
	_prioritySprite = NULL;
	_isAnimatePlaying = false;
	return true;
}

void Plant::createSlider()
{
	_hpSlider = ControlSlider::create("EnemyHPBg.png","EnemyHP.png","EnemyHpthumb.png");
	_hpSlider->setPosition(
		_sprite->getPositionX() + _sprite->getContentSize().width / 2,
		_sprite->getPositionY() + _sprite->getContentSize().height  + 10);
	_hpSlider->setTouchEnabled(false);
	_hpSlider->setMinimumValue(0);
	_hpSlider->setMaximumValue(_hp);
	_hpSlider->setValue(_hp );
	_hpSlider->setVisible(false);
	addChild(_hpSlider);
}

void Plant::sliderShow()
{
	if(_hpSlider )
	{
		_hpSlider->setVisible(true);
	}
}

void Plant::createPriorityPoint()
{
	//图片
	_prioritySprite = Sprite::createWithSpriteFrameName("point01.png");
	_prioritySprite->setPosition(
		_sprite->getContentSize().width / 2,
		_sprite->getContentSize().height + 25);
	this->addChild(_prioritySprite);

	//动画
	auto animate = AnimationUtil::getInstance()->getAnimate("point0");
	auto repete = RepeatForever::create(animate);
	_prioritySprite->runAction(repete);

	_isPriorityAttact = true;
}

bool Plant::isPriorityAttact()
{
	return _isPriorityAttact;
}

void Plant::getHurt(float hp)
{
	_hp = _hp - hp;
	if(_hp <= 0)
	{
		_hp = 0;
	}
	_hpSlider->setValue(_hp);
}

float Plant::getLife()
{
	return _hp;
}

void Plant::die()
{
	_hp = -1;
	_hpSlider->setValue(0);
	if(this->isPriorityAttact())
	{
		this->removeChild(this->_prioritySprite);
		this->_prioritySprite = NULL;
		this->_isPriorityAttact = false;
	}
	this->removeChild(_hpSlider);
	this->stopActionByTag(101);//在enemyLayer中定义
	this->_sprite->stopAllActions();
	auto die = AnimationUtil::getInstance()->getAnimate("enemydie");
	auto dieDone = CallFunc::create(CC_CALLBACK_0(Plant::removePlant,this,this,_sprite));
	_sprite->runAction(Sequence::createWithTwoActions(die,dieDone));

	//播放死亡effect
	GameAuio::getInstance()->palyEffect(AUDIO_JAMDIE);
}

void Plant::removePlant(Node* pPlant,Node* pSprite)
{
	Plant* plant = (Plant*)pPlant;
	Sprite* sprite = (Sprite*)pSprite;
	if(plant != NULL ){
		sprite->stopAllActions();
		this->removeChild(sprite);
		this->removeAllChildrenWithCleanup(true);
		GameData::getInstance()->_plantsVector.eraseObject(this);
		this->getParent()->removeChild(this,true);
	}
}

void Plant::playAnimate(const char* name)
{
	if(_isAnimatePlaying)
	{
		return;
	}

	_animate = AnimationUtil::getInstance()->getSpriteBySplitIMG(name,1,6);
	_animate->setPosition(_sprite->getContentSize().width / 2,_sprite->getContentSize().height / 2);
	this->addChild(_animate,10);

	auto animate = AnimationUtil::getInstance()->getAnimate(name);
	auto animateDone = CallFunc::create(CC_CALLBACK_0(Plant::playAnimateFinish,this));

	_isAnimatePlaying = true;

	_animate->runAction(Sequence::create(animate,animateDone,NULL));
}

void Plant::playAnimateFinish()
{
	if(_isAnimatePlaying && _animate){
		this->removeChild(_animate,true);
		_animate = NULL;
		_isAnimatePlaying = false;
	}
}

//================================================

Plant* Honglan::createPlant()
{

	Plant* plant = Plant::create();

	plant->_sprite = Sprite::createWithSpriteFrameName("honglan.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 150;
	plant->_money = 300;

	return plant;
}

Plant* Quan::createPlant()
{

	Plant* plant = Plant::create();

	plant->_sprite = Sprite::createWithSpriteFrameName("quan.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 200;
	plant->_money = 400;

	return plant;
}

Plant* Hua::createPlant()
{

	Plant* plant = Plant::create();

	plant->_sprite = Sprite::createWithSpriteFrameName("hua.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 100;
	plant->_money = 200;

	return plant;
}

Plant* Lanjuan::createPlant()
{
	Plant* plant = Plant::create();

	plant->_sprite = Sprite::createWithSpriteFrameName("lanjuan.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 160;
	plant->_money = 320;

	return plant;
}

Plant* Honglv::createPlant()
{

	Plant* plant = Plant::create();

	plant->_sprite = Sprite::createWithSpriteFrameName("honglv.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 130;
	plant->_money = 260;

	return plant;
}

Plant* Lvjuan::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("lvjuan.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Damo::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("damo.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Fang::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("fang.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Huangci::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("huangci.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Huanggan::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("huanggan.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Huigan::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("huigan.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Xiaocao::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("xiaocao.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Xiaomo::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("xiaomo.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Zhuang::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("zhuang.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Yuanxrz::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("yuanxrz.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Gu::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("gu.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Box::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("box.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Shenshu::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("shenshu.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Qianshu::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("qianshu.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Z::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("z.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* H::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("h.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Huaxrz::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("huaxrz.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Xiaoxrz::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("xiaoxrz.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Shenshugan::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("shenshugan.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Jiancao::createPlant()
{
	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("jiancao.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}

Plant* Qianshugan::createPlant()
{

	Plant* plant = Plant::create();
	plant->_sprite = Sprite::createWithSpriteFrameName("qianshugan.png");
	plant->_sprite->setAnchorPoint(Point::ZERO);
	plant->addChild(plant->_sprite);
	plant->_hp = 170;
	plant->_money = 340;

	return plant;
}
