#pragma once
#include "BoxCollider.h"
class Player : public BoxCollider
{
private:
	bool flg;					// �v���C���[���������邩
	int life;					// �v���C���[�̎c�@
	float x, y;					// �v���C���[�̍��W
	float w, h;					// �v���C���[�̑傫��
	float speedX, speedY;		// �v���C���[�̑��x
	float speedMax;				// �v���C���[�̍ő呬�x
	float inertiaX, inertiaY;	//�v���C���[�̊���
	float imageX, imageY;		// �v���C���[�̉摜�̍��W
	int images[3];

	static const int WIDTH = 20;
	static const int HEIGHT = 20;
public:
	Player();					// �R���X�g���N�^
	~Player();					// �f�X�g���N�^
	void Update();				// �X�V����
	void Draw()const;			// �`�揈��
	void LoadImages();			// �摜�ǂݍ���
	void DeleteImages();		// �摜�폜
	bool IsFly(BoxCollider box) const;			// ���ł��邩�ǂ���
};

