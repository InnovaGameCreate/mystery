#include "header.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	SceneMgr_Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		SceneMgr_Update();  //�X�V
		SceneMgr_Draw();    //�`��

		fps_Update();	//�X�V
		fps_Draw();		//�`��
		fps_Wait();		//�ҋ@
	}

	SceneMgr_Finalize();

	DxLib_End();
	return 0;
}