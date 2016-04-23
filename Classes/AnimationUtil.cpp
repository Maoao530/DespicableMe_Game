#include "AnimationUtil.h"

AnimationUtil* AnimationUtil::_pInstance = NULL;

AnimationUtil* AnimationUtil::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new AnimationUtil();
	}
	return _pInstance;
}

void AnimationUtil::destroyInstance(){
	if(_pInstance != NULL){
		delete _pInstance;
		_pInstance = NULL;
	}
}

void AnimationUtil::initAnimationBySplitIMG(const char* filename,float time,int numOfpng){

	if(AnimationCache::getInstance()->getAnimation(filename) != NULL){
		return;
	}
	auto big = Sprite::create(filename);

	float width = big->getContentSize().width / numOfpng;
	float height = big->getContentSize().height;

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(time / numOfpng);

	for(int i = 0; i < numOfpng; i++){
		auto frame = SpriteFrame::create(filename,Rect(i*width,0,width,height));
		animation->addSpriteFrame(frame);
	}
	
	AnimationCache::getInstance()->addAnimation(animation,filename);	
	
	
}



void AnimationUtil::initAnimationBySpriteFrameName(const char* filename,float time,int numOfpng){


	if(AnimationCache::getInstance()->getAnimation(filename) != NULL){
		return;
	}

	char str[20] = {0};

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(time / numOfpng);

	for(int i = 1; i <= numOfpng; i++ ){
		sprintf(str,"%s%d.png",filename,i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animation->addSpriteFrame(frame);
	}
	
	AnimationCache::getInstance()->addAnimation(animation,filename);
	
	
}

Animate* AnimationUtil::getAnimate(const char* filename){

	Animation* animation = AnimationCache::getInstance()->getAnimation(filename);

	Animate* animate = Animate::create(animation);

	return animate;

}

Sprite* AnimationUtil::getSpriteBySplitIMG(const char* filename,int index,int totalNum){

	auto big = Sprite::create(filename);

	Size size = big->getContentSize();

	int width = size.width / totalNum;
	int startX = (index - 1) * width; 

	Sprite* sprite = Sprite::create(filename,Rect(startX,0,width,size.height));
	return sprite;

}

