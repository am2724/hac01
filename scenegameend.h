#pragma once
#include "source/SceneBase.h"
class SceneGameend : public SceneBase
{
public:
	SceneGameend();			// �R���X�g���N�^
	virtual ~SceneGameend();	// �f�X�g���N�^

	void	Input()override;	// ����
	void	Process()override;	// �v�Z
	void	Draw()override;		// �`��

protected:

	int		_cgBg;		// �w�i�摜
	int		_cgBg1;		// ���ԃv���[�g
	int		_cgBg2;		// 1�v���C���[�v���[�g
	int		_cgBg3;		// 2�v���C���[�v���[�g
	int		_cgBg4;		// FINISH
	int		_cgBg5;		// WIN
	int		_cgBg6;		// LOSE
	int		_cgBg7;		// DRAW

	int		_bgm;		//�@�Q�[���v���C���ɗ����BGM
};
