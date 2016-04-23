#pragma once

/**
 * @file         PlantLayer.h    
 * @date         2014-6-12
 * @author       shun_fzll
 * @brief   	 
 * 
 */

#include "cocos2d.h"

using namespace cocos2d;


class PlantLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(PlantLayer);
	void addPlant();
};