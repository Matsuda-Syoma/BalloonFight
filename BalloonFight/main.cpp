#include"DxLib.h"
#include"common.h"
#include"PAD_INPUT.h"
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {

	// タイトルを設定
	SetMainWindowText("タイトル名");

	// ウィンドウモードで起動
	ChangeWindowMode(true);

	// ウィンドウサイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLORBIT);
	SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	// DXライブラリの初期化処理
	if (DxLib_Init() == -1)return -1;

	// 描画先画面を裏にする（ダブルバッファリング）
	SetDrawScreen(DX_SCREEN_BACK);

	// ゲームループ
	while (ProcessMessage() == 0) {

		// PADの入力更新
		PAD_INPUT::UpdateInput();

		// 画面の初期化
		ClearDrawScreen();

		// 描画処理

		// デバッグ処理
		PAD_INPUT::DebugInput();

		// 裏画面の内容を表に表示する
		ScreenFlip();
	}

	// DXライブラリの終了処理
	DxLib_End();

	return 0;
}
