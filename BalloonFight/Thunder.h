#pragma once
#include "BoxCollider.h"
class Thunder : public BoxCollider{
public:
	Thunder();							// �R���X�g���N�^
	~Thunder();							// �f�X�g���N�^
	void Update();				//�`��ȊO�̍X�V�����s
	void Draw() const;			// �`��Ɋւ��邱�Ƃ�����

	void LoadImages();

private:
	int CloudImg[3];
	int ThunderImg[6];
	int ThunBallImg[3];

	int FlashCount;
};
