#pragma once

/**
 * @file         PlantPoint.h    
 * @date         2014-6-12
 * @author       shun_fzll
 * @brief   	 
 * 
 */

#include "cocos2d.h"

using namespace cocos2d;

enum PlantTAG
{
	//jam1
	HONGLAN ,	//
	HUA,		//
	QUAN,		//
	DAMO,
	FANG,
	HONGLV,		//
	HUANGCI,
	HUANGGAN,
	HUIGAN,
	LANJUAN,	//
	LVJUAN,		//
	XIAOCAO,
	XIAOMO,
	ZHUANG,

	//jam2
	YUANXRZ,
	GU,
	BOX,
	SHENSHU,
	QIANSHU,

	Z,
	H,
	HUAXRZ,
	XIAOXRZ,

	SHENSHUGAN,
	JIANCAO,
	QIANSHUGAN

};

class PlantPoint : public Node
{
public:
	virtual bool init();
	CREATE_FUNC(PlantPoint);
	void setPlantType(int type);
	int getPlantType();
private:
	int _plantType;
};