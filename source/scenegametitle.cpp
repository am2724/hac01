#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "scenegametitle.h"
#include "sceneexplanation.h"
#include "scenegamemain.h"
#include "gamepad.h"


SceneGameTitle::SceneGameTitle() {
	_cgBg  = LoadGraph("res/title.png");  // 背景画像
	_cgBg1 = LoadGraph("res/B_explain.png");  // Bでゲーム説明画面へ
	_cgBg2 = LoadGraph("res/A_play.png");	  // Aでゲームプレイ画面へ

	_bgm   = LoadSoundMem("res/title_BGM.mp3");  // タイトル＆説明画面で流れるBGM
	ChangeNextPlayVolumeSoundMem(180, _bgm);
	PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP, TRUE);
}

SceneGameTitle::~SceneGameTitle() {
	DeleteGraph(_cgBg);
	DeleteGraph(_cgBg1);
	DeleteGraph(_cgBg2);

	DeleteSoundMem(_bgm);
}

void SceneGameTitle::Input() {
	// 何もしない
}

void SceneGameTitle::Process() {
	if(gPad._trg & PAD_INPUT_4) {		// Aボタン/Cキーでゲーム説明画面へ
		SceneBase* scene = new SceneExplanation();
		ChangeScene(scene);
	}

	if(gPad._trg & PAD_INPUT_3) {		// Bボタン/Aキーでゲームプレイ画面へ
		SceneBase* scene = new SceneGameMain();
		ChangeScene(scene);
	}

	if(gPad._trg & PAD_INPUT_9)
	{
		kouti = 1;
	}
}

void SceneGameTitle::Draw() {
	DrawGraph(0, 0, _cgBg, FALSE);									// 背景画像
	DrawGraph(30, SCREEN_H - 200, _cgBg1, TRUE);					// Bで説明画面
	DrawGraph(SCREEN_W - 540, SCREEN_H - 200, _cgBg2, TRUE);		// Aでゲームプレイ画面

//	PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP, TRUE);
}
