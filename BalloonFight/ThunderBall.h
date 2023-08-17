#pragma once
#include "BoxCollider.h"

class ThunderBall : public BoxCollider {
public:
	
	ThunderBall(int spown,bool p_flg,float _x,float _y);							// �R���X�g���N�^
	~ThunderBall();							// �f�X�g���N�^
	void Update();				//�`��ȊO�̍X�V�����s
	void Draw() const;			// �`��Ɋւ��邱�Ƃ�����
	void ChangeAngle();
	float GetBoxSide(BoxCollider box, int i);
	int Hit(BoxCollider _stage);
	int HitPlayer(BoxCollider _player);
	void LoadImages();
	void SetplayerHit(bool _hit);
	/*int SetXY(float _x,float _y);*/
	void SetY();
	float BallX, BallY;
	bool Hitflg;				// �v���C���[�̃t���O�擾�p�ϐ�
	bool thunder_flg;
	int spownAngle;

	bool playerhit;
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

