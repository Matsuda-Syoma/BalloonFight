#pragma once
#include "BoxCollider.h"
class Bubble : public BoxCollider
{
private:
	float x, y;					// �v���C���[�̍��W
	float w, h;					// �v���C���[�̑傫��
	static const int WIDTH = 20;
	static const int HEIGHT = 20;
public:

	//�R���X�g���N�^
	Bubble();
	//�f�X�g���N�^
	~Bubble();

	void Update();

	void Draw() const;					// �`��Ɋւ��邱�Ƃ�����
};

