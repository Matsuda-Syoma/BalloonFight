#include "GameMain.h"

GameMain::GameMain()				// �����ŏ�����
{
	player = new Player;
	bubble = new Bubble;
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
	bubble->Draw();
}

void GameMain::Game()				// �����ŃQ�[���̔���Ȃǂ̏���������
{
	player->Update();
	bubble->Update();
}
