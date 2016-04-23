#pragma once

/**
 * @file         WayPoint.h    
 * @date         2014-6-27
 * @author       shun_fzll
 * @brief   	 
 * 
 */

#include "cocos2d.h"

using namespace cocos2d;

class WayPoint:public Node
{
public:
	virtual bool init();
	CREATE_FUNC(WayPoint);
	void setEnd(bool flag);
	bool isEnd();
private:
	bool _isEnd;
};