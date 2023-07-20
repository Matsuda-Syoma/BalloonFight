#pragma once
#include "BoxCollider.h"
#include "DxLib.h" 
#include "Player.h"

class Fish: public BoxCollider
{
private:

	Player* player;

	bool flg;
	float x, y;					// �v���C���[�̍��W
	float w, h;					// �v���C���[�̑傫��
	static const int WIDTH = 20;
	static const int HEIGHT = 20;
	int image[10];
	int imagecnt;
	float imageX, imageY;
	int WeitTime;

public:

	//�R���X�g���N�^
	Fish(float _x);
	//�f�X�g���N�^
	~Fish();

	void Update();

	void Draw() const;					// �`��Ɋւ��邱�Ƃ�����

	bool GetFlg();

	void LoadImage();
};

