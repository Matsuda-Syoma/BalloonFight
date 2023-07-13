#pragma once
#include "BoxCollider.h"
#include "Stage.h"
#include"Player.h"
#include <math.h>

// ����邱��
// �G�̕\��

class Enemy : public Player
{
private:

	bool Enemy_landingflg;					// �K���n�ʂɗ����Ă��邩
	bool Enemy_groundflg;					// �K�����n������

	bool Enemy_missflg;						// �~�X�����Ƃ��̃t���O
	bool Enemy_animflg;						// �~�X�����Ƃ��̃t���O
	int Enemy_life;							// �K�̎c�@
	int Enemy_ballon;						// �K�̕��D�̐�
	int Enemy_HitStage;						// �K���ǂ��ɓ���������
	float Ex, Ey;					// �K�̍��W
	float Ew, Eh;					// �K�̑傫��
	int Enemy_speedX;						// �K�̑��x
	float Enemy_startX;						// �K�̏���
	float Enemy_FlyspeedMax;				// �K�̋󒆍ő呬�x
	float Enemy_GroundspeedMax;				// �K�̒n��ő呬�x
	float Enemy_inertiaX, Enemy_inertiaY;	// �K�̊���
	float Enemy_imageX, Enemy_imageY;		// �K�̉摜�̍��W
	bool Eimg_Reverse;						// �����Ă����
	int E_images[40];
	int E_AnimImg;

	static const int E_WIDTH = 64;
	static const int E_HEIGHT = 64;

public:
	// �R���X�g���N�^
	Enemy();

	// �f�X�g���N�^
	~Enemy();
		
	void E_Init(int _life);				// ���l�̏�����
	void Update();						// �X�V����
	void Draw()const;					// �`�揈��
	void Enemy_LoadImg();				// �摜�ǂݍ���
	void AnimUpdate();					// �A�j���[�V�����̍X�V
};

