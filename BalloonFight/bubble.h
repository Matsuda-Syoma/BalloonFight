#pragma once
#include "BoxCollider.h"
#include "DxLib.h"
class Bubble : public BoxCollider
{
private:
	bool flg;
	float x, y;					// �v���C���[�̍��W
	float w, h;					// �v���C���[�̑傫��
	static const int WIDTH = 20;
	static const int HEIGHT = 20;
	float SpeedX;
	float SpeedY;
	float moveX;
	bool moveSwitch;
public:

	//�R���X�g���N�^
	Bubble();
	//�f�X�g���N�^
	~Bubble();

	void Update();

	void Draw() const;					// �`��Ɋւ��邱�Ƃ�����

	bool GetFlg();
};

