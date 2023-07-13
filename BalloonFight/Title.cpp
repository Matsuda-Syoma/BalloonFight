#include "Title.h"

Title::Title()
{
	LoadImage();
	CursorNum = 0;
	WaitTime = 0;

	TitleImg_Logo = LoadGraph("Resources/images/Title/Title_Logo.png");
	TitleImg_Select = LoadGraph("Resources/images/Title/Title_ModeSelect.png");
	TitleImg_Credit = LoadGraph("Resources/images/Title/Title_Credit.png");
	/*TitleImg_Cursor = LoadGraph("Resources/images/Title/Title_CursorAnimation.png");*/
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

	DrawRotaGraph(340, CursorY, 1.0f, 0, TitleImg_Cursor[CursorNum], TRUE, 0);

	/*DrawRotaGraph(imageX, imageY, 1.0f, 0, images[AnimImg], true, 0);*/

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