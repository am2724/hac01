#include "scenegameend.h"
#include "DxLib.h"
#include "source/winmain.h"
#include "source/gamemain.h"
#include "source/scenegametitle.h"
#include "source/scenegamemain.h"
#include "source/sceneexplanation.h"


SceneGameend::SceneGameend() 
{
	_cgBg = LoadGraph("res/game_scene.png"); // 背景画像
	_cgBg1 = LoadGraph("res/time_plate.png"); // 時間プレート
	_cgBg2 = LoadGraph("res/P1_plate.png");	  //1Pプレート
	_cgBg3 = LoadGraph("res/P2_plate.png");	  //2Pプレート 
	_cgBg4 = LoadGraph("res/front_FINISH.png");  // FINISH
	_cgBg5 = LoadGraph("res/front_WIN.png");  // WIN
	_cgBg6 = LoadGraph("res/front_LOSE.png"); // LOSE
	_cgBg7 = LoadGraph("res/front_draw.png"); // DRAW

	// BGMの読み込み
	_bgm = LoadSoundMem("res/sento_BGM.mp3");
	PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP, TRUE);
}

SceneGameend::~SceneGameend() {
	// 何もしない
}

void SceneGameend::Input() {
	// 何もしない
}

void SceneGameend::Process() {
	// 何もしない
}

void SceneGameend::Draw() 
{
	//DrawGraph(0, 0, _cgBg5, TRUE);		// WIN表示
	//DrawGraph(0, 0, _cgBg6, TRUE);		// LOSE表示
	//DrawGraph(0, 0, _cgBg7, TRUE);		// DRAW表示
}