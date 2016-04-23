/*

#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class GameHUD : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(GameHUD);
	virtual void onEnter();

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
	void onTouchEnded(Touch* touch, Event* event);
	

public:

	Sprite* _background;
	Sprite* _selSpriteRange;
	Sprite* _selSprite;

	Vector<Sprite*> _movableSprites;

};

*/