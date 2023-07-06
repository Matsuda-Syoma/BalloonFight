#include "common.h"
#include "Player.h"
#include "LoadSounds.h"

enum class STATE {
	stay = 0,
	walk,
	fly,
	miss,
};
STATE state;

Player::Player()			// �R���X�g���N�^
{
	w = WIDTH;
	h = HEIGHT;
	GroundspeedMax = 3.0f;
	FlyspeedMax = 3.0f;
	Init(2);
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
	balloon = 2;
	x = 40;
	y = 410 - WIDTH;
	inertiaX = 0;
	inertiaY = 0;
	speedX = 0;
	startX = 0.15f;
	jumpdelay = 0;
	state = STATE::stay;
	AnimUpdateTime = 0;
	AnimImg = 0;
	AnimWork = 0;
	animflg = false;
	imageReverse = true;
}

void Player::Update()		// �v���C���[�̍X�V����
{
	// �v���C���[�̉摜�̒��S���W
	imageX = x + (w / 2);
	imageY = y + (w / 2);

	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

		// ��������
	if (inertiaY < 150 && !landingflg || missflg) {
		if (flg) {	
			state = STATE::fly;
		}
		inertiaY += 2.0 * (3 - balloon);
	}

	/////////�f�o�b�O����
	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_Y)) {
		BallonBreak(1);
	}
	clsDx();
	printfDx("%02d %02d %d %d %f",AnimUpdateTime, AnimImg, state, jumpdelay ,inertiaX);

	if (flg == true) {

		groundflg = landingflg;		// ����Ȃ��悤�ɂ���

		// �W�����v�̃N�[���^�C��
		if (jumpdelay > 0) {
			--jumpdelay;
		}

		// A�{�^�����������Ƃ��ɏ�ɉ���
		//if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_A) && jumpdelay <= 0) {
		if (PAD_INPUT::GetNowKey(XINPUT_BUTTON_A) && jumpdelay <= 0) {	//////////�����A��
			animflg = false;
			state = STATE::fly;
			PlaySoundMem(Sounds::SE_PlayerJump, DX_PLAYTYPE_BACK, true);
			jumpdelay = DELAY;
			if (groundflg) {
				groundflg = false;
				inertiaY -= 15.0f;
			}
			if (inertiaY > 0) {
				inertiaY -= 40.0f + (inertiaY / 6);
			}
			else {
				inertiaY -= 40.0f;				// ���x�����A���܏オ��̂��x��
			}
			if (inertiaY < -150) {
				inertiaY = -150;
			}
			// �E�����ɓ��͂����܂�A�{�^�����������Ȃ�E�ɉ���
			if (inputX() >= 0.1) {
				inertiaX += 1.0f;
				// ���������Ƃ��ɑ��x����Ȃ瑬�x������ŌŒ�
				if (inertiaX > FlyspeedMax) {
					inertiaX = FlyspeedMax;
				}
			}
			// �������ɓ��͂����܂�A�{�^�����������Ȃ獶�ɉ���
			if (inputX() <= -0.1) {
				inertiaX -= 1.0f;
				// ���������Ƃ��ɑ��x����Ȃ瑬�x������ŌŒ�
				if (inertiaX < -FlyspeedMax) {
					inertiaX = -FlyspeedMax;
				}
			}
		}

		// �E����
		if (inputX() >= 0.1) {
			imageReverse = true;
			if (inertiaX < FlyspeedMax && !landingflg) {
				inertiaX += 0.001f;
			}
			else if (inertiaX < GroundspeedMax && landingflg) {
				inertiaX += startX - 0.05f;
			}
		}
		else if (inputX() == 0 && inertiaX > 0 && landingflg) {
			inertiaX += -startX;
		}

		// ������
		if (inputX() <= -0.1) {
			imageReverse = false;
			if (inertiaX > -FlyspeedMax && !landingflg) {
				inertiaX -= 0.001f;
			}
			else if (inertiaX > -GroundspeedMax && landingflg) {
				inertiaX += -startX + 0.05f;
			}
		}
		else if (inputX() == 0 && inertiaX < 0 && landingflg) {
			inertiaX += startX;
		}

		if (inputX() == 0 && inertiaX < 0.15f && inertiaX > -0.15f) {
			inertiaX = 0;
		}

		// ���ʉ��̍Đ�(����)
		if (++speedX > 35 && inertiaX != 0 && landingflg) {
			PlaySoundMem(Sounds::SE_PlayerWalk, DX_PLAYTYPE_BACK, true);
			speedX = 0;
		}

		// ��ʊO�ɏo���甽�Α�����o�Ă���
		if (x + WIDTH < 0) {
			x = SCREEN_WIDTH;
		}
		if (x > SCREEN_WIDTH) {
			x = 0 - WIDTH;
		}

		// ��ʏ�̒��˕Ԃ�
		if (y < 0 - (WIDTH / 2)) {
			y = 0 - ((WIDTH / 2));
			inertiaY *= -0.8f;
		}
	}

	// ��ʉ��ɍs�����ꍇ�~�X
	if (y > SCREEN_HEIGHT) {
		Init(--life);
		PlaySoundMem(Sounds::SE_Restart, DX_PLAYTYPE_BACK, true);
	}

	// �v���C���[�̍��W�X�V
	y += inertiaY / FRAMERATE;		// ���̏d��(�t���[���� * ���D�̐�)
	x += inertiaX;

	// �A�j���[�V�����̍X�V
	AnimUpdate();

}
// �v���C���[�̕`��
void Player::Draw() const
{
	DrawRotaGraph(imageX, imageY, 1.0f, 0, images[AnimImg],true, imageReverse);
	DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, 0xff0000, false);
}

