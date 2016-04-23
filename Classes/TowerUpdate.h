#pragma once

/**
 * @file         TowerUpdate.h    
 * @date         2014-6-22
 * @author       shun_fzll
 * @brief   	 ������ͼƬ
 * 
 */

#include "cocos2d.h"
#include "Tower.h"

using namespace cocos2d;

class TowerUpdate : public Node{
public:
	virtual bool init();
	CREATE_FUNC(TowerUpdate);
	void initTowerUpdate(Tower* pTower);
	//���ڸ����Ƿ���Ե��
	void TowerUpdateLoagic(float dt);
	//�Ƿ�ɸ�����
	bool isCanUpdate();
public:
	Sprite* _updateBG;

	//update
	Sprite* _update_nor;
	Sprite* _update_dis;
	Sprite* _dingji;
	Sprite* _updateMoneyBG;
	LabelTTF* _updateLabel;
	int _updateMoney;
	bool _isCanUpdate;	//�Ƿ��������

	//remove
	Sprite* _remove;
	Sprite* _removeMoneyBG;
	LabelTTF* _removeLabel;
	int _soldMoney;

	int _level;			//���ȼ�

};