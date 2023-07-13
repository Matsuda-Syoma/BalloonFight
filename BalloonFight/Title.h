#pragma once
#include "AbstractScene.h"
class Title : public AbstractScene {
private:
	int TitleImg_Logo;					// �^�C�g�����S�摜
	int TitleImg_Select;				// �^�C�g���Z���N�g�摜
	int TitleImg_Credit;				// �^�C�g���N���W�b�g�摜
	int TitleImg_Cursor[4];				// �^�C�g���J�[�\���摜
	int CursorNum;
	int CursorY = 330;

	int WaitTime;
public:
	Title();							// �R���X�g���N�^
	~Title();							// �f�X�g���N�^
	AbstractScene* Update() override;	// �`��ȊO�̍X�V�����s
	void Draw() const override;			// �`��Ɋւ��邱�Ƃ�����
	void LoadImage();
	bool CAnim_Play();
};
