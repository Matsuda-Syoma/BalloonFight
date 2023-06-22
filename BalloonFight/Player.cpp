#include "common.h"
#include "Player.h"
#include "PAD_INPUT.h"
#include <math.h>

Player::Player()			// �R���X�g���N�^
{
	flg = true;
	landingflg = false;
	groundflg = false;
	life = 3;
	x = 40;
	y = 96;
	w = WIDTH;
	h = HEIGHT;
	inertiaX = 0;
	inertiaY = 0;
	speedX = 0;
	speedY = 0;
	speedMax = 3.0f;
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

	// �X�e�B�b�N���쎞��0����1�̊Ԃ��o��悤�ɂ���------------��Ő����ɂ���
	//speedX = round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100;
	//speedY = round(((float)PAD_INPUT::GetPadThumbLY() / 32767) * 100) / 100;

	// ��������
	if (inertiaY < 350 && !landingflg) {
		inertiaY += 1.5;
	}
	else if (groundflg) {
		inertiaY = 0;
		inertiaX = 0;
	}

	// A�{�^�����������Ƃ��ɏ�ɉ���
	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_A)) {

		if (groundflg) {
			!groundflg;
			inertiaY -= 100;
			
		}
		if (inertiaY > 0) {
			inertiaY -= 25 + (inertiaY / 4);
		}
		else {
			inertiaY -= 50;
		}

		//�E�����ɓ��͂����܂�A�{�^�����������Ȃ�E�ɉ���
		if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 >= 0.1) {
			inertiaX += 1.0f;
			// ���������Ƃ��ɑ��x����Ȃ瑬�x������ŌŒ�
			if (inertiaX > speedMax) {
				inertiaX = speedMax;
			}
		}
		//�������ɓ��͂����܂�A�{�^�����������Ȃ獶�ɉ���
		if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1) {
			inertiaX -= 1.0f;
			// ���������Ƃ��ɑ��x����Ȃ瑬�x������ŌŒ�
			if (inertiaX < -speedMax) {
				inertiaX = -speedMax;
			}
		}
	}

	//�E����
	if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 >= 0.1 && inertiaX < speedMax && !landingflg) {
		inertiaX += 0.001f;
	}
	else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 >= 0.1 && inertiaX < speedMax && landingflg) {
		inertiaX = 2.0f;
	}

	//������
	if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1 && inertiaX > -speedMax && !landingflg) {
		inertiaX -= 0.001f;
	}

	else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1 && inertiaX > -speedMax && landingflg) {
		inertiaX = - 2.0f;
	}

	y += inertiaY / (FRAMERATE * 1.0f);		// ���̏d��(�t���[���� * ���D�̐�)
	x += inertiaX;

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
	if (y < 0) {		// ��ʏ�̒��˕Ԃ�
		inertiaY *= -0.8f;
	}

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

bool Player::IsFly(Stage box){
	int nowhit = Player::HitBox(box);
	clsDx();
	printfDx("%d",nowhit);
	if (Player::HitBox(box) == 6) {
		landingflg = true;
		groundflg = true;
		return true;
	}
	landingflg = false;
	groundflg = false;
	return false;
}

float Player::GetBoxTop(Stage box) {
	return box.GetTop();
}