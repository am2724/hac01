#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "scenebase.h"
#include "GamePad.h"


// ����cpp�ł��g�������O���[�o���ϐ��́A�w�b�_�t�@�C����extern�錾����

// �Q�[�����

void ChangeScene(SceneBase* scene);	// Scene��ύX����

void GameMain();	// gamemain.cpp �Ɏ��̂��L�q


extern int gTime;
extern int gSecond;
extern int gMinute;

extern int gStartTime;

extern GamePad	gPad;			// �Q�[���p�b�h�̏��
