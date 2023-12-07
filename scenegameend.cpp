#include "scenegameend.h"
#include "DxLib.h"
#include "source/winmain.h"
#include "source/gamemain.h"
#include "source/scenegametitle.h"
#include "source/scenegamemain.h"
#include "source/sceneexplanation.h"


SceneGameend::SceneGameend() 
{
	_cgBg = LoadGraph("res/game_scene.png"); // �w�i�摜
	_cgBg1 = LoadGraph("res/time_plate.png"); // ���ԃv���[�g
	_cgBg2 = LoadGraph("res/P1_plate.png");	  //1P�v���[�g
	_cgBg3 = LoadGraph("res/P2_plate.png");	  //2P�v���[�g 
	_cgBg4 = LoadGraph("res/front_FINISH.png");  // FINISH
	_cgBg5 = LoadGraph("res/front_WIN.png");  // WIN
	_cgBg6 = LoadGraph("res/front_LOSE.png"); // LOSE
	_cgBg7 = LoadGraph("res/front_draw.png"); // DRAW

	// BGM�̓ǂݍ���
	_bgm = LoadSoundMem("res/sento_BGM.mp3");
	PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP, TRUE);
}

SceneGameend::~SceneGameend() {
	// �������Ȃ�
}

void SceneGameend::Input() {
	// �������Ȃ�
}

void SceneGameend::Process() {
	// �������Ȃ�
}

void SceneGameend::Draw() 
{
	//DrawGraph(0, 0, _cgBg5, TRUE);		// WIN�\��
	//DrawGraph(0, 0, _cgBg6, TRUE);		// LOSE�\��
	//DrawGraph(0, 0, _cgBg7, TRUE);		// DRAW�\��
}