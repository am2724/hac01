#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "SceneBase.h"


class SceneGameTitle : public SceneBase {
public:
	SceneGameTitle();			// �R���X�g���N�^
	virtual ~SceneGameTitle();	// �f�X�g���N�^

	void	Input() override;	// ����
	void	Process() override;	// �v�Z
	void	Draw() override;	// �`��

protected:
	int		_cgBg;		// �w�i�摜
	int		_cgBg1;		// B�{�^���Ő�����
	int		_cgBg2;		// A�{�^���Ń^�C�g����
	int		_bgm;
};

