#pragma once
#include "AbstractScene.h"
#include "LoadSounds.h"
#include "LoadImages.h"
#include "Player.h"
#include"Enemy.h"
#include "Stage.h"
#include"bubble.h"
#include"Fish.h"
#include"UI.h"
#include "ScoreUP.h"
#include "Splash.h"
#include <vector>
class GameMain : public AbstractScene
{
public:
	int StageImage = 0;
private:
	std::vector<Stage> stage;
	std::vector<ScoreUP>scoreUP;
	std::vector<Splash>splash;
	std::vector<Enemy>enemy;
	std::vector<Bubble>bubble;

	int Score;
	bool Pause;
	int StageNum;
	bool StageSwitch;
	int StageSwitchTime;
	bool parachuteflg;
	int SpawnDelay;
public:
	GameMain(int _score, int _stage, int _life);// �R���X�g���N�^

	~GameMain();								// �f�X�g���N�^

	// �N���X�̃I�u�W�F�N�g
	Player* player;		// �v���C���[�̃N���X
	UI* ui;
	Fish* fish;
	//Stage* stage;		// �X�e�[�W�̃N���X
	virtual AbstractScene* Update() override;	// �`��ȊO�̍X�V�����s
	void Draw() const override;					// �`��Ɋւ��邱�Ƃ�����
	void Game();								// �Q�[���̏���

private:
	int HighScore;

	int LifeImg;

	int fishflg;		// ����update�����p�t���O
};

