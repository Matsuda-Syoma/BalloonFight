#include"DxLib.h"
#include"common.h"
#include"SceneManager.h"
#include"Title.h"
#include"PAD_INPUT.h"
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	SetMainWindowText("タイトル名");		// タイトルを設定
	ChangeWindowMode(true);					// ウィンドウモードで起動

	// ウィンドウサイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// DXライブラリの初期化処理
	if (DxLib_Init() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);			// 描画先画面を裏にする

	SceneManager scene = (dynamic_cast<AbstractScene*>(new Title()));

	// ゲームループ
	while (ProcessMessage() == 0 && scene.Update() != nullptr) {

		PAD_INPUT::UpdateInput();			// PADの入力更新
		ClearDrawScreen();					// 画面の初期化

		// 描画処理

		scene.Draw();

		ScreenFlip();						// 裏画面の内容を表に表示する
	}

	// DXライブラリの終了処理
	DxLib_End();
	return 0;
}
