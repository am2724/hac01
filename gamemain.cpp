#include "DxLib.h"
#include "source/scenebase.h"
#include "source/sceneexplanation.h"
#include "source/scenegamemain.h"
#include "source/scenegametitle.h"
#include "source/gamepad.h"
#include "source/gamemain.h"

//
// �萔�E�\���̒�`
//



//
// �O���[�o���ϐ��錾
//

// �Q�[�����

GamePad	gPad;			// �Q�[���p�b�h�̏��








// �G�̎�ނƃ{�^���̑Ή��\












// Scene�|�C���^
SceneBase* gScene;					// �|�C���^�Ȃ̂�new����܂Ŏ��͖̂���

// Scene�̐؂�ւ��p
SceneBase* gNewScene;				// NULL�ȊO���Z�b�g����Ă�����A�V�[����؂�ւ���

// Scene��ύX����
void ChangeScene(SceneBase* scene) 
{
	gNewScene = scene;		// ���̃V�[�����Z�b�g
}

// �G��̂�ݒ�







// �A�v���̏�����
// �N������1�񂾂����s�����
void AppInit()
{
	

	

	gNewScene = NULL;		// ���̃V�[��������������
	gScene = new SceneGameTitle();		// Scene�̎��̂����
}



// �A�v���̉��
// �I������1�񂾂����s�����
void AppRelease()
{
	delete gScene;				// Scene���폜����
}











//
// �t���[�������B1�t���[����1�񂸂��s�����
//

// �t���[�������F����
void FrameInput()
{
	gPad.Input();

	

	// Scene�̓��͌Ăяo��
	gScene->Input();
}



// �t���[�������F�v�Z
void FrameProcess()
{

	// Scene�̌v�Z�Ăяo��
	gScene->Process();

}











// �t���[�������F�`��
void FrameDraw() {

	ClearDrawScreen();	// ��ʂ�����������

	// Scene�̕`��Ăяo��
	gScene->Draw();
	
	
	
	ScreenFlip();							// ����ʂ̓��e��\��ʂɔ��f������
}

//
void GameMain()
{
	AppInit();	// ������

	// 1�t���[�����[�v��g�� ----------------------------------------------------------
	while (ProcessMessage() == 0)		// �v���O�������I������܂Ń��[�v
	{

		// �V�[����؂�ւ��邩�H
		if (gNewScene != NULL) {
			delete gScene;		// ���̃V�[�����폜����
			gScene = gNewScene;	// �󂯎�����V�[�����|�C���^�Z�b�g
			gNewScene = NULL;	// ���̃V�[��������������
		}

		FrameInput();	// ����
		FrameProcess();	// �v�Z
		FrameDraw();	// �`��
		
	}

	AppRelease();	// ���
}
