#include "enemy.h"
#include "common.h"
#include "DxLib.h"
#include "LoadSounds.h"
// �摜���[�h����

// �R���X�g���N�^
Enemy::Enemy(float _x,float _y)
{
	w = WIDTH;
	h = HEIGHT;
	AnimImg = 0;

	flg = true;
	imageReverse = true;

	x = _x;
	y = _y - WIDTH;

	balloon = 1;
	color = GetRand(2);

	FlyspeedMax = 2;
	inertiaX = 0;
	inertiaY = 0;
	MoveX = 0;
	MoveY = GetRand(1);
	RandomMoveX = 0;
	RandomMoveY = 0;

	MaxRandomMoveX = GetRand(5) + 1 * FRAMERATE;
	MaxRandomMoveY = GetRand(2) + 2* FRAMERATE;
	jumpdelay = 0;

	LoadImages();
}

// �f�X�g���N�^
Enemy::~Enemy()
{

}

void Enemy::E_Init(int _life)
{
	
}

void Enemy::Update()
{
	// �G�̉摜�̒��S���W
	imageX = x + (w / 2);
	imageY = y + (w / 2);

	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

	if (inertiaY < 75 && !landingflg || missflg) {
		if (flg && groundflg) {
			//AnimFlg = 0;
			state = STATE::fly;
		}
		inertiaY += 1.0;
	}

	groundflg = landingflg;

	if (jumpdelay > 0) {
		--jumpdelay;
	}
	// ���ړ����邩�ǂ��������߂�
	if (++RandomMoveX > MaxRandomMoveX || MoveX == 0) {
		MoveX = GetRand(2) - 1;
		RandomMoveX = 0;
		MaxRandomMoveX = GetRand(2) + 3 * FRAMERATE;
	}
	// ���ړ�����
	inertiaX += MoveX * 0.01;
	// ���x����𒴂����瑬�x���Œ肷��
	if (inertiaX > FlyspeedMax) {
		inertiaX = FlyspeedMax;
	}
	if (inertiaX < -FlyspeedMax) {
		inertiaX = -FlyspeedMax;
	}
	// �㏸���邩�ǂ��������߂�
	if (++RandomMoveY > MaxRandomMoveY) {
		MoveY = GetRand(1);
		RandomMoveY = 0;
		MaxRandomMoveY = GetRand(3) + 2 * FRAMERATE;
	}
	// �㏸����
	if (MoveY == 1 && jumpdelay <= 0) {
		//AnimFlg = 0;
		state = STATE::fly;
		if (!CheckSoundMem(Sounds::SE_EnemyMove)) {
			PlaySoundMem(Sounds::SE_EnemyMove, DX_PLAYTYPE_BACK, true);
		}
		jumpdelay = DELAY;
		if (groundflg) {
			groundflg = false;
			inertiaY -= 15.0f;
		}
		if (inertiaY > 0) {
			inertiaY -= 10.0f + (inertiaY / 6);
		}
		else {
			inertiaY -= 10.0f;				// ���x�����A���܏オ��̂��x��
		}
		// �㏸���x����𒴂����瑬�x���Œ肷��
		if (inertiaY < -75) {
			inertiaY = -75;
		}

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
		y = 0 - (WIDTH / 2);
		inertiaY *= -0.8f;
	}


	y += inertiaY / FRAMERATE;		// ���̏d��(�t���[���� * ���D�̐�)
	x += inertiaX;
}

void Enemy::Draw() const
{
	// �摜�ݒ�@�摜�\���ԍ��@�摜��ʃt���O
	DrawRotaGraph(imageX, imageY, 1.0f, 0, images[color][AnimImg], true, imageReverse);
	DrawBox((int)box.left, (int)box.top, (int)box.right, (int)box.bottom, 0xffffff, false);
	DrawFormatString((int)box.left + 14, (int)box.top,0xffffff, "%d", balloon);
	DrawFormatString((int)box.left + 14, (int)box.top - 20,0xffffff, "%d", color);
}

void Enemy::LoadImages()
{
	LoadDivGraph("Resources/images/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, images[0]);
	LoadDivGraph("Resources/images/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, images[1]);
	LoadDivGraph("Resources/images/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, images[2]);
}

bool Enemy::IsFly(Stage box) {
	HitStage = Enemy::HitBox(box);
	// �㑤�ɓ��������Ƃ��̔���
	if (HitStage == 1) {
		landingflg = true;
		if (!groundflg && jumpdelay <= 0) {
			inertiaY = 0;
			//inertiaX = 0;
			groundflg = true;
		}
		if (jumpdelay <= DELAY - 1) {
			y = GetBoxSide(box, 1) - h;
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

float Enemy::GetBoxSide(BoxCollider box, int i) {
	return box.GetSide(i);
}

float Enemy::GetX() {
	return x;
}

float Enemy::GetY() {
	return y;
}

bool Enemy::GetFlg() {
	return flg;
}

void Enemy::SetFlg(bool _flg) {
	flg = _flg;
}

void Enemy::ChangeInertia(BoxCollider _player, int i) {
	switch (i)
	{
	case 1:
		y = GetBoxSide(_player, 2) + 1;
		inertiaY *= -RESTITUTION_COEFFICIENT;
		break;
	case 2:
		y = GetBoxSide(_player, 1) - (h + 1);
		inertiaY *= -RESTITUTION_COEFFICIENT;
		break;
	case 3:
		x = GetBoxSide(_player, 4) + 1;
		inertiaX *= -RESTITUTION_COEFFICIENT;
		break;
	case 4:
		x = GetBoxSide(_player, 3) - (w + 1);
		inertiaX *= -RESTITUTION_COEFFICIENT;
		break;
	default:
		break;
	/*case 1:
		y = GetBoxSide(_player, 1) - (h + 1);
		break;
	case 2:
		y = GetBoxSide(_player, 2) + 1;
		inertiaY *= -0.8f;
		break;
	case 3:
		x = GetBoxSide(_player, 3) - (w + 1);
		inertiaX *= -0.8f;
		break;
	case 4:
		x = GetBoxSide(_player, 4) + 1;
		inertiaX *= -0.8f;
		break;*/
	}
}

int Enemy::HitEnemy(BoxCollider _enemy) {

	int HitEnemy = HitBox(_enemy);

	switch (HitEnemy)
	{
	case 1:
		y = GetBoxSide(_enemy, 1) - (h + 1);
		inertiaY *= -0.8f;
		return 1;
		break;
	case 2:
		y = GetBoxSide(_enemy, 2) + 1;
		inertiaY *= -0.8f;
		return 2;
		break;
	case 3:
		x = GetBoxSide(_enemy, 3) - (w + 1);
		inertiaX *= -0.8f;
		return 3;
		break;
	case 4:
		x = GetBoxSide(_enemy, 4) + 1;
		inertiaX *= -0.8f;
		return 4;
		break;
	default:
		return 0;
		break;
	}

}

void Enemy::AnimUpdate()
{
	switch (state)
	{
	case STATE::stay:
		break;
	case STATE::walk:
		break;
	case STATE::fly:
		break;
	case STATE::miss:
		break;
	default:
		break;
	}
}
