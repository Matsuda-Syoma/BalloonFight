#include "GameMain.h"

GameMain::GameMain()				// �����ŏ�����
{
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
}

void GameMain::Game()				// �����ŃQ�[���̔���Ȃǂ̏���������
{
}
