#pragma once
#include "BoxCollider.h"
class Stage : public BoxCollider
{
public:
	Stage();										// �R���X�g���N�^
	Stage(float _x,float _y,float _w,float _h);		// ���W�ƃT�C�Y�w��
	~Stage();										// �f�X�g���N�^
	void Draw()const;								// �`�揈��
	float GetTop();
};

