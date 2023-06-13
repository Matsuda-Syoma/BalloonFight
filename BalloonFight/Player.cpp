#include "common.h"
#include "Player.h"
#include "PAD_INPUT.h"
#include <math.h>

Player::Player() {
	flg = true;
	life = 3;
	x = 40;
	y = SCREEN_WIDTH - 96;
	w = WIDTH;
	h = HEIGHT;
	speedX = 0;
	speedY = 0;
	speedMax = 3;
	LoadImages();
}

Player::~Player()
{
}

void Player::LoadImages() {
	for (int i = 0; i < 3; i++) {
		images[i] = 0;
	}
}