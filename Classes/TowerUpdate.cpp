#include "TowerUpdate.h"
#include "GameData.h"

bool TowerUpdate::init(){
	if(!Node::init()){
		return false;
	}
	return true;
}

void TowerUpdate::initTowerUpdate(Tower* pTower){

	//update����
	_updateBG = Sprite::createWithSpriteFrameName("update_bg.png");
	this->addChild(_updateBG,0);
	
	//updateͼƬ
	//���������� ��ɫ������������ ������������
	_update_nor = Sprite::createWithSpriteFrameName("update_n.png");
	_update_dis = Sprite::createWithSpriteFrameName("update_d.png");
	_dingji = Sprite::createWithSpriteFrameName("dingji.png");
	_update_nor->setPosition(0, + 35 + _update_nor->getContentSize().height / 2 );
	_update_dis->setPosition(0, + 35 + _update_dis->getContentSize().height / 2 );
	_dingji->setPosition(0,+ 35 + _dingji->getContentSize().height / 2 );
	

	//update��ұ���
	_updateMoneyBG = Sprite::createWithSpriteFrameName("CoinBg.png");
	_updateMoneyBG->setPosition(Point(0, 35));
	

	//removeͼƬ,���ж�removeλ��
	_remove = Sprite::createWithSpriteFrameName("repealbtn.png");
	Point removePos ;
	Point updatePos;
	Point towerPos = pTower->getPosition();
	Size winSize = Director::getInstance()->getWinSize();
	if(towerPos.y  < 64 )    //���
	{              
		if(towerPos.x < 64)  //�������
		{			
			removePos = Point(35 +_remove->getContentSize().width / 2 ,10);
		}
		else				//������� ���� ����м�
		{							
			removePos = Point(-35 - _remove->getContentSize().width / 2,10);
		}
	}
	else if(towerPos.y > (512 - 64 * 2))    //���Ҳ����menu����һ�е�λ��
	{ 
		//remove����λ��
		removePos = Point(0 ,-35 - _remove->getContentSize().height / 2);
		
		if(towerPos.x < 64)                 //�����
		{			
			updatePos = Point(35 +_update_nor->getContentSize().width / 2 ,0);
		}
		else                                //����� ���� ��м�
		{							
			updatePos = Point(-35 - _update_nor->getContentSize().width / 2,0);
		}
		_dingji->setPosition(updatePos);
		_update_nor->setPosition(updatePos );
		_update_dis->setPosition(updatePos);
		_updateMoneyBG->setPosition(updatePos.x, updatePos.y - _update_nor->getContentSize().height / 2);

		

	}
	else					//����λ��
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

	//remove��ұ���
	_removeMoneyBG = Sprite::createWithSpriteFrameName("CoinBg.png");
	_removeMoneyBG->setPosition(removePos.x, removePos.y - _remove->getContentSize().height / 2  );
	this->addChild(_removeMoneyBG,10);

	//Ȼ���Ǹ������ĵȼ����ж�update��remove���
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

		//Ĭ�Ͽ�������
		_isCanUpdate = true;

		//���Ǯ�������������������
		if(GameData::getInstance()->_currentMoney < _updateMoney){
			_isCanUpdate = false;
			_update_nor->setVisible(_isCanUpdate);
		}

		//�Ƴ�����sprite
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

		//Ĭ�Ͽ�������
		_isCanUpdate = true;

		//���Ǯ�������������������
		if(GameData::getInstance()->_currentMoney < _updateMoney){
			_isCanUpdate = false;
			_update_nor->setVisible(_isCanUpdate);
		}

		//�Ƴ�����sprite
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

		//��������
		_isCanUpdate = false;

		//�Ƴ����õ�sprite
		this->removeChild(_update_nor);
		this->removeChild(_update_dis);
		this->removeChild(_updateMoneyBG);
		
		break;
	
	}

	//���Ƕ���
	if(_level != 3)
			this->schedule(schedule_selector(TowerUpdate::TowerUpdateLoagic));
		
}

bool TowerUpdate::isCanUpdate(){
	return _isCanUpdate;
}

void TowerUpdate::TowerUpdateLoagic(float dt){
	//��������������������
	if(GameData::getInstance()->_currentMoney < _updateMoney){
		_isCanUpdate = false;
		_update_nor->setVisible(_isCanUpdate);
	}else{
		_isCanUpdate = true;
		_update_nor->setVisible(_isCanUpdate);
	}

}
