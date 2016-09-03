#include "header.h"
#pragma warning(disable:4996)
int k;
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);
	bgm_Initialize();
	se_Initialize();
	SceneMgr_Initialize();
	wipe_Initialize();
	::AllocConsole();               // �R�}���h�v�����v�g���\�������
	freopen("CON", "r", stdin);     // �W�����͂̊��蓖��
	freopen("CON", "w", stdout);    // �W���o�͂̊��蓖��
	freopen("CON", "w", stderr);    // �W���G���[�o�͂̊��蓖��
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		
		SceneMgr_Update();  //�X�V
		if (get_mode() == 0)
			if (ClearDrawScreen() != 0)
				break;

		SceneMgr_Draw();    //�`��
	
		if (get_mode()==1) {
			wipe_Update();
			wipe_Draw();
		}
		
		key_Update();

		fps_Update();	//�X�V
		fps_Draw();		//�`��
		fps_Wait();		//�ҋ@
	}

	SceneMgr_Finalize();
	bgm_Finalize();
	se_Finalize();

	DxLib_End();
	return 0;
}


