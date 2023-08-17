#pragma once
#include "BoxCollider.h"
//#include"ThunderBall.h"


class Thunder : public BoxCollider{
public:
	Thunder(int _Stage);							// �R���X�g���N�^
	~Thunder();							// �f�X�g���N�^
	void Update();				//�`��ȊO�̍X�V�����s
	void Draw() const;			// �`��Ɋւ��邱�Ƃ�����

	void LoadImages();

	int BallAngle(int _i);

	bool ThunderSpawn();
	void RandSpawn();
	int GetRandSpawn();
	int GetRandSpawn2();

	void Respawn();
	void Respawn2();


	

	//bool Re_Thunder();// �ăX�|�[���֐�

	float CloudX_Set, CloudY_Set;		// �l�󂯓n���p
	float CloudX_Set2, CloudY_Set2;		// �l�󂯓n���p
	bool WCloud_flg;
	int Th_rund;			// 1~4�ŕ��������߂�
	int Th_rund2;			// 1~4�ŕ��������߂�
private:
	int Stage;
	float CloudX, CloudY;
	float CloudX2, CloudY2;

	float thunder_x, thunder_y;		// �����摜��]���ɋN���邸����C�����邽�߂̕ϐ�

	int CloudImg[3];
	int ThunderImg[6];
	int ThunBallImg[3];

	int FlashCount;
	int BallCount;
	int cu_Cnt;

	int FlashCount2;
	int BallCount2;
	int cu_Cnt2;
	
	

	int SetTh_rund;			// 1~4�ŕ��������߂�
	int SetTh_rund2;			// 1~4�ŕ��������߂�
	
	int WaitTime;
	int WaitTime2;
	int ThAnimImg;
	
	int Spawn_Cnt;
	int Spawn_Cnt2;
	int Spawn_End;
	float thunderRota;
	float thunderRota2;


	
	bool ThFlg;
	bool ThFlg2;
	bool FlFlg;
	bool FlFlg2;
	bool current_flg;
	bool current_flg2;
	

};
