#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�
#include "SceneBase.h"

class SceneExplanation : public SceneBase {
public:
	SceneExplanation();			// �R���X�g���N�^
	virtual ~SceneExplanation();	// �f�X�g���N�^

	void	Input() override;	// ����
	void	Process() override;	// �v�Z
	void	Draw() override;	// �`��

protected:
	int		_cgBg;		// �w�i�摜
	int		_cgBg1;		// �Q�[���������
	int		_cgBg2;		// B�{�^���Ń^�C�g����

	int		_bgm;		// BGM
};

