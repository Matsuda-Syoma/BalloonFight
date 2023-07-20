#include "Fish.h"
#include"Player.h"
#include"DxLib.h"

// �R���X�g���N�^
Fish::Fish(float _x)
{
	imagecnt = -1;
	WeitTime = 0;
	flg = false;

	x = _x;
	y = 400;
	w = WIDTH;
	h = HEIGHT;

	LoadDivGraph("Resources/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, image);

	
}

Fish::~Fish()
{

}

void Fish::Update()
{
	if (++WeitTime % 11 == 0 && flg ==true) {
		imagecnt = imagecnt+1;
	}
	if (imagecnt >= 5) {
		imagecnt = 0;
	}

	imageX = x + (w / 2);
	imageY = y + (h / 2);


	box.left = x;
	box.right = x + w;
	box.top = y;
	box.bottom = y + h;

	

}

void Fish::Draw() const
{
	DrawBox(box.left, box.top, box.right, box.bottom, 0xffffff, false);
	DrawRotaGraph(imageX, imageY, 1.0f, 0, image[imagecnt], true);
	DrawBox(150, 400, 500, 480, 0x00ff00, 0);
}

bool Fish::GetFlg() {
	return flg;
}

void Fish::LoadImage()
{
	/*�������̓t�@�C�������w�肵�܂��B
		�������͉摜�̕����������w�肵�܂��B����Ȃ�΂P�Q�Ȃ̂łP�Q���w�肵�܂��B
		��O�A��l�����͉��Əc�����ɑ΂���摜�̕������ł��B
		����ł���΁A���͂R��A�c�͂S�s�ɂȂ��Ă���̂ŁA�R�ƂS���w�肵�܂��B
		��T�A��U�����͕����摜����̑傫�����w�肵�܂��B
		��V�����́A�������ꂽ�摜���̃O���t�B�b�N�n���h����ۑ�����int�^�̔z��ւ̃|�C���^���w�肵�܂��B
		����͂P�Q���ǂނ̂ŁAint image[12]�ȂǂƂ����z������A���̃|�C���^��n���܂��B
		�z��̒��ɂ͈ȉ��̂悤�ɃO���t�B�b�N�n���h�����i�[����܂��B�����͔z��̓Y����\���Ă��܂��B*/

	LoadDivGraph("Resources/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, image);
}

