#include "EnemyLayer.h"
#include "Enemy.h"
#include "Resources.h"
#include "AnimationUtil.h"
#include "GameData.h"
#include "Wave.h"
#include "XmlParser.h"
#include "StringUtil.h"
#include "MainScene.h"
#include "GameOverLayer.h"
#include "GameAudio.h"
#include "ChooseScene.h"

EnemyLayer::EnemyLayer(){
	CCLOG("enemylayer()");
//	GameData::getInstance()->_enemysVector.clear();
	_currentEnemyNum = 0;
	_enemyTotalNum = 0;
	_dieWave = 0;
	_scheDuleFlag = true;
}
EnemyLayer::~EnemyLayer(){
	CCLOG("����enemylayer()");
	
}
bool EnemyLayer::init(){
	if(!Layer::init()){
		return false;
	}

	//��ǰ���Ѿ������ĵ���
	_currentEnemyNum = 0 ;
	//�Ѿ����˵Ĳ���
	_dieWave = 0;

	//�������ӹ����Ķ�ʱ��
	_schedule = schedule_selector(EnemyLayer::createEnemys);
	this->schedule(_schedule,1.0f,100,1.5f);
	_scheDuleFlag = true;

	this->scheduleUpdate();
	CCLOG("enemyLayer init finsh");
	return true;
}



void EnemyLayer::update(float dt){

	Vector<Enemy*> vs = GameData::getInstance()->_enemysVector;
	int curwave = GameData::getInstance()->_currentWave;
	//�����ڴ������� �� ����vectorΪ�գ��ſ�ʼ��������
	if(!_scheDuleFlag && GameData::getInstance()->_enemysVector.empty()){

		//��һ��
		_currentEnemyNum = 0;
		GameData::getInstance()->_currentWave ++;

		//����һ��
		if(GameData::getInstance()->_currentWave == GameData::getInstance()->_totalWave){
			GameAuio::getInstance()->palyEffect(AUDIO_FINAL_WAVE);
		}

		//����֮ǰ�Ѿ�������һ�����Ѿ�������û�б�Ҫ�ٴ�����һ����game success
		if (GameData::getInstance()->_currentWave > GameData::getInstance()->_totalWave )
		{
			this->unscheduleUpdate();
			this->unschedule(_schedule);
			this->scheduleOnce(schedule_selector(EnemyLayer::popupGameOverLayer),1.0f);
			return;
		}

		//�޸�mainScene����ǩ
		char waveStr[10] = {0};
		sprintf(waveStr,"%d / %d",
			GameData::getInstance()->_currentWave,GameData::getInstance()->_totalWave);
		((MainScene*)this->getParent())->_waveLabel->setString(waveStr);

		//���¿�����ʱ��
		this->schedule(_schedule,1.0f,100,2.0f);
		_scheDuleFlag = true;
		_dieWave ++;
	}
}

void EnemyLayer::createEnemys(float dt){
	int curwave = GameData::getInstance()->_currentWave;
	addWave(GameData::getInstance()->_currentWave);
	
}

void EnemyLayer::addWave(int currentWave){

	Vector<Enemy*> vs = GameData::getInstance()->_enemysVector;
	int curwave = GameData::getInstance()->_currentWave;
	//enemy����Vector
	GameData::getInstance()->_enemyNumVector = GameData::getInstance()->_wavesVector.at(currentWave -1 );
	auto vc = GameData::getInstance()->_enemyNumVector;
	
	_enemyTotalNum = GameData::getInstance()->_enemyNumVector.size();

	//������������һ�����˳��ֽ���
	if(_currentEnemyNum >= _enemyTotalNum){
		//ֹͣ��ʱ��
		this->unschedule(_schedule);
		_scheDuleFlag = false;
		return;
	}
	//����һ������
	addEnemy(GameData::getInstance()->_enemyNumVector.at(_currentEnemyNum++));
}

void EnemyLayer::addEnemy(int enemyType){

	char str[20] = {0};
	sprintf(str,"EnemyList%d.png",enemyType);

	_enemyStr = str;

	enemyBirth(enemyType);
}

