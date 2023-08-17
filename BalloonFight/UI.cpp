#include "UI.h"
#include "DxLib.h"
#include"common.h"
//�R���X�g���N�^
UI::UI()
{
	OverCount = 0;
	NowScore = 0;
	HighScore = 10000;
	Stage = 1;
	PhaseCount = 0;
	GameOverFlg = false;
	Title_flg = false;
	for (int i = 0; i < 6; i++) {
		Score[i] = 0;
	}
	for (int i = 0; i < 6; i++) {
		HiScore[i] = 0;
	}
	LoadImages();
}

//�f�X�g���N�^
UI::~UI()
{

}

//�X�V
void UI::Update(int _score, int _stage)
{
	HighScoreWork = HighScore;
	NowScore = _score;
	Stage = _stage;

	if (GameOverFlg == true) {
		if (++OverCount > FRAMERATE) {
			Title_flg = true;
		}
	}
	//�n�C�X�R�A���X�V
	if (NowScore > HighScore) {
		HighScore = NowScore;
	}

	for (int i = 0; i < 6; i++) {
		Score[i] = NowScore % 10;
		NowScore /= 10;
	}
	for (int i = 0; i < 6; i++) {
		HiScore[i] = HighScoreWork % 10;
		HighScoreWork /= 10;
	}

	if (PhaseCount < 240) {
		PhaseCount++;
		if (PhaseCount % 20 < 10) {
			PhaseFlg = true;
		}
		else {
			PhaseFlg = false;
		}
	}
}

//�`��
void UI::Draw() const
{
	//�X�R�A
	DrawGraph(20, 10, ScoreImg, true);
	//DrawFormatString(40, 10, 0xFFFFFF, "%06d", NowScore);
	for (int i = 0; i < 6; i++) {
		DrawRotaGraph(30 + (20 * (6 - i)), 18, 1.0, 0.0, NumImg[Score[i]],TRUE);
	}
	DrawGraph(260, 10, HighScoreImg, true);
	for (int i = 0; i < 6; i++) {
		DrawRotaGraph(290 + (20 * (6 - i)), 18, 1.0, 0.0, NumImg[HiScore[i]], TRUE);
	}
	//DrawFormatString(310, 40, 0xFFFFFF, "%06d", HighScore);
	//DrawGraph(310, 10, NumImg[0], true);

	if (GameOverFlg) {
		//DrawString(280, 230, "GameOver", 0xffffff);
		DrawGraph(220, 220, GameOImg, TRUE);
	}


	if (!PhaseFlg) {
		//DrawFormatString(290, 30, 0xffa500, "PHASE-%d", Stage);
		DrawGraph(260, 30, PhaseImg, TRUE);
		DrawGraph(380, 20, NumImg[Stage], TRUE);
	}

}

//�摜�Ǎ�
void UI::LoadImages()
{
	ScoreImg = LoadGraph("Resources/images/UI/UI_Score.png");
	HighScoreImg = LoadGraph("Resources/images/UI/UI_HiScore.png");
	GameOImg = LoadGraph("Resources/images/UI/UI_GameOver.png");
	PhaseImg = LoadGraph("Resources/images/UI/UI_Phase.png");
	LoadDivGraph("Resources/images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, NumImg);


}

//�摜�폜
void UI::DeleteImages()
{

}

void UI::GameOver()
{
	GameOverFlg = true;
}

int UI::GetHighScore()
{
	return HighScore;
}
