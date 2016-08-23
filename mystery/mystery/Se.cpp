#include "header.h"

//Se用ハンドル
static int sehandle[Se_none];

//初期化
void se_Initialize() {
	//例：sehandle[Stone_Jump] = LoadSoundMem("se/poyo.mp3"); // se/poyo.mp3 をロードし、識別番号をHandleに格納

}

// 引数に設定した効果音を再生する
void se_Play(Se se) {
	switch (se)
	{
	case Stone_Jump:
		//例：PlaySoundMem(sehandle[se], DX_PLAYTYPE_BACK);
		break;

	}
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