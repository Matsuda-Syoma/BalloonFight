#include"DxLib.h"
#include"common.h"
#include"SceneManager.h"
#include"Title.h"
#include"PAD_INPUT.h"
#include "FPSController.h"

//test-------------------
#include"GameMain.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	SetMainWindowText("BalloonFight");		// �^�C�g����ݒ�
	ChangeWindowMode(true);					// �E�B���h�E���[�h�ŋN��

	// �E�B���h�E�T�C�Y�̐ݒ�
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// DX���C�u�����̏���������
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);			// �`����ʂ𗠂ɂ���

	SceneManager scene = (dynamic_cast<AbstractScene*>(new GameMain(0,4,3)));

	FpsController FPSct(FRAMERATE,UPDATETIME);

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && scene.Update() != nullptr) {

		PAD_INPUT::UpdateInput();			// PAD�̓��͍X�V
		ClearDrawScreen();					// ��ʂ̏�����

		// �`�揈��

		scene.Draw();

		FPSct.All();

		clsDx();
		int i;
		int j;
		GetMousePoint(&i, &j);
		printfDx("%d %d", i,j);

		ScreenFlip();						// ����ʂ̓��e��\�ɕ\������
	}

	// DX���C�u�����̏I������
	DxLib_End();
	return 0;
}
