#include "DxLib.h"
#include "winmain.h"
#include "gamemain.h"
#include "scenegametitle.h"
#include "sceneexplanation.h"
#include "scenegamemain.h"
#include "gamepad.h"


SceneGameTitle::SceneGameTitle() {
	_cgBg  = LoadGraph("res/title.png");  // �w�i�摜
	_cgBg1 = LoadGraph("res/B_explain.png");  // B�ŃQ�[��������ʂ�
	_cgBg2 = LoadGraph("res/A_play.png");	  // A�ŃQ�[���v���C��ʂ�

	_bgm   = LoadSoundMem("res/title_BGM.mp3");  // �^�C�g����������ʂŗ����BGM
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
	// �������Ȃ�
}

void SceneGameTitle::Process() {
	if(gPad._trg & PAD_INPUT_4) {		// A�{�^��/C�L�[�ŃQ�[��������ʂ�
		SceneBase* scene = new SceneExplanation();
		ChangeScene(scene);
	}

	if(gPad._trg & PAD_INPUT_3) {		// B�{�^��/A�L�[�ŃQ�[���v���C��ʂ�
		SceneBase* scene = new SceneGameMain();
		ChangeScene(scene);
	}

	if(gPad._trg & PAD_INPUT_9)
	{
		kouti = 1;
	}
}

void SceneGameTitle::Draw() {
	DrawGraph(0, 0, _cgBg, FALSE);									// �w�i�摜
	DrawGraph(30, SCREEN_H - 200, _cgBg1, TRUE);					// B�Ő������
	DrawGraph(SCREEN_W - 540, SCREEN_H - 200, _cgBg2, TRUE);		// A�ŃQ�[���v���C���

//	PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP, TRUE);
}
