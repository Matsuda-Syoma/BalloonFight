#pragma once
#include"common.h"
#include"AbstractScene.h"

class UI{
public:
	UI();							// �R���X�g���N�^
	~UI();							// �f�X�g���N�^
	void Update();	// �`��ȊO�̍X�V�����s
	void Draw() const;			// �`��Ɋւ��邱�Ƃ�����
};

