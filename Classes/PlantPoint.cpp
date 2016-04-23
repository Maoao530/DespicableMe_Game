#include "PlantPoint.h"

bool PlantPoint::init()
{
	if(!Node::init())
	{
		return false;
	}
	return true;
}

void PlantPoint::setPlantType(int type)
{
	this->_plantType = type;
}

int PlantPoint::getPlantType()
{
	return this->_plantType;
}