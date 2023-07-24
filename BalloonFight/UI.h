#pragma once
#include"common.h"
#include"AbstractScene.h"
#include"Player.h"
#include<DxLib.h>

class UI{
public:
	UI();							// �R���X�g���N�^
	~UI();							// �f�X�g���N�^
	void Update(int _score, int _stage);	// �`��ȊO�̍X�V�����s
	void Draw() const;			// �`��Ɋւ��邱�Ƃ�����
	void LoadImages();

	void DeleteImages();

	void GameOver();

private:
	int NowScore;					//���݂̃X�R�A
	int HighScore;					//�n�C�X�R�A
	int HighScoreWork;				//�n�C�X�R�A�����p

	int TmpScore;					//�X�R�A
	int PosX;

	int PlayerLife;					//�c�@

	int Stage;
	int PhaseCount;

	bool PhaseFlg;
	bool GameOverFlg;

	int Score[6];
	int HiScore[6];
	int NumImg[10];
	int ScoreImg;
	int HighScoreImg;
	int GameOImg;
	int PhaseImg;
	int SampleImg;
};

