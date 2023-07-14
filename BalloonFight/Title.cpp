#include "Title.h"
#include"DxLib.h"

Title::Title()
{
	Imgflg = 1;
	CursorY = 300;
	CursorNum = 0;
	WaitTime = 0;

	TitleImg_Logo = LoadGraph("Resources/images/Title/Title_Logo.png");
	TitleImg_Select = LoadGraph("Resources/images/Title/Title_ModeSelect.png");
	TitleImg_Credit = LoadGraph("Resources/images/Title/Title_Credit.png");

	LoadDivGraph("Resources/images/Title/Title_CursorAnimation.png", 4, 4, 1, 32, 64, TitleImg_Cursor);
}

Title::~Title()
{

}

AbstractScene* Title::Update()
{
	// %が割り切れる時＆フラグで反転
	if (++WaitTime % 21 == 0 && Imgflg == 1) {
		CursorNum = CursorNum + 1;
	}

	if (++WaitTime % 21 == 0 && Imgflg == -1) {
		CursorNum = CursorNum - 1;
	}

	// フラグ反転処理
	if (CursorNum >= 3) {
		Imgflg = -1;
	}
	if (CursorNum <= 0) {
		Imgflg = 1;
	}

	// タイトルカーソル下移動
	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_DPAD_DOWN) == TRUE) {
		CursorY = CursorY + 35;
	}
	if (CursorY > 370) {
		CursorY = 300;
	}

	// タイトルカーソル上移動
	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_DPAD_UP) == TRUE) {
		CursorY = CursorY - 35;
	}
	if (CursorY < 300) {
		CursorY = 370;
	}

	if (PAD_INPUT::GetKeyFlg(XINPUT_BUTTON_A) && CursorY == 300) {
		return new GameMain;
	}

	return this;
}

void Title::Draw() const
{
	DrawRotaGraph(330, 140, 1, 0, TitleImg_Logo, TRUE);
	DrawRotaGraph(340, 330, 1, 0, TitleImg_Select, TRUE);
	DrawRotaGraph(340, 450, 1, 0, TitleImg_Credit, TRUE);

	/*DrawRotaGraph(150, CursorY, 1, 0, testimg, TRUE);*/

	DrawRotaGraph(150, CursorY, 1.0f, 0, TitleImg_Cursor[CursorNum], true,0);
	/* DrawString(150, CursorY, "●", 0xff0000); */
}