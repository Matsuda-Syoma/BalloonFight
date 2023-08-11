#pragma once
#include "BoxCollider.h"
#include"ThunderBall.h"


class Thunder : public BoxCollider{
public:
	ThunderBall* thunderball;
	Thunder();							// �R���X�g���N�^
	~Thunder();							// �f�X�g���N�^
	void Update();				//�`��ȊO�̍X�V�����s
	void Draw() const;			// �`��Ɋւ��邱�Ƃ�����

	void LoadImages();

	int BallAngle(int _i);

	bool ThunderSpawn();
	float CloudX, CloudY;
private:
	int CloudImg[3];
	int ThunderImg[6];
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;

	int WaitTime;
	int ThAnimImg;
	
	

	bool ThFlg;
	bool FlFlg;
	
};
