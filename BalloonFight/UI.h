#pragma once
#include "AbstractScene.h"
class UI : public AbstractScene {
public:
	UI();							// �R���X�g���N�^
	~UI();							// �f�X�g���N�^
	AbstractScene* Update() override;	// �`��ȊO�̍X�V�����s
	void Draw() const override;			// �`��Ɋւ��邱�Ƃ�����

private:
	int NowScore;					//���݂̃X�R�A
	int HighScore;						//�n�C�X�R�A
};