// �R���g���[���̓��͂�Ԃ�
float Player::inputX() {
	return round(((float)PAD_INPUT::GetPadThumbLX() / 32767) * 100) / 100;
}

// �摜�̓ǂݍ���
void Player::LoadImages() {
	LoadDivGraph("Resources/images/Player/Player_animation_d.png",32,8,4,64,64,images);
}

// �v���C���[�����ł邩�Ԃ�(1:��A2:���A3:���A4:�E)
bool Player::IsFly(Stage box){
	HitStage = Player::HitBox(box);

	// �㑤�ɓ��������Ƃ��̔���
	if (HitStage == 1) {
		landingflg = true;
		state = STATE::stay;
		if (!groundflg && jumpdelay <= 0) {
			inertiaY = 0;
			//inertiaX = 0;
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
		imageReverse = !imageReverse;
		inertiaX *= -0.8f;
	}
	// �E�ɂ����������̔���
	if (HitStage == 4) {
		//x = GetBoxSide(box, 4) - (x - GetBoxSide(box, 4));
		x = GetBoxSide(box, 4) + 1;
		imageReverse = !imageReverse;
		inertiaX *= -0.8f;
	}
	landingflg = false;
	return false;
}

// �v���C���[�̃t���O��Ԃ�
bool Player::IsFlg() {
	return flg;
}

// �����Ő��l��Ԃ�(1:��A2:���A3:���A4:�E)
float Player::GetBoxSide(Stage box ,int i) {
	return box.GetSide(i);
}

// �_���[�W���Ɉ��������D�����炷
void Player::BallonBreak(int i) {
	PlaySoundMem(Sounds::SE_Splash, DX_PLAYTYPE_BACK, true);
	AnimUpdateTime = 31;
	AnimImg += 8;
	balloon -= i;
	if (balloon <= 0) {
		flg = false;
		Miss(0);
	}
}

// 0�������A1��������
void Player::Miss(int i) {
	switch (i) {
		case 0:
			if (!missflg) {
				state = STATE::miss;
				inertiaX = 0.0f;
				inertiaY = -150.0f;
				missflg = true;
			}
			break;
	}
}

// �v���C���[�̃��C�t��Ԃ�
int Player::GetLife() {
	return life;
}

// �A�j���[�V�����̍X�V
void Player::AnimUpdate() {
	AnimUpdateTime++;
	switch (state)
	{
	case STATE::stay:
		animflg = false;
		if (AnimUpdateTime > 17) {
			if (AnimWork % 2 == 0) {
				if (balloon == 2) {
					AnimImg = 1;
				}
				if (balloon == 1) {
					AnimImg = 1 + 3;
				}
			}
			else if (AnimWork % 4 == 1) {
				if (balloon == 2) {
					AnimImg = 2;
				}
				if (balloon == 1) {
					AnimImg = 2 + 3;
				}
			}
			else {
				if (balloon == 2) {
					AnimImg = 0;
				}
				if (balloon == 1) {
					AnimImg = 0 + 3;
				}
			}
			AnimWork++;
			AnimUpdateTime = 0;
		}
		break;
	case STATE::walk:

		break;
	case STATE::fly:
		if (animflg == false) {
			if (balloon == 2) {
				AnimImg = 21;
			}
			if (balloon == 1) {
				AnimImg = 21 + 8;
			}
			AnimUpdateTime = 0;
			animflg = true;
			if (!groundflg && jumpdelay <= 0) {
				if (balloon == 2) {
					AnimImg = 20;
				}
				if (balloon == 1) {
					AnimImg = 20 + 8;
				}
				AnimUpdateTime = 50;
			}
		}
		if (animflg == false && !groundflg) {
			
		}
		if (AnimUpdateTime < 10) {
			if (AnimUpdateTime % 2 == 0) {
				if (balloon == 2) {
					AnimImg--;
				}
				if (balloon == 1) {
					AnimImg--;
				}
				//AnimUpdateTime = 0;
			}
		}
		else if (AnimUpdateTime < 18) {
			if (AnimUpdateTime % 2 == 0) {
				if (balloon == 2) {
					AnimImg++;
				}
				if (balloon == 1) {
					AnimImg++;
				}
				//AnimUpdateTime = 0;
			}
		}
		break;
	case STATE::miss:
		if (AnimUpdateTime > 2) {
			if (AnimWork % 3 == 0) {
					AnimImg = 23;
			}
			else {
				AnimImg--;
			}
			AnimWork++;
			AnimUpdateTime = 0;
		}
		break;
	default:
		break;
	}
}