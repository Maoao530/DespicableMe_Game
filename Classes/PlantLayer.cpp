#include "PlantLayer.h"
#include "GameData.h"
#include "PlantPoint.h"
#include "Plant.h"
#include "Resources.h"

bool PlantLayer::init(){
	if(!Layer::init()){
		return false;
	}

	//add plant
	addPlant();
	
	return true;
}

void PlantLayer::addPlant(){
	for(PlantPoint* plantPoint : GameData::getInstance()->_plantPointVector )
	{
		Plant* plant = NULL;
		Point pos = plantPoint->getPosition();
		int type = plantPoint->getPlantType();
		switch (type)
		{
		case HONGLAN:
			plant = Honglan::createPlant();
			break;
		case HUA:
			plant = Hua::createPlant();
			break;
		case QUAN:
			plant = Quan::createPlant();
			break;
		case LANJUAN:
			plant = Lanjuan::createPlant();
			break;
		case HONGLV:
			plant = Honglv::createPlant();
			break;
		case LVJUAN:
			plant = Lvjuan::createPlant();
			break;
		case DAMO:
			plant = Damo::createPlant();
			break;
		case FANG:
			plant = Fang::createPlant();
			break;
		case HUANGCI:
			plant = Huangci::createPlant();
			break;
		case HUANGGAN:
			plant = Huanggan::createPlant();
			break;
		case HUIGAN:
			plant = Huigan::createPlant();
			break;
		case XIAOCAO:
			plant = Xiaocao::createPlant();
			break;
		case XIAOMO:
			plant = Xiaomo::createPlant();
			break;
		case ZHUANG:
			plant = Zhuang::createPlant();
			break;
			//jam2
		case YUANXRZ:
			plant = Yuanxrz::createPlant();
			break;
		case GU:
			plant = Gu::createPlant();
			break;
		case BOX:
			plant = Box::createPlant();
			break;
		case SHENSHU:
			plant = Shenshu::createPlant();
			break;
		case QIANSHU:
			plant = Qianshu::createPlant();
		case Z:
			plant = Z::createPlant();
			break;
		case H:
			plant = H::createPlant();
			break;
		case HUAXRZ:
			plant = Huaxrz::createPlant();
			break;
		case XIAOXRZ:
			plant = Xiaoxrz::createPlant();
			break;
		case SHENSHUGAN:
			plant = Shenshugan::createPlant();
			break;
		case JIANCAO:
			plant = Jiancao::createPlant();
			break;
		case QIANSHUGAN:
			plant = Qianshugan::createPlant();
			break;
		default:
			break;
		}
		plant->setPosition(pos);
		plant->createSlider();
		GameData::getInstance()->_plantsVector.pushBack(plant);
		this->addChild(plant);
	}
}