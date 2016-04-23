#include "TowerUpdate.h"
#include "GameData.h"

bool TowerUpdate::init(){
	if(!Node::init()){
		return false;
	}
	return true;
}

void TowerUpdate::initTowerUpdate(Tower* pTower){

	//update背景
	_updateBG = Sprite::createWithSpriteFrameName("update_bg.png");
	this->addChild(_updateBG,0);
	
	//update图片
	//顶级在最下 灰色不可升级在中 可升级在最上
	_update_nor = Sprite::createWithSpriteFrameName("update_n.png");
	_update_dis = Sprite::createWithSpriteFrameName("update_d.png");
	_dingji = Sprite::createWithSpriteFrameName("dingji.png");
	_update_nor->setPosition(0, + 35 + _update_nor->getContentSize().height / 2 );
	_update_dis->setPosition(0, + 35 + _update_dis->getContentSize().height / 2 );
	_dingji->setPosition(0,+ 35 + _dingji->getContentSize().height / 2 );
	

	//update金币背景
	_updateMoneyBG = Sprite::createWithSpriteFrameName("CoinBg.png");
	_updateMoneyBG->setPosition(Point(0, 35));
	

	//remove图片,并判断remove位置
	_remove = Sprite::createWithSpriteFrameName("repealbtn.png");
	Point removePos ;
	Point updatePos;
	Point towerPos = pTower->getPosition();
	Size winSize = Director::getInstance()->getWinSize();
	if(towerPos.y  < 64 )    //最底
	{              
		if(towerPos.x < 64)  //最底最左
		{			
			removePos = Point(35 +_remove->getContentSize().width / 2 ,10);
		}
		else				//最底最右 或者 最底中间
		{							
			removePos = Point(-35 - _remove->getContentSize().width / 2,10);
		}
	}
	else if(towerPos.y > (512 - 64 * 2))    //最顶，也就是menu下面一行的位置
	{ 
		//remove正常位置
		removePos = Point(0 ,-35 - _remove->getContentSize().height / 2);
		
		if(towerPos.x < 64)                 //最顶最左
		{			
			updatePos = Point(35 +_update_nor->getContentSize().width / 2 ,0);
		}
		else                                //最顶最右 或者 最顶中间
		{							
			updatePos = Point(-35 - _update_nor->getContentSize().width / 2,0);
		}
		_dingji->setPosition(updatePos);
		_update_nor->setPosition(updatePos );
		_update_dis->setPosition(updatePos);
		_updateMoneyBG->setPosition(updatePos.x, updatePos.y - _update_nor->getContentSize().height / 2);

		

	}
	else					//正常位置
	{								
		removePos = Point(0 ,-35 - _remove->getContentSize().height / 2);
	}
	
	
	_remove->setPosition(removePos);
	this->addChild(_remove,1);

	//update
	this->addChild(_update_nor,3);
	this->addChild(_update_dis,2);
	this->addChild(_dingji,1);
	this->addChild(_updateMoneyBG,10);

	//remove金币背景
	_removeMoneyBG = Sprite::createWithSpriteFrameName("CoinBg.png");
	_removeMoneyBG->setPosition(removePos.x, removePos.y - _remove->getContentSize().height / 2  );
	this->addChild(_removeMoneyBG,10);

	//然后是根据塔的等级来判断update和remove金币
	_level = pTower->_towerLevel;
	char str[10] = {0};
	switch (_level)
	{
	case 1:	
		
		//update Label
		_updateMoney = pTower->_money + 60 ;
		sprintf(str,"%d",_updateMoney);
		_updateLabel = LabelTTF::create(str,"",15);
		_updateLabel->setPosition(_updateMoneyBG->getContentSize().width / 2 , 
			_updateMoneyBG->getContentSize().height / 2);
		_updateMoneyBG->addChild(_updateLabel);

		//remove label
		_soldMoney = pTower->_money / 2;
		sprintf(str,"%d",_soldMoney);
		_removeLabel = LabelTTF::create(str,"",15);
		_removeLabel->setPosition(_removeMoneyBG->getContentSize().width / 2 , 
			_removeMoneyBG->getContentSize().height / 2);
		_removeMoneyBG->addChild(_removeLabel);

		//默认可以升级
		_isCanUpdate = true;

		//如果钱少于升级金币则不能升级
		if(GameData::getInstance()->_currentMoney < _updateMoney){
			_isCanUpdate = false;
			_update_nor->setVisible(_isCanUpdate);
		}

		//移除顶级sprite
		this->removeChild(_dingji);


		break;
	case 2:	
		//update Label
		_updateMoney = pTower->_money + 120 ;
		sprintf(str,"%d",_updateMoney);
		_updateLabel = LabelTTF::create(str,"",15);
		_updateLabel->setPosition(_updateMoneyBG->getContentSize().width / 2 , 
			_updateMoneyBG->getContentSize().height / 2);
		_updateMoneyBG->addChild(_updateLabel);
	
		//remove label
		_soldMoney = pTower->_money / 2;
		sprintf(str,"%d",_soldMoney);
		_removeLabel = LabelTTF::create(str,"",15);
		_removeLabel->setPosition(_removeMoneyBG->getContentSize().width / 2 , 
			_removeMoneyBG->getContentSize().height / 2);
		_removeMoneyBG->addChild(_removeLabel);

		//默认可以升级
		_isCanUpdate = true;

		//如果钱少于升级金币则不能升级
		if(GameData::getInstance()->_currentMoney < _updateMoney){
			_isCanUpdate = false;
			_update_nor->setVisible(_isCanUpdate);
		}

		//移除顶级sprite
		this->removeChild(_dingji);

		break;

	case 3:

		//remove label
		_soldMoney = pTower->_money / 2;
		sprintf(str,"%d",_soldMoney);
		_removeLabel = LabelTTF::create(str,"",15);
		_removeLabel->setPosition(_removeMoneyBG->getContentSize().width / 2 , 
			_removeMoneyBG->getContentSize().height / 2);
		_removeMoneyBG->addChild(_removeLabel);

		//不可升级
		_isCanUpdate = false;

		//移除无用的sprite
		this->removeChild(_update_nor);
		this->removeChild(_update_dis);
		this->removeChild(_updateMoneyBG);
		
		break;
	
	}

	//不是顶级
	if(_level != 3)
			this->schedule(schedule_selector(TowerUpdate::TowerUpdateLoagic));
		
}

bool TowerUpdate::isCanUpdate(){
	return _isCanUpdate;
}

void TowerUpdate::TowerUpdateLoagic(float dt){
	//如果金币少于升级所需金币
	if(GameData::getInstance()->_currentMoney < _updateMoney){
		_isCanUpdate = false;
		_update_nor->setVisible(_isCanUpdate);
	}else{
		_isCanUpdate = true;
		_update_nor->setVisible(_isCanUpdate);
	}

}
