#include "WayPoint.h"

bool WayPoint::init()
{
	if (!Node::init())
	{
		return false;
	}
	_isEnd = false;
	return true;
}

void WayPoint::setEnd(bool flag){
	this->_isEnd = flag;
}

bool WayPoint::isEnd(){
	return this->_isEnd;
}