void EnemyLayer::enemyBirth(int type ){
	Enemy* enemy = NULL;
	switch (type)
	{
	case 1:
		enemy = Enemy1::createEnemy();
		break;
	case 2:
		enemy = Enemy2::createEnemy();
		break;
	case 3:
		enemy = Enemy3::createEnemy();
		break;
	case 4:
		enemy = Enemy4::createEnemy();
		break;
	case 5:
		enemy = Enemy5::createEnemy();
		break;
	case 6:
		enemy = Enemy6::createEnemy();
		break;
	case 7:
		enemy = Enemy7::createEnemy();
		break;
	case 8:
		enemy = Enemy8::createEnemy();
		break;
	case 9:
		enemy = Enemy9::createEnemy();
		break;
	case 10:
		enemy = Enemy10::createEnemy();
		break;
	case 11:
		enemy = Enemy11::createEnemy();
		break;
	case 12:
		enemy = Enemy12::createEnemy();
		break;
	case 13:
		enemy = Enemy13::createEnemy();
		break;
	case 14:
		enemy = Enemy14::createEnemy();
		break;
	case 15:
		enemy = Enemy15::createEnemy();
		break;
	default:
		break;
	}
	enemy->createSlider();
	Point curPos = enemy->getCurrentWaypoint()->getPosition();
	enemy->setPosition(curPos);
	
	this->addChild(enemy);

	//add enemy to vector
	GameData::getInstance()->_enemysVector.pushBack(enemy);

	//birth
	auto birth = AnimationUtil::getInstance()->getAnimate("enemybirth");
	
	auto birthDone = CallFunc::create(
		CC_CALLBACK_0(EnemyLayer::enemyMove,this,enemy));

	enemy->_sprite->runAction(Sequence::createWithTwoActions(birth,birthDone));

	//������Ч
	GameAuio::getInstance()->palyEffect(AUDIO_ADDENEMY);
}

void EnemyLayer::enemyMove(Node* node){

	Enemy* enemy  = (Enemy*)node;
	//move to the end
	Point curPos = enemy->getCurrentWaypoint()->getPosition();
	if(enemy->_isSlowDown == true){
		curPos = enemy->getPosition();
	}
	Point nextPos = enemy->getNextWaypoint()->getPosition();
	float distance = fabs (nextPos.x - curPos.x) + fabs(nextPos.y - curPos.y);
	float duration = distance / enemy->_speed;

	auto move = MoveTo::create(duration,nextPos);
	auto moveDone = CallFuncN::create(this,callfuncN_selector(EnemyLayer::followPath));
	auto sequence = Sequence::create(move,moveDone,NULL);
	sequence->setTag(ENEMY_MOVE_ACTION_TAG1);
	enemy->runAction(sequence);

	if(enemy->_isSlowDown == true)
	{
		return;
	}

	//run the animation
	AnimationUtil::getInstance()->initAnimationBySplitIMG(_enemyStr.c_str(),0.7f,7);
	auto animate = AnimationUtil::getInstance()->getAnimate(_enemyStr.c_str());
	RepeatForever* repeatForever = RepeatForever::create(animate);
	enemy->_sprite->runAction(repeatForever);


}


void EnemyLayer::followPath(Node* node){
	Enemy* enemy = (Enemy*)node;
	
	if(enemy->getCurrentWaypoint()->isEnd()){
		
		char str[15] = {0};
		sprintf(str,"enemy%d.mp3",enemy->_enemyNo);
		GameAuio::getInstance()->palyEffect(str);

		enemy->_sprite->stopAllActions();
		enemy->removeChild(enemy->_hpSlider);
		//�Ƴ���_hpSlider��������Ϊ�գ�ֻ������һ֡Ϊ��
		//�������ֶ��ÿտ��Խ���bug
		//enemy�ߵ��յ㣨enemyִ��die�Ƴ�hpSlider�������ӵ�������getHurt��hpSlider��Ϊ�յ��쳣��
		enemy->_hpSlider = NULL;
		if (enemy->isPriorityAttact())
		{
			enemy->removeChild(enemy->_prioritySprite,true);
			enemy->_prioritySprite = NULL;
			enemy->_isPriorityAttact = false;
		}
		auto die = AnimationUtil::getInstance()->getAnimate("enemydie");
		auto dieDone = CallFunc::create(CC_CALLBACK_0(EnemyLayer::removeEnemy,this,enemy,enemy->_sprite));

		auto sprite = enemy->_sprite;
		enemy->_sprite->runAction(Sequence::createWithTwoActions(die,dieDone));
		
		//Hp --
		((MainScene*)this->getParent())->_hp --;
		if(((MainScene*)this->getParent())->_hp < 0)
			return;
		char hpStr[10] = {0};
		sprintf(hpStr,"%d",((MainScene*)this->getParent())->_hp);
		((MainScene*)this->getParent())->_hpLabel->setString(hpStr);
		//game over
		if(((MainScene*)this->getParent())->_hp == 0){
			this->unscheduleUpdate();
			this->unschedule(_schedule);
			this->scheduleOnce(schedule_selector(EnemyLayer::popupGameOverLayer),3.5f);
		}
		
		return;
	}

//	Point curPos = enemy->getCurrentWaypoint()->getPosition();
	Point curPos = enemy->getPosition();
	Point nextPos = enemy->getNextWaypoint()->getPosition();

	float distance = fabs (nextPos.x - curPos.x) + fabs(nextPos.y - curPos.y);
	float duration = distance / enemy->_speed;

	auto move = MoveTo::create(duration,nextPos);
	auto moveDone = CallFuncN::create(this,callfuncN_selector(EnemyLayer::followPath));

	auto sequence = Sequence::create(move,moveDone,NULL);
	sequence->setTag(ENEMY_MOVE_ACTION_TAG2);
	enemy->runAction(sequence);
}

