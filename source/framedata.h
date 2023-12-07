#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�


// �����蔻��\����
struct CHARA_HITRECT {
	int		type;				// �����蔻��̎��
	int		hx, hy, hw, hh;		// ��_����̔����`
};

// �����蔻����
#define	CHARA_HITRECT_TYPE_NONE		0	//�g��Ȃ������ŃR�����g�A�E�g���Ă���
#define	CHARA_HITRECT_TYPE_ATTACK	1	//�g��Ȃ������ŃR�����g�A�E�g���Ă���
#define	CHARA_HITRECT_TYPE_DAMAGE	2	//�g��Ȃ������ŃR�����g�A�E�g���Ă���

#define	CHARA_HITRECT_NUM	4	// 1�t���[�����ɂ��铖���蔻��̍ő吔	//�g��Ȃ������ŃR�����g�A�E�g���Ă���

// �L�����N�^�t���[���\����
// 1���̃t���[���Ɋւ���ݒ�
struct CHARA_FRAME {
	int		frameId;	// �t���[��ID�B�ŗL�̔ԍ���U��
	int		cgId;		// �g�p�摜�ԍ� cgChara[]
	int		cx, cy;		// �摜�̊�_�B�������w��
	int		w, h;		// �摜�T�C�Y
	CHARA_HITRECT	hit[CHARA_HITRECT_NUM];		// �����蔻���`
};



extern struct CHARA_FRAME tblFrame[];
