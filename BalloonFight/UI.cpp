#include "UI.h"
#include "DxLib.h"
//�R���X�g���N�^
UI::UI()
{
	NowScore = 0;
	HighScore = 10000;

	Stage = 1;
	PhaseCount = 0;
}

//�f�X�g���N�^
UI::~UI()
{

}

//�X�V
void UI::Update()
{
	if (PhaseCount < 240) {
		PhaseCount++;
		if (PhaseCount % 20 < 10) {
			PhaseFlg = true;
		}
		else {
			PhaseFlg = false;
		}
	}

	//�n�C�X�R�A���X�V
	if (NowScore > HighScore) {
		HighScore = NowScore;
	}
}

//�`��
void UI::Draw() const
{
	//�X�R�A
	DrawString(20, 10, "I-", 0xff0000);
	DrawFormatString(40, 10, 0xFFFFFF, "%06d", NowScore);

	DrawString(270, 10, "TOP-", 0xffa500);
	DrawFormatString(310, 10, 0xFFFFFF, "%06d", HighScore);

	if (PlayerLife == 0) {
		DrawString(280, 230, "GameOver", 0xffffff);
	}


	if (!PhaseFlg) {
		DrawFormatString(290, 30, 0xffa500, "PHASE-%d", Stage);
	}
}

//�摜�Ǎ�
void UI::LoadImages()
{

}

//�摜�폜
void UI::DeleteImages()
{

}