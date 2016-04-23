#pragma once

/**
 * @file         Bullet.h    
 * @date         2014-6-23
 * @author       shun_fzll
 * @brief   	 �ӵ�
 * 
 */

#include "cocos2d.h"

using namespace cocos2d;

//������Ч���Ѳ�ͬ�����ķ��� 
enum BulletType
{
	BULLET_AOE,			//�����ӵ���aoe�˺�(�ɴ�͸)
	BULLET_SINGLE,		//�����ӵ��ĵ����˺������ɴ�͸��
	CIRCLE_AOE,			//ȦȦ�е����˺�
	LINE_SINGLE,			//��Ե������˺�
	LINE_AOE
};

class Bullet : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(Bullet);
	static Bullet* create(const char* name,float attackValue,int distance,int type,int towerNo);
	void playAnimate(const char* name,int times);
	void playAniamteFinish();
	//���ϵĸ���sprite��״̬�����Ե��ӵ����е�
	void updateSpriteState(float dt);
public:
	Sprite* _sprite;

	float _attackValue;
	int _distance;	
	int _type;		//�ӵ�����
	int _towerNo;	//��Ӧ��������

	bool _playingAnimate;//�Ƿ񲥷Ž���

	Rect _spriteRect;	//ʵʱ����

	char tempName[20] ;
	
};



