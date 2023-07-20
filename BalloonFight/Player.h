#pragma once
#include "BoxCollider.h"
#include "Stage.h"
#include "PAD_INPUT.h"
#include <math.h>
class Player : public BoxCollider
{
private:
	bool flg;					// �v���C���[���������邩
	bool landingflg;			// �v���C���[���n�ʂɗ����Ă��邩
	bool groundflg;				// �v���C���[�����n������
	bool missflg;				// �~�X�����Ƃ��̃t���O
	bool misssoundflg;			// �~�X�����Ƃ��̌��ʉ��̃t���O
	bool spawnflg;
	int life;					// �v���C���[�̎c�@
	int balloon;					// �v���C���[�̕��D�̐�
	int HitStage;				// �v���C���[���ǂ��ɓ���������
	float x, y;					// �v���C���[�̍��W
	float w, h;					// �v���C���[�̑傫��
	int speedX;					// �v���C���[�̑��x
	float startX;				// �v���C���[�̏���
	float FlyspeedMax;			// �v���C���[�̋󒆍ő呬�x
	float GroundspeedMax;		// �v���C���[�̒n��ő呬�x
	float inertiaX, inertiaY;	// �v���C���[�̊���
	float imageX, imageY;		// �v���C���[�̉摜�̍��W
	int AnimImg;
	int AnimWork;
	int AnimSelect;
	int AnimUpdateTime;
	int AnimFlg = 0b0000;
	bool imageReverse;
	int images[40];
	int LifeImg;
	int jumpdelay;

	static const int WIDTH = 32;
	static const int HEIGHT = 48;
	static const int DELAY = 9;
	
public:

	Player();							// �R���X�g���N�^
	~Player();							// �f�X�g���N�^
	void Init(int _life);				// ���l�̏�����
	void Update();						// �X�V����
	void Draw()const;					// �`�揈��
	void LoadImages();					// �摜�ǂݍ���
	void DeleteImages();				// �摜�폜
	void Miss(int i);					// �~�X�̊֐�
	void BallonBreak(int i);			// ���D�����炵��0�ȉ���������Flg��؂�
	void AnimUpdate();					// �A�j���[�V�����̍X�V

	int HitEnemy(BoxCollider _enemy);

	bool IsFly(Stage box);				// ���ł��邩�ǂ���
	bool GetFlg();						// �v���C���[�������Ă��邩

	bool GetSpawnFlg();

	void SetSpawnFlg(bool _flg);

	float GetX();
	float GetY();

	float GetBoxSide(BoxCollider box, int i);	// �����Ő��l��Ԃ�(1:��A2:���A3:���A4:�E)
	float inputX();						// �X�e�B�b�N�̓��͒l��Ԃ�

	int GetLife();				// �c�@��Ԃ�
	
};

