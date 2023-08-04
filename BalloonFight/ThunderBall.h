#pragma once
#include "BoxCollider.h"

class ThunderBall : public BoxCollider {
public:
	
	ThunderBall();							// �R���X�g���N�^
	~ThunderBall();							// �f�X�g���N�^
	void Update();				//�`��ȊO�̍X�V�����s
	void Draw() const;			// �`��Ɋւ��邱�Ƃ�����
	void ChangeAngle();
	void LoadImages();

private:
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;

	int BallX, BallY;
	int MoveX, MoveY;

	int Speed;				//�{�[�����x
	float BallAngle;		//�{�[���̊p�x

};

