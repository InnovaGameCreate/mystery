#include "header.h"
#pragma warning(disable:4996)
int k;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	bgm_Initialize();
	se_Initialize();
	SceneMgr_Initialize();
	wipe_Initialize();
	::AllocConsole();               // コマンドプロンプトが表示される
	freopen("CON", "r", stdin);     // 標準入力の割り当て
	freopen("CON", "w", stdout);    // 標準出力の割り当て
	freopen("CON", "w", stderr);    // 標準エラー出力の割り当て
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		
		SceneMgr_Update();  //更新
		if (get_mode() == 0)
			if (ClearDrawScreen() != 0)
				break;

		SceneMgr_Draw();    //描画
	
		if (get_mode()==1) {
			wipe_Update();
			wipe_Draw();
		}
		
		key_Update();

		fps_Update();	//更新
		fps_Draw();		//描画
		fps_Wait();		//待機
	}

	SceneMgr_Finalize();
	bgm_Finalize();
	se_Finalize();

	DxLib_End();
	return 0;
}


