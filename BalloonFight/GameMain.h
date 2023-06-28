#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "bubble.h"
class GameMain : public AbstractScene
{

public:
	GameMain();									// �R���X�g���N�^
	~GameMain();								// �f�X�g���N�^

	// �N���X�̃I�u�W�F�N�g
	Player* player;		// �v���C���[�̃N���X
	Bubble* bubble;

	virtual AbstractScene* Update() override;	// �`��ȊO�̍X�V�����s
	void Draw() const override;					// �`��Ɋւ��邱�Ƃ�����
	void Game();								// �Q�[���̏���
};

