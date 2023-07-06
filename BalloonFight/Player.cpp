#include "common.h"
#include "Player.h"
#include "PAD_INPUT.h"
#include <math.h>

Player::Player()			// �R���X�g���N�^
{
	w = WIDTH;
	h = HEIGHT;
	GroundspeedMax = 2.0f;
	FlyspeedMax = 3.0f;
	Init(3);
	LoadImages();
}

Player::~Player()			// �f�X�g���N�^
{
}

// ���l�̏�����
void Player::Init(int _life) {
	flg = true;
	landingflg = false;
	groundflg = false;
	missflg = false;
	life = _life;
	ballon = 2;
	x = 40;
	y = 440 - WIDTH;
	inertiaX = 0;
	inertiaY = 0;
	speedX = 0;
	speedY = 0;
	jumpdelay = 0;
}

void Player::Update()		// �v���C���[�̍X�V����
{
	// �v���C���[�̉摜�̒��S���W
	imageX = x + (w / 2);
	imageY = y + (h / 2);

	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

		// ��������
	if (inertiaY < 325 && !landingflg || missflg) {
		inertiaY += 1.5 * (3 - ballon);
	}

	/////////�f�o�b�O����
	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_Y)) {
		BallonBreak(1);
	}

	if (flg == true) {

		groundflg = landingflg;		// ����Ȃ��悤�ɂ���

		// �W�����v�̃N�[���^�C��
		if (jumpdelay > 0) {
			--jumpdelay;
		}

		// A�{�^�����������Ƃ��ɏ�ɉ���
		//if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_A) && jumpdelay <= 0) {
		if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && jumpdelay <= 0) {	//////////�����A��
			jumpdelay = DELAY;
			if (groundflg) {
				groundflg = false;
				inertiaY -= 5.0f;
			}
			if (inertiaY > 0) {
				inertiaY -= 25.0f + (inertiaY / 4);
			}
			else {
				inertiaY -= 50.0f;				// ���x�����A���܏オ��̂��x��
			}
			// �E�����ɓ��͂����܂�A�{�^�����������Ȃ�E�ɉ���
			if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 >= 0.1) {
				inertiaX += 1.0f;
				// ���������Ƃ��ɑ��x����Ȃ瑬�x������ŌŒ�
				if (inertiaX > FlyspeedMax) {
					inertiaX = FlyspeedMax;
				}
			}
			// �������ɓ��͂����܂�A�{�^�����������Ȃ獶�ɉ���
			if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1) {
				inertiaX -= 1.0f;
				// ���������Ƃ��ɑ��x����Ȃ瑬�x������ŌŒ�
				if (inertiaX < -FlyspeedMax) {
					inertiaX = -FlyspeedMax;
				}
			}
		}

		// �E����
		if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 >= 0.1 && inertiaX < FlyspeedMax && !landingflg) {
			inertiaX += 0.001f;
		}
		else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 >= 0.1 && inertiaX < GroundspeedMax && landingflg) {
			inertiaX += 0.25f;
		}
		else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 == 0 && inertiaX > 0 && landingflg) {
			inertiaX += -0.25f;
		}

		// ������
		if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1 && inertiaX > -FlyspeedMax && !landingflg) {
			inertiaX -= 0.001f;
		}
		else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 <= -0.1 && inertiaX > -GroundspeedMax && landingflg) {
			inertiaX += -0.25f;
		}
		else if (round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100 == 0 && inertiaX < 0 && landingflg) {
			inertiaX += 0.25f;
		}

		// ��ʊO�ɏo���甽�Α�����o�Ă���
		if (x + WIDTH < 0) {
			x = SCREEN_WIDTH;
		}
		if (x > SCREEN_WIDTH) {
			x = 0 - WIDTH;
		}

		if (y < 0) {		// ��ʏ�̒��˕Ԃ�
			y = 0 - (y - 0);
			inertiaY *= -0.8f;
		}
	}

	//��ʉ��ɍs�����ꍇ�~�X
	if (y > SCREEN_HEIGHT) {
		Init(--life);
	}

	y += inertiaY / FRAMERATE;		// ���̏d��(�t���[���� * ���D�̐�)
	x += inertiaX;


}
// �v���C���[�̕`��
void Player::Draw() const
{
	DrawGraph(x, y, images[0], true);
	DrawFormatString(x +(w / 3), y - 20, 0xffffff, "%d", ballon);
	DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, 0xff0000, false);
	DrawCircle(x, y, 2, 0xffffff);
	
	
}

void Player::LoadImages() {
	LoadDivGraph("Resources/images/Player/Player_animation_d.png",32,8,4,64,64,images);
}

bool Player::IsFly(Stage box){
	HitStage = Player::HitBox(box);
	if (HitStage == 1) {
		landingflg = true;
		if (!groundflg && jumpdelay <= 0) {
			inertiaY = 0;
			inertiaX = 0;
			groundflg = true;
		}
		if (jumpdelay <= DELAY - 1) {
			y = GetBoxSide(box,1) - h;
		}
		return true;
		}

	// �����ɂ����������̔���
	if (HitStage == 2) {
		//y = GetBoxSide(box, 2) - (y - GetBoxSide(box, 2));
		y = GetBoxSide(box, 2) + 1;
		inertiaY *= -0.8f;
	}
	// ���ɂ����������̔���
	if (HitStage == 3) {
		x = GetBoxSide(box, 3) - (w + 1);
		inertiaX *= -0.8f;
	}
	// �E�ɂ����������̔���
	if (HitStage == 4) {
		//x = GetBoxSide(box, 4) - (x - GetBoxSide(box, 4));
		x = GetBoxSide(box, 4) + 1;
		inertiaX *= -0.8f;
	}
	landingflg = false;
	return false;
}

bool Player::IsFlg() {
	return flg;
}

// �����Ő��l��Ԃ�(1:��A2:���A3:���A4:�E)
float Player::GetBoxSide(Stage box ,int i) {
	return box.GetSide(i);
}

// 0�ȉ��Ȃ�true���Ԃ�
void Player::BallonBreak(int i) {
	ballon -= i;
	if (ballon <= 0) {
		flg = false;
		Miss(0);
	}
}

// 0�������A1��������
void Player::Miss(int i) {
	switch (i) {
		case 0:
			if (!missflg) {
				inertiaX = 0.0f;
				inertiaY = -150.0f;
				missflg = true;
			}
			break;
	}
}

int Player::GetLife() {
	return life;
}