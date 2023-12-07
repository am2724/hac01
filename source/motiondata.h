#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�


// �L�����N�^����e�[�u��
struct CHARA_MOTION_ITEM {
	int		frameId;	// �\���������t���[��ID
	int		frameCnt;	// ���t���[���\�����邩
	int		mx, my;		// �\�����A1�t���[��������ړ�����l
};

// �P���[�V����������A���[�V�����A�C�e���������܂ŏ����邩
#define	CHARA_MOTION_ITEM_MAX	64

// ���[�V�����A�C�e���p�R�}���h�BframeId �Ɏw�肵�Ďg���BframeId�Əd�����Ă͂����Ȃ�
// �R�}���h�̓t���[���I�����ɏ�������邽�߁A�ŏ��̃t���[���ɂ͎w��ł��Ȃ��d�l
#define	CHARA_MOTION_COMMAND_LOOP		1	// ���[�V���������[�v����(frameCnt�Ƀ��[�V����index�w��)
#define	CHARA_MOTION_COMMAND_MOTION		2	// �ʂ̃��[�V������(frameCnt�Ƀ��[�V�����ԍ��w��)
#define	CHARA_MOTION_COMMAND_PLAYSE		3	// ���ʉ��Đ�(frameCnt��SE_xxxx)



struct CHARA_MOTION {		//�g��Ȃ������ŃR�����g�A�E�g���Ă���
	//int		mirror_lr;	// ���E���]����Ȃ�1, ���Ȃ��Ȃ�0
	CHARA_MOTION_ITEM	item[CHARA_MOTION_ITEM_MAX];
};

// ���[�V�����ԍ��B0�Ԃ���̒ʂ��ԍ��ł��邱��
//#define	MOTION_R_STAND		0
//#define	MOTION_L_STAND		1
//#define	MOTION_R_RUN		2
//#define	MOTION_L_RUN		3
//#define	MOTION_R_ATTACK		4
//#define	MOTION_L_ATTACK		5
//#define	MOTION_R_DAMAGE		6
//#define	MOTION_L_DAMAGE		7
//#define	MOTION_R_JUMP_UP	8
//#define	MOTION_L_JUMP_UP	9
//#define	MOTION_R_JUMP_DOWN	10
//#define	MOTION_L_JUMP_DOWN	11


// ���[�V�����ԍ��B0�Ԃ���̒ʂ��ԍ��ł��邱��
/*#define	MOTION_STAND		0
  #define	MOTION_ATTACK		1*/


extern struct CHARA_MOTION tblMotion[];
