#pragma once
#include "AbstractScene.h"
class Title : public AbstractScene {
public:
	Title();							// �R���X�g���N�^
	~Title();							// �f�X�g���N�^
	AbstractScene* Update() override;	// �`��ȊO�̍X�V�����s
	void Draw() const override;			// �`��Ɋւ��邱�Ƃ�����
};