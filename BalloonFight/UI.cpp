#include "UI.h"

//�R���X�g���N�^
UI::UI()
{

}

//�f�X�g���N�^
UI::~UI()
{

}

//�X�V
AbstractScene* UI::Update()
{
	
}

//�`��
void UI::Draw() const
{
	DrawString(100, 100, "test title", 0xff0000);
}