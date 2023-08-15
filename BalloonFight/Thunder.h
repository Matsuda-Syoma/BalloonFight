#pragma once
#include "BoxCollider.h"
//#include"ThunderBall.h"


class Thunder : public BoxCollider{
public:
	Thunder();							// �R���X�g���N�^
	~Thunder();							// �f�X�g���N�^
	void Update();				//�`��ȊO�̍X�V�����s
	void Draw() const;			// �`��Ɋւ��邱�Ƃ�����

	void LoadImages();

	int BallAngle(int _i);

	bool ThunderSpawn();
	void RandSpawn();
	int GetRandSpawn();

	//bool Re_Thunder();// �ăX�|�[���֐�

	float CloudX2, CloudY2;
private:
	float CloudX, CloudY;
	float thunder_x, thunder_y;		// �����摜��]���ɋN���邸����C�����邽�߂̕ϐ�

	int CloudImg[3];
	int ThunderImg[6];
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;
	int cu_Cnt;
	int Th_rund;			// 1~4�ŕ��������߂�

	int WaitTime;
	int ThAnimImg;
	
	int Spawn_Cnt;
	float thunderRota;
	bool ThFlg;
	bool FlFlg;
	bool current_flg;

};
