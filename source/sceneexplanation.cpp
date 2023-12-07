#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "scenegametitle.h"
#include "scenegamemain.h"
#include "sceneexplanation.h"
#include "gamepad.h"


SceneExplanation::SceneExplanation() {
	_cgBg  = LoadGraph("res/game_scene.png");		// 背景画像
	_cgBg1 = LoadGraph("res/explain_scene.png");   // 説明画面の板
	_cgBg2 = LoadGraph("res/B_title.png");			// Bでタイトル画面へ

	_bgm = LoadSoundMem("res/title_BGM.mp3");		// タイトル＆説明画面で流れるBGM
	ChangeNextPlayVolumeSoundMem(200, _bgm);
	PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP, TRUE);

}

SceneExplanation::~SceneExplanation() {
	DeleteGraph(_cgBg); 
	DeleteGraph(_cgBg1);
	DeleteGraph(_cgBg2);

	DeleteGraph(_bgm);
}

void SceneExplanation::Input() {
	// 何もしない
}

void SceneExplanation::Process() {
	if (gPad._trg & PAD_INPUT_4) {		//Bボタンでタイトル画面へ
		SceneBase* scene = new SceneGameTitle();
		ChangeScene(scene);
	}
}

void SceneExplanation::Draw() {
	DrawGraph(0, 0, _cgBg, FALSE);								 // 背景画像
	DrawGraph(0, 0, _cgBg1, TRUE);								 // 説明画面の板
	DrawGraph(SCREEN_W - 500, SCREEN_H - 200, _cgBg2, TRUE);	 // Bでタイトル画面へ

}
