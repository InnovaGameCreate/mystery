#include "header.h"

//Se用ハンドル
static int sehandle[Se_none];

//初期化
void se_Initialize() {
	sehandle[Gauge_Move] = LoadSoundMem("se/jump05.mp3"); // se/poyo.mp3 をロードし、識別番号をHandleに格納
	sehandle[Gauge_Ok] = LoadSoundMem("se/moveup.wav");
	sehandle[Timing_Move] = LoadSoundMem("se/jump06.mp3");
	sehandle[Timing_Ok] = LoadSoundMem("se/ccc.wav");
	sehandle[Finished] = LoadSoundMem("se/result.wav");
	sehandle[Hiscored] = LoadSoundMem("se/good.wav");
	sehandle[Result_Ok] = LoadSoundMem("se/decide.wav");
}

// 引数に設定した効果音を再生する
void se_Play(Se se) {

		PlaySoundMem(sehandle[se], DX_PLAYTYPE_BACK);

}

//終了
void se_Finalize() {
	//再生停止
	for (int i = 0; i < Se_none; i++)
		StopSoundMem(sehandle[i]);

	//ファイルの開放
	for (int i = 0; i < Se_none; i++)
		DeleteSoundMem(sehandle[i]);
}