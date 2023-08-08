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

	bool flg;

	bool landingflg;				// �n�ʂɗ����Ă��邩
	bool groundflg;					// ���n������
	bool deathflg;					// �~�X�����Ƃ��̃t���O
	bool startflg;
	int balloon;					// ���D�̐�
	int balloondelay;				// 
	int color;						// �F
	int HitStage;					// �ǂ��ɓ���������
	float x, y;						// ���W
	float w, h;						// �傫��
	int speedX;						// ���x
	float startX;					// ����
	float FlyspeedMax;				// �󒆍ő呬�x
	float GroundspeedMax;			// �n��ő呬�x
	float inertiaX, inertiaY;		// ����
	float imageX, imageY;			// �摜�̍��W
	bool imageReverse;				// �����Ă����
	int imagesG[18];
	int imagesR[18];
	int imagesP[18];
	int AnimImg;
	int AnimFlg;
	int AnimWork;
	int AnimSelect;
	int AnimUpdateTime;
	int MoveX;
	int MoveY;
	int RandomMoveX;
	int RandomMoveY;
	int MaxRandomMoveX;
	int MaxRandomMoveY;

	int jumpdelay;

	static const int WIDTH = 32;
	static const int HEIGHT = 48;
	static const int DELAY = 9;

public:

	enum class STATE : int {
		STAY = 0,
		FLY,
		FISH,
		MISS,
	};
	STATE state;

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
	bool GetDeathFlg();
	int GetBalloon();
	int GetState();
	void ChangeInertia(BoxCollider _player, int i);
	int HitEnemy(BoxCollider _enemy);
	void BallonBreak(int i);
	void Death(int i);
	void AnimUpdate();					// �A�j���[�V�����̍X�V
};

