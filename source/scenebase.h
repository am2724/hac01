#pragma once	// .h�̐擪�ɋL�q�B#include�ł��̃t�@�C�������x�ǂݍ��݂��Ă��A1�x�����ǂݍ��܂Ȃ�

class SceneBase {
public:
	SceneBase();			// �R���X�g���N�^
	virtual ~SceneBase();	// �f�X�g���N�^

	virtual void	Input();	// ����
	virtual void	Process();	// �v�Z
	virtual void	Draw();		// �`��

protected:
};

