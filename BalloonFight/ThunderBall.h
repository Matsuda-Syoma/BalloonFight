#pragma once
#include "BoxCollider.h"

class ThunderBall : public BoxCollider {
public:
	
	ThunderBall();							// �R���X�g���N�^
	~ThunderBall();							// �f�X�g���N�^
	void Update();				//�`��ȊO�̍X�V�����s
	void Draw() const;			// �`��Ɋւ��邱�Ƃ�����
	void ChangeAngle();
	float GetBoxSide(BoxCollider box, int i);
	int Hit(BoxCollider _stage);
	void LoadImages();

	int BallX, BallY;

private:
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;

	
	int MoveX, MoveY;

	int Speed;				//�{�[�����x
	float BallAngle;		//�{�[���̊p�x

	static const int WIDTH = 32;
	static const int HEIGHT = 32;
};

