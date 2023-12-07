#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "scenebase.h"
#include "framedata.h"
#include "motiondata.h"


// �A�j���[�V�����p�^�[���p��`
// �z��̔ԍ��͊Ԃ��󂯂ė]�T�������Đݒ肵�Ă��܂�
//#define	PT_PLAYER_STAND		0		//  0�` 20��
//#define	PT_PLAYER_RUN		20		//  20�` 6��
//#define	PT_PLAYER_ATTACK	30		//  30�` 7��
//#define	PT_PLAYER_DAMAGE	40		//  40�` 1��
//#define	PT_PLAYER_JUMP_UP	50		//  50�` 2��
//#define	PT_PLAYER_JUMP_DOWN	60		//  60�` 2��
//#define	_PT_CHARA_ALLNUM_	100		// �S�p�^�[������
// ���L�����N�^�֘A�̉摜�͂��ׂ� _cgChara[] �ɓǂݍ��ނ悤�ɂ���̂ŁA����ID���d�����Ȃ��悤�ɐݒ肷�邱��

// ���ʉ��p��`
// �z��̔ԍ���0�`
#define	SE_HIT		0		// ����
#define	SE_FINISH	1		// �Q�[���I��
#define	SE_RESULT	2		// ���U���g���
#define SE_DAMAGE   3
#define	_SE_ALL_	4		// �SSE��

#define ENEMY_MAX (4)
#define ENEMY_TYPE_MAX (8)
#define PLAYER_MAX (2)
#define PAD_BUTTON_MAX (4)
    





class SceneGameMain : public SceneBase {
public:
	SceneGameMain();			// �R���X�g���N�^
	virtual ~SceneGameMain();	// �f�X�g���N�^

	void	Input() override;	// ����
	void	Process() override;	// �v�Z
	void	Draw() override;	// �`��

protected:
	//void	CharaChangeMotion(int charaIndex, int motion);
	//int		SearchFrame(int frameId);

protected:
	int		_cgBg;		// �w�i�摜
	int		_cgBg1;		// ���ԃv���[�g
	int		_cgBg2;		// 1�v���C���[�v���[�g
	int		_cgBg3;		// 2�v���C���[�v���[�g
	int		_cgBg4;		// FINISH
	int		_cgBg5;		// WIN
	int		_cgBg6;		// LOSE
	int		_cgBg7;		// DRAW

	

	int		_se[_SE_ALL_];	// ���ʉ��Z�b�g
	int		_bgm;		//�@�Q�[���v���C���ɗ����BGM

	int Time;
	int Second;
	int Minute;

	int startTime;

	
	
	
};

extern int kouti;