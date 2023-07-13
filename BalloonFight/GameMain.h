#pragma once
#include "AbstractScene.h"
#include "LoadSounds.h"
#include "LoadImages.h"
#include "Player.h"
#include"Enemy.h"
#include "Stage.h"
#include"bubble.h"
#include"UI.h"
#include "ScoreUP.h"
#include <vector>
class GameMain : public AbstractScene
{
public:
	int StageImage = 0;
private:
	std::vector<Stage> stage;
	std::vector<ScoreUP>scoreUP;
	int Score;
	bool Pause;
public:
	GameMain();									// �R���X�g���N�^
	~GameMain();								// �f�X�g���N�^

	// �N���X�̃I�u�W�F�N�g
	Player* player;		// �v���C���[�̃N���X
	Bubble* bubble;
	UI* ui;
	Enemy* enemy;		// �G�̃N���X

	//Stage* stage;		// �X�e�[�W�̃N���X
	virtual AbstractScene* Update() override;	// �`��ȊO�̍X�V�����s
	void Draw() const override;					// �`��Ɋւ��邱�Ƃ�����
	void Game();								// �Q�[���̏���

private:
	int NowScore;
	int HighScore;

	int LifeImg;
};

