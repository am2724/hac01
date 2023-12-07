#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "scenegametitle.h"
#include "scenegamemain.h"
#include "sceneexplanation.h"
#include "gamepad.h"


SceneExplanation::SceneExplanation() {
	_cgBg  = LoadGraph("res/game_scene.png");		// �w�i�摜
	_cgBg1 = LoadGraph("res/explain_scene.png");   // ������ʂ̔�
	_cgBg2 = LoadGraph("res/B_title.png");			// B�Ń^�C�g����ʂ�

	_bgm = LoadSoundMem("res/title_BGM.mp3");		// �^�C�g����������ʂŗ����BGM
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
	// �������Ȃ�
}

void SceneExplanation::Process() {
	if (gPad._trg & PAD_INPUT_4) {		//B�{�^���Ń^�C�g����ʂ�
		SceneBase* scene = new SceneGameTitle();
		ChangeScene(scene);
	}
}

void SceneExplanation::Draw() {
	DrawGraph(0, 0, _cgBg, FALSE);								 // �w�i�摜
	DrawGraph(0, 0, _cgBg1, TRUE);								 // ������ʂ̔�
	DrawGraph(SCREEN_W - 500, SCREEN_H - 200, _cgBg2, TRUE);	 // B�Ń^�C�g����ʂ�

}
