#include "GameMain.h"

GameMain::GameMain()				// �����ŏ�����
{
	player = new Player;
	bubble = new Bubble;
	stage.emplace_back(0,440,160,480);
	stage.emplace_back(480,340,640,480);

	stage.emplace_back(200,320,440,330);

	NowScore = 0;
	HighScore = 10000;

	PlayerLife = 3;

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
	//�X�R�A
	DrawFormatString(20, 10, 0xFFFFFF, "I-%06d", NowScore);
	DrawFormatString(275, 10, 0xFFFFFF, "TOP-%06d", HighScore);

	if (PlayerLife == 3) {
		DrawBox(60, 30, 70, 40, 0xFF0000, TRUE);
		DrawBox(75, 30, 85, 40, 0xFF0000, TRUE);
	}

	if (PlayerLife == 3) {
		DrawBox(75, 30, 85, 40, 0xFF0000, TRUE);
	}



	player->Draw();
	bubble->Draw();
	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}
}

void GameMain::Game()				// �����ŃQ�[���̔���Ȃǂ̏���������
{

	player->Update();
	if (player->IsFlg()) {
		for (size_t i = 0; i < stage.size(); i++) {
			if (player->IsFly(stage.at(i))) {
				break;
			}
		}
	}
	else {
		player->Miss(0);
	}
	bubble->Update();

}
