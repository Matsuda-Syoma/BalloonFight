#include "GameMain.h"

GameMain::GameMain()				// �����ŏ�����
{
	player = new Player;
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
}

void GameMain::Game()				// �����ŃQ�[���̔���Ȃǂ̏���������
{
	player->Update();
}
