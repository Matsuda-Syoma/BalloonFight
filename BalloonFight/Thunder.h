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
	void RandSpawn();
	int GetRandSpawn();

	float CloudX2, CloudY2;
private:
	float CloudX, CloudY;
	

	int CloudImg[3];
	int ThunderImg[6];
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;
	int cu_Cnt;
	int Th_rund;			// 1~4�ŕ��������߂�

	int WaitTime;
	int ThAnimImg;
	

	bool ThFlg;
	bool FlFlg;
	bool current_flg;

};
