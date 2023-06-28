#include "GameMain.h"
#include"UI.h"

GameMain::GameMain()				// �����ŏ�����
{
	player = new Player;

	PlayerLife = 2;
	NowScore = 0;
	HighScore = 10000;
	
}

GameMain::~GameMain()				// ������delete�Ȃǂ�����
{
}

AbstractScene* GameMain::Update()	// �����ŃQ�[�����C���̍X�V������
{
	Game();
	return this;
}

void GameMain::Draw() const			// �����ŃQ�[�����C���̕`��
{
	player->Draw();

	DrawFormatString(50, 10, 0xFFFFFF, "I-%06d ", NowScore);		//���݂̃X�R�A�`��
	DrawFormatString(270, 10, 0xFFFFFF, "TOP-%06d ", HighScore);	//�n�C�X�R�A�`��

	//���C�t3
	if (PlayerLife == 3) {
		DrawBox(100, 40, 110, 50, 0xff0000, FALSE);
		DrawBox(85, 40, 95, 50, 0xff0000, FALSE);
	}
	//���C�t2
	if (PlayerLife == 2) {
		DrawBox(100, 40, 110, 50, 0xff0000, FALSE);
	}

}


void GameMain::Game()				// �����ŃQ�[���̔���Ȃǂ̏���������
{
	player->Update();
}
