#include "GameMain.h"

GameMain::GameMain()				// �����ŏ�����
{
	player = new Player;
	stage.emplace_back(0,440,160,480);
	stage.emplace_back(480,340,640,480);

	stage.emplace_back(200,320,440,330);
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


}
