#include "header.h"
//BGM再生
//次のBGMに移る際は必ずBGMを停止してから次に移ること


static int bgmhandle[Bgm_none];
//初期化
void bgm_Initialize() {
	bgmhandle[Bgm_Playing]= LoadSoundMem("bgm/ryunomai.mp3"); // sound/town.mp3をロードし、識別番号をhandleに格納
	bgmhandle[Bgm_Result] = LoadSoundMem("bgm/famipop3.wav");
}
//引数に設定したBGM再生
void bgm_Play(Bgm se) {

		PlaySoundMem(bgmhandle[se], DX_PLAYTYPE_LOOP);
}
//BGM停止
void bgm_Stop() {
	for (int i = 0; i < Bgm_none; i++)
		StopSoundMem(bgmhandle[i]);
}

//終了
void bgm_Finalize() {
	for (int i = 0; i < Bgm_none;i++)
		StopSoundMem(bgmhandle[i]);
}