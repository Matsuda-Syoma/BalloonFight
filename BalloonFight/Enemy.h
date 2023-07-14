#pragma once
#include "BoxCollider.h"
#include "Stage.h"
#include <math.h>
#include "BoxCollider.h"
// ����邱��
// �G�̕\��

class Enemy : public BoxCollider
{
private:

	enum class STATE {
		stay = 0,
		walk,
		fly,
		miss,
	};
	STATE state;

	bool flg;

	bool landingflg;					// �K���n�ʂɗ����Ă��邩
	bool groundflg;					// �K�����n������

	bool missflg;				// �~�X�����Ƃ��̃t���O
	bool animflg;				// �~�X�����Ƃ��̃t���O
	int life;					// �K�̎c�@
	int ballon;					// �K�̕��D�̐�
	int HitStage;				// �K���ǂ��ɓ���������
	float x, y;					// �K�̍��W
	float w, h;					// �K�̑傫��
	int speedX;					// �K�̑��x
	float startX;				// �K�̏���
	float FlyspeedMax;			// �K�̋󒆍ő呬�x
	float GroundspeedMax;		// �K�̒n��ő呬�x
	float inertiaX, inertiaY;	// ����
	float imageX, imageY;		// �K�̉摜�̍��W
	bool imageReverse;						// �����Ă����
	int images[40];
	int AnimImg;

	int jumpdelay;

	static const int WIDTH = 32;
	static const int HEIGHT = 48;
	static const int DELAY = 9;

public:
	// �R���X�g���N�^

	Enemy(float _x, float _y);

	// �f�X�g���N�^
	~Enemy();
		
	void E_Init(int _life);				// ���l�̏�����
	void Update();						// �X�V����
	void Draw()const;					// �`�揈��
	void LoadImages();				// �摜�ǂݍ���
	bool IsFly(Stage box);
	float GetBoxSide(BoxCollider box, int i);
	float GetX();
	float GetY();
	bool GetFlg();
	void SetFlg(bool _flg);
	void ChangeInertia(BoxCollider _player, int i);
	int HitEnemy(BoxCollider _enemy);
	void AnimUpdate();					// �A�j���[�V�����̍X�V
};

