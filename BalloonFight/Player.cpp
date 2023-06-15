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

	// ��ʊO�ɏo���甽�Α�����o�Ă���
	if (x + WIDTH < 0) {
		x = SCREEN_WIDTH;
	}

	if (x > SCREEN_WIDTH) {
		x = 0 - WIDTH;
	}

	if (y > SCREEN_HEIGHT) {
		y = 90;
	}

	// �X�e�B�b�N���쎞��0����1�̊Ԃ��o��悤�ɂ���------------��Ő����ɂ���
	//speedX = round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100;
	//speedY = round(((float)PAD_INPUT::GetPadThumbLY() / 32767) * 100) / 100;

	// ��������
	if (inertiaY < 350) {
		inertiaY += 0.8;
	}

	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_A)) {
		inertiaY -= 25+(inertiaY / 4);
	}

	y += inertiaY / (FRAMERATE * 1.0f);		// ���̏d��(�t���[���� * ���D�̐�)

	// �v���C���[�̈ړ�����  -----(��)
	x += speedX;

	//�E
	//if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 < 1 && speedX < 5.6f) {

	//	speed += 0.1f;

	//}
	//else if (gPlayer.speed > 0.0f) {
	//	gPlayer.speed -= 0.2f;
	//}

	////��
	//if (gNowKey & PAD_INPUT_LEFT && gPlayer.speed > -5.6f) {
	//	gPlayer.speed -= 0.1f;
	//}
	//else if (gPlayer.speed < 0.0f) {
	//	gPlayer.speed += 0.2f;
	//}
}

void Player::Draw() const
{
	DrawBox(box.left, box.top, box.right, box.bottom, 0xff0000, true);
}

void Player::LoadImages() {
	for (int i = 0; i < 3; i++) {
		images[i] = 0;
	}
}

bool Player::IsFly(BoxCollider box) const{
	if (Player::HitBox(box)) {
		return true;
	}
	return false;
}