#include "GameMain.h"

GameMain::GameMain()				// �����ŏ�����
{
	player = new Player;
	stage = new Stage(200, 250, 210, 220);
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
	stage->Draw();
}

void GameMain::Game()				// �����ŃQ�[���̔���Ȃǂ̏���������
{
	player->Update();
}
