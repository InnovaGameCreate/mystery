#include "header.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	SceneMgr_Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		SceneMgr_Update();  //更新
		SceneMgr_Draw();    //描画

		fps_Update();	//更新
		fps_Draw();		//描画
		fps_Wait();		//待機
	}

	SceneMgr_Finalize();

	DxLib_End();
	return 0;
}