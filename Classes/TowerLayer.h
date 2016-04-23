#pragma once

/**
 * @file         TowerLayer.h    
 * @date         2014-6-13
 * @author       shun_fzll
 * @brief   	 
 * 
 */

#include "cocos2d.h"
#include "Tower.h"

using namespace cocos2d;

const int BUILD_TOWER_SELECT_TAG = 101;
const int BUILD_TOWER_UPDATE_TAG = 151;

enum TouchType
{
	MENU  = -2,	//�����˵�
	ROAD  = -1,	//·
	NONE  = 0,	//�յ�
	TOWER = 1,	//�����������Ƴ�
	ENEMY = 2,	//���ˣ����ȹ���
	PLANT = 3	//ֲ����ȹ���
};
class TowerLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(TowerLayer);
	
	//touch 
	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);

	//�жϷ��صĴ�������
	TouchType getTouchType(Point point);
	//������ѡ��ͼƬ
	void buildTowerSelect(Point point);
	//��update�д����ӵ���ײ
	void update(float dt);

	//����Ҫ��������
	void setUpdateTower(Tower* pTower);
	//����������ͼƬ
	void buildTowerUpdate();

private:
	//�ж��Ƿ����ڴ�����
	bool isBuildingTower;

	//�ж��Ƿ�����������
	bool _isUpdatingTower;
	Tower* _towerUpdate;
};