#pragma once
#include "BoxCollider.h"

class ThunderBall : public BoxCollider {
public:
	
	ThunderBall(bool p_flg);							// �R���X�g���N�^
	~ThunderBall();							// �f�X�g���N�^
	void Update();				//�`��ȊO�̍X�V�����s
	void Draw() const;			// �`��Ɋւ��邱�Ƃ�����
	void ChangeAngle();
	float GetBoxSide(BoxCollider box, int i);
	int Hit(BoxCollider _stage);
	//int HitPlayer(BoxCollider _player);
	int GetX();
	int GetY();
	void LoadImages();

	void SetXY(float _x,float _y);

	float BallX, BallY;
	bool Hitflg;				// �v���C���[�̃t���O�擾�p�ϐ�
	bool thunder_flg;
private:

	
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;

	//float x, y;						// ���W
	//float w, h;						// �傫��
	//
	int MoveX, MoveY;

	int Speed;				//�{�[�����x
	float BallAngle;		//�{�[���̊p�x

	static const int WIDTH = 32;
	static const int HEIGHT = 32;
};

