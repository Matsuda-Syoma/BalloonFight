#pragma once
#include"common.h"
#include"AbstractScene.h"
#include"Player.h"
#include<DxLib.h>

class UI{
public:
	UI();							// �R���X�g���N�^
	~UI();							// �f�X�g���N�^
	void Update();				// �`��ȊO�̍X�V�����s
	void Draw() const;			// �`��Ɋւ��邱�Ƃ�����
	void LoadImages();

	void DeleteImages();

private:
	int NowScore;					//���݂̃X�R�A
	int HighScore;					//�n�C�X�R�A

	int PlayerLife;					//�c�@

	int Stage;
	int PhaseCount;

	bool PhaseFlg;

	/*int LifeImg;
	int NumImg[10];
	int IImg;
	int TopImg;
	int GameOImg;
	int PhaseImg;*/
};