void EnemyLayer::removeEnemy(Node* pEnemy,Node* pSprite){
	Enemy* enemy = (Enemy*)pEnemy;
	Sprite* sprite = (Sprite*)pSprite;
	if(enemy != NULL ){
		sprite->stopAllActions();
		GameData::getInstance()->_enemysVector.eraseObject(enemy);
		this->removeChild(enemy,true);
	}
}

void EnemyLayer::popupGameOverLayer(float dt){

	GameOverLayer* layer = NULL;
	//�ɹ� ��ǰ���������ܲ�����1
	if(GameData::getInstance()->_currentWave > GameData::getInstance()->_totalWave)
	{
		GameAuio::getInstance()->palyEffect(AUDIO_WIN);

		layer = GameOverLayer::create(
			"success.png",
			GameData::getInstance()->_totalWave,
			GameData::getInstance()->_currentLevel);
		layer->setCallbackFunc(this,callfuncN_selector(EnemyLayer::popupGameOverCallback));
		//ѡ���ؿ�
		layer->addButton("select_n.png","select_s.png",NULL,BTN_CHOOSE_LEVEL);
		//��һ��
		layer->addButton("nextlevel_normal.png","nextlevel_select.png",NULL,BTN_NEXT_LEVEL);

		//������ǰ�ؿ� = ��ͨ���ؿ� + 1��˵�����Կ����µ���һ��
		if(GameData::getInstance()->_currentLevel == GameData::getInstance()->_currentPassLevel + 1){
			GameData::getInstance()->_currentLevel ++;
			GameData::getInstance()->_currentPassLevel ++;
			UserDefault::getInstance()->setIntegerForKey(
				"current_pass_level",GameData::getInstance()->_currentPassLevel);
		}
		//���򲻿����µĹؿ�
		else
		{
			GameData::getInstance()->_currentLevel ++;
		}
		
		
	}
	//ʧ�� 
	else
	{
		GameAuio::getInstance()->palyEffect(AUDIO_LOSE);

		layer = GameOverLayer::create(
			"fail.png",
			_dieWave ,
			GameData::getInstance()->_currentLevel);
		layer->setCallbackFunc(this,callfuncN_selector(EnemyLayer::popupGameOverCallback));
		//ѡ���ؿ�
		layer->addButton("select_n.png","select_s.png",NULL,BTN_CHOOSE_LEVEL);
		//����һ��
		layer->addButton("retry_normal.png","retry_select.png",NULL,BTN_CUR_LEVEL);
	}
	
	this->getParent()->addChild(layer,1);
}

void EnemyLayer::popupGameOverCallback(Node* pNode){
	int tag = pNode->getTag();
	CCLog("��=====popupGameOverCallback::popButtonCallback======��button call back. tag: %d",tag);
	GameAuio::getInstance()->palyEffect(AUDIO_BTNSELECT);
	switch (tag)
	{
	case BTN_CHOOSE_LEVEL:	//ѡ���ؿ�
		Director::getInstance()->replaceScene(
			TransitionFade::create(0.5f,ChooseScene::createScene()));
		break;
	case BTN_CUR_LEVEL:		//����һ��
		Director::getInstance()->replaceScene(
			TransitionFade::create(
			1.f,MainScene::createScene(GameData::getInstance()->_currentLevel)));
		break;
	case BTN_NEXT_LEVEL:	//��һ��
		
		//�����Ѿ�ͨ��
		if(GameData::getInstance()->_currentLevel == 14){
			Director::getInstance()->replaceScene(
				TransitionFade::create(0.5f,ChooseScene::createScene()));
			break;
		}

		//��ͨ����������һ��
		Director::getInstance()->replaceScene(
			TransitionFade::create(
			1.f,MainScene::createScene(GameData::getInstance()->_currentLevel)));
			
		break;
	default:
		break;
	}

}





