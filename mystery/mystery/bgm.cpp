#include "header.h"
//BGM再生
//次のBGMに移る際は必ずBGMを停止してから次に移ること


static Bgm bgmhandle[Bgm_none];
//初期化
void bgm_Initialize() {
	//例：player[Start]= LoadSoundMem("sound/town.mp3"); // sound/town.mp3をロードし、識別番号をhandleに格納

}
//引数に設定したBGM再生
void bgm_Play(Bgm se) {

	switch (se)
	{
	case Start:
		
		break;
	case Menu:
		PlaySoundMem(bgmhandle[se], DX_PLAYTYPE_LOOP);
		break;
	case Playing:

		break;
	}
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