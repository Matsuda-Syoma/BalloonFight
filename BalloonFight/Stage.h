#pragma once
#include "BoxCollider.h"
class Stage : public BoxCollider
{
public:
	Stage();										// �R���X�g���N�^
	Stage(int _stage, int _i);//�f�[�^�̎w��
	Stage(float _x,float _y,float _w,float _h);		// ���W�ƃT�C�Y�w��
	~Stage();										// �f�X�g���N�^
	void Draw()const;								// �`�揈��
	void LoadImage();								// �摜�ǂݍ���
	float GetSide(int i);							// �����Ő��l��Ԃ�(1:��A2:���A3:���A4:�E)
};