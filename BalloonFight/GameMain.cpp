#include "GameMain.h"

GameMain::GameMain()				// �����ŏ�����
{
	player = new Player;
	stage.emplace_back(200,210,350,220);
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
	//stage->Draw();
	for (size_t i = 0; i < stage.size(); i++) {
		stage.at(i).Draw();
	}
}

void GameMain::Game()				// �����ŃQ�[���̔���Ȃǂ̏���������
{
	player->Update();
	for (size_t i = 0; i < stage.size(); i++) {
		if (player->IsFly(stage.at(i))) {

		}
	}
}
