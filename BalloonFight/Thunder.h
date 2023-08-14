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

private:
	int CloudImg[3];		//�_�̉摜
	int ThunderImg[6];		//��Ȃ̉摜
	int ThunBallImg[3];		//���̋��̉摜

	int FlashCount;			//�_�ł̂������
	int BallCount;			//���̃J�E���g

	int WaitTime;			//�҂�
	int FlWait;				//�_�ł�҂�
	int ThAnimImg;			//��Ȃ��o��
	
	int CloudX, CloudY;		//�_�̍��W
	int ThX, ThY;			//��Ȃ̍��W

	bool ThFlg;				//
	bool FlFlg;

};
