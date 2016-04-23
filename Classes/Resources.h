#pragma once 

#include <string>

//searchPaths
static const std::string  searchPaths[] = {
	"fonts",

	"music",
	"music/enemy",
	"music/other",

	"images",
	"images/cocostudio",
	"images/loading",
	"images/main",
	"images/help",
	"images/choose",
	"images/enemy",
	"images/plant",
	"images/tower",
	"images/bullet",

	"maps",
	"maps/tmx",
	"maps/tmx-ext",
	"maps/xml",
	
};

// -------------- WelcomeScene   --------------------------

static const char* UI_MAINBG = "dm_mainbg.ExportJson";
static const char* BTN_START = "start";
static const char* BTN_SET = "set";
static const char* BTN_HELP = "help";
static const char* BTN_EXIT = "exit";


// -------------- SettingScene   --------------------------

static const char* UI_SETTING = "setMusic.ExportJson";
static const char* BTN_SET_EFFECT = "btn_effect";
static const char* BTN_SET_BGMUSIC = "btn_bgmusic";
static const char* BTN_SET_CLOSE = "btn_set_close";


// -------------- HelpScene      --------------------------

static const char* IMG_HELPBG = "helpbg.png";
static const char* IMG_MENU_HELP_N = "menuBtnHelp_n.png";
static const char* IMG_MENU_HELP_P = "menuBtnHelp_p.png";
static const char* IMG_MENU_ENEMY_N = "menuBtnEnemy_n.png";
static const char* IMG_MENU_ENEMY_P = "menuBtnEnemy_p.png";
static const char* IMG_MENU_TOWER_N = "menuBtnPower_n.png";
static const char* IMG_MENU_TOWER_P = "menuBtnTower_p.png";
static const char* IMG_BTN_CLOSE = "x.png";
static const char* IMG_POINT_N = "point_n.png";
static const char* IMG_POINT_P = "point_p.png";
static const char* IMG_HELP_ENEMY_INTRODUCE = "enemyintroduce.png";


// -------------- LoadingScene   --------------------------

static const char* IMG_LOADINGBG = "loading_bg.png";
static const char* IMG_LOADING_BAR = "bar.png";
static const char* IMG_LOADING_BAR_BG = "bar_bg.png";
static const char* IMG_LOADING_BAR_TIP = "bar_tip.png";
static const char* IMG_LOADING_BAR_THUMB = "bar_thumb.png";


// -------------- ChooseScene    --------------------------

static const char* IMG_GIRL_PNG = "girl_m.png";
static const char* IMG_GIRL_PLIST = "girl_m.plist";

static const char* IMG_CHOOSE_PNG = "chooses.png";
static const char* IMG_CHOOSE_PLIST = "chooses.plist";

static const char* UI_CHOOSE = "ChooseMap.ExportJson";
static const char* BTN_CHOOSE = "btn";
static const char* BTN_CHOOSE_EXIT = "choose_btnExit";


// -------------- MainScene      --------------------------
static const char* MAP1 = "map1.tmx";
static const char* MAP_BACKGROUND = "bg";
static const char* MAP_ROAD = "road";
static const char* MAP_OBJECT = "object";

static const char* IMG_MENU_BG = "Menu_Bg.png";
static const char* IMG_PAUSE_LABEL = "OnSuspend.png";
static const char* IMG_MENU_PAUSE = "Pause.png";
static const char* IMG_MENU_RESUME = "Resume.png";
static const char* IMG_MENU_SPEED_1 = "Speed1x.png";
static const char* IMG_MENU_SPEED_2 = "Speed2x.png";
static const char* IMG_MENU_MENUBTN = "Menu_Btn_n.png";

static const char* IMG_POP_MENU_BG = "Set_Menu.png";
static const char* IMG_POP_MENU_RESUME_N = "resume_n.png";
static const char* IMG_POP_MENU_RESUME_P = "resume_s.png";
static const char* IMG_POP_MENU_RESTART_N = "restart_n.png";
static const char* IMG_POP_MENU_RESTART_P = "restart_s.png";
static const char* IMG_POP_MENU_SELECT_N = "select_n.png";
static const char* IMG_POP_MENU_SELECT_P = "select_s.png";

static const char* IMG_ENEMY_PNG = "enemy.png";
static const char* IMG_ENEMY_PLIST = "enemy.plist";
static const char* IMG_ENEMY_BD_PNG = "enemy_b_d.png";
static const char* IMG_ENEMY_BD_PLIST = "enemy_b_d.plist";

static const char* IMG_PLANT_PNG = "jam1.png";
static const char* IMG_PLANT_PLIST = "jam1.plist";

static const char* IMG_PLANT2_PNG = "jam2.png";
static const char* IMG_PLANT2_PLIST = "jam2.plist";

static const char* IMG_TOWER_LAYER_PLIST = "TowerLayer.plist";
static const char* IMG_TOWER_LAYER_PNG = "TowerLayer.png";

static const char* IMG_TOWERS_N = "towers_n.png";
static const char* IMG_TOWERS_D = "towers_d.png";

static const char* IMG_TOWERS_DZ_PNG = "dz.png";
static const char* IMG_TOWERS_DZ_PLIST = "dz.plist";

static const char* IMG_TOWERS_PNG = "ta.png";
static const char* IMG_TOWERS_PLIST = "ta.plist";


// -------------- MUSIC ------------------------
static const char* AUDIO_MAINBG = "BGMusic.mp3";
static const char* AUDIO_GAMEBG = "gameBG.mp3";

static const char* AUDIO_BTNSELECT = "btnselect.mp3";
static const char* AUDIO_ADDENEMY = "addenemy.mp3";
static const char* AUDIO_FINAL_WAVE = "finalwave.mp3";
static const char* AUDIO_JAMDIE = "jamdie.mp3";
static const char* AUDIO_LOSE = "lose.mp3";
static const char* AUDIO_WIN = "win.mp3";
static const char* AUDIO_SELECT_FAULT = "selectfault.mp3";
static const char* AUDIO_SHOOT_SELECT = "shootselect.mp3";

static const char* AUDIO_TOWER_SELECT = "turrentselect.mp3";
static const char* AUDIO_TOWER_BUILD = "turrentbuild.mp3";
static const char* AUDIO_TOWER_SELL = "turrentsell.mp3";
static const char* AUDIO_TOWER_UPDATE = "turrentupdate.mp3";




