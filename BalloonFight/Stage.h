#pragma once
#include "BoxCollider.h"
class Stage : public BoxCollider
{
private:
	int ImageX, ImageY, Image;
public:
	Stage();										// �R���X�g���N�^
	Stage(float _x,float _y,float _w,float _h, int _image);		// ���W�ƃT�C�Y�w��
	~Stage();										// �f�X�g���N�^
	void Draw()const;								// �`�揈��
	int GetImage();								// �摜�ǂݍ���
	float GetSide(int i);							// �����Ő��l��Ԃ�(1:��A2:���A3:���A4:�E)
};