#pragma once
#include "AbstractScene.h"
#include "Player.h"
#include "Stage.h"
#include"bubble.h"
#include <vector>
class GameMain : public AbstractScene
{
public:
	int StageImage = 0;
private:
	std::vector<Stage> stage;
public:
	GameMain();									// �R���X�g���N�^
	~GameMain();								// �f�X�g���N�^

	// �N���X�̃I�u�W�F�N�g
	Player* player;		// �v���C���[�̃N���X
	Bubble* bubble;
	//Stage* stage;		// �X�e�[�W�̃N���X
	virtual AbstractScene* Update() override;	// �`��ȊO�̍X�V�����s
	void Draw() const override;					// �`��Ɋւ��邱�Ƃ�����
	void Game();								// �Q�[���̏���

private:
	int NowScore;					//���݂̃X�R�A
	int HighScore;					//�n�C�X�R�A

	int PlayerLife;					//�c�@

	int Stage;
	int PhaseCount;

	bool PhaseFlg;
};

