#pragma once

/**
 * @file         TowerSelect.h    
 * @date         2014-6-19
 * @author       shun_fzll
 * @brief   	 ������ʱ���ͼƬ����Towerһһ��Ӧ
 * 

 */

#include "cocos2d.h"

using namespace cocos2d;

class TowerSelect : public Node{
public:
	virtual bool init();
	CREATE_FUNC(TowerSelect);
	//����index��money
	void initTowerSelect(int index,int money);

	//���ڸ����Ƿ���Ե��
	void TowerSelectLoagic(float dt);

	bool isCanSelect();

public:
	int _money;
	Sprite* _sprite_nor; //����������ʾ�ɵ����ͼƬ
	Sprite* _sprite_dis; //���ɵ����ͼƬ
	Sprite* _moneySprite;//moeny bg
	LabelTTF* _moneyLabel;
	//�Ƿ����ѡ��
	bool _isCanSelect;
	int _towerType;
};

class TowerSelectFactory{
public:
	static TowerSelect* createTowerSelct(int type);

};

