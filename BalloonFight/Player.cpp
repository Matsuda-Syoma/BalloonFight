#include "common.h"
#include "Player.h"
#include "PAD_INPUT.h"
#include <math.h>

Player::Player()			// �R���X�g���N�^
{
	flg = true;
	life = 3;
	x = 40;
	y = 96;
	w = WIDTH;
	h = HEIGHT;
	inertiaX = 0;
	inertiaY = 0;
	speedX = 0;
	speedY = 0;
	speedMax = 3;
	LoadImages();
}

Player::~Player()			// �f�X�g���N�^
{
}

void Player::Update()		// �v���C���[�̍X�V����
{
	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

	// �v���C���[�̉摜�̒��S���W
	imageX = x + (w / 2);
	imageY = y + (h / 2);

	if (y > SCREEN_HEIGHT) {
		y = 90;
	}

	// �X�e�B�b�N���쎞��0����1�̊Ԃ��o��悤�ɂ���
	speedX = round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100;
	speedY = round(((float)PAD_INPUT::GetPadThumbLY() / 32767) * 100) / 100;

	// ��������
	if (inertiaY < 75) {
		inertiaY += 0.2;
	}
	y += inertiaY / (60 * 2.0f);		// ���̏d��(�t���[���� * ���D�̐�)

	// �v���C���[�̈ړ�����  -----(��)
	x += speedX * speedMax;
}

void Player::Draw() const
{
	DrawCircle(imageX, imageY, 4, 0xffffff);
}

void Player::LoadImages() {
	for (int i = 0; i < 3; i++) {
		images[i] = 0;
	}
}

bool IsFly(BoxCollider boxcollider) {
	if (Player::HitBox()) {
		return true;
	}
	
}