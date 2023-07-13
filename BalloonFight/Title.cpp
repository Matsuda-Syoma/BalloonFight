#include "Title.h"
#include"DxLib.h"

Title::Title()
{
	LoadImage();
	CursorNum = 0;
	WaitTime = 0;

	TitleImg_Logo = LoadGraph("Resources/images/Title/Title_Logo.png");
	TitleImg_Select = LoadGraph("Resources/images/Title/Title_ModeSelect.png");
	TitleImg_Credit = LoadGraph("Resources/images/Title/Title_Credit.png");
	/*TitleImg_Cursor = LoadGraph("Resources/images/Title/Title_CursorAnimation.png");*/
	
	LoadDivGraph("Resources/images/Title/Title_CursorAnimation.png", 4, 4, 1, 64, 64, TitleImg_Cursor);
}

Title::~Title()
{

}

AbstractScene* Title::Update()
{
	return this;
}

void Title::Draw() const
{
	DrawRotaGraph(330, 140, 1, 0, TitleImg_Logo, TRUE);
	DrawRotaGraph(340, 330, 1, 0, TitleImg_Select, TRUE);
	DrawRotaGraph(340, 450, 1, 0, TitleImg_Credit, TRUE);

	DrawRotaGraph(340, CursorY, 1, 0, TitleImg_Cursor[1], TRUE, 0);
	/* DrawString(150, CursorY, "œ", 0xff0000); */
}

void Title::LoadImage()
{
	LoadDivGraph("Resources/images/Title/Title_CursorAnimation.png", 4, 4, 1, 64, 64, TitleImg_Cursor);
}

bool Title::CAnim_Play()
{
	if (++WaitTime % 3 == 0) {
		CursorNum++;
	}
	if (CursorNum > 3) {
		return true;
	}
	return false;
}