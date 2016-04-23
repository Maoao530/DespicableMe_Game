#pragma once

/**
 * @file         GameData.h    
 * @date         2014-5-24
 * @author       shun_fzll
 * @brief   	 游戏数据存储 比如Scene
 * 
 */

#include "cocos2d.h"
#include "WelcomeScene.h"
#include "SettingScene.h"
#include "HelpScene.h"
#include "LoadingScene.h"
#include "ChooseScene.h"
#include "WayPoint.h"
#include "Enemy.h"
#include "Wave.h"
#include <vector>
#include "PlantPoint.h"
#include "Plant.h"
#include "Tower.h"
#include "Bullet.h"


using namespace cocos2d;

class GameData{
public:
	
	static GameData* getInstance();
	static void destroyInstance();
public:

	Scene* _welcomeScene;
	Scene* _settingScene;
	Scene* _helpScene;
	Scene* _loadingScene;
	Scene* _chooseScene;

	bool _music;	//background music
	bool _effect;	//button effect
	int _currentPassLevel;//player had pass level
//	int _musicState;

	Vector<WayPoint*> _pointsVector;
	Vector<Enemy*> _enemysVector;
	Vector<PlantPoint*> _plantPointVector;
	Vector<Plant*> _plantsVector;
	Vector<Bullet*> _bulletVector;
	Vector<Tower*> _towersVector;
	Vector<Bullet*> _bulletToDeleteVector;

	std::vector<std::vector<int>> _wavesVector;
	std::vector<int> _enemyNumVector;

	//game control parameter
	int _currentLevel;
	int _currentMoney;
	int _currentWave;
	int _totalWave;
	int _currentSpeed;
	bool _isPause;

private:
	GameData();
	~GameData();
	static GameData* _pInstance;
	
};