#pragma once
#include "AbstractScene.h"
#include "Player.h"
class GameMain : public AbstractScene
{

public:
	GameMain();									// �R���X�g���N�^
	~GameMain();								// �f�X�g���N�^

	// �N���X�̃I�u�W�F�N�g
	Player* player;		// �v���C���[�̃N���X

	virtual AbstractScene* Update() override;	// �`��ȊO�̍X�V�����s
	void Draw() const override;					// �`��Ɋւ��邱�Ƃ�����
	void Game();								// �Q�[���̏���

private:
	int NowScore;					//���݂̃X�R�A
	int HighScore;					//�n�C�X�R�A

	int PlayerLife;					//�c�@
	int WaitTime;
};

