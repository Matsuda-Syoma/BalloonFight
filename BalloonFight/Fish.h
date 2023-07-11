#pragma once
#include "BoxCollider.h"
#include "DxLib.h" 
class Fish: public BoxCollider
{
private:
	bool flg;
	float x, y;					// �v���C���[�̍��W
	float w, h;					// �v���C���[�̑傫��
	static const int WIDTH = 20;
	static const int HEIGHT = 20;

public:
	//�R���X�g���N�^
	Fish();
	//�f�X�g���N�^
	~Fish();

	void Update();

	void Draw() const;					// �`��Ɋւ��邱�Ƃ�����

	bool GetFlg();
};

