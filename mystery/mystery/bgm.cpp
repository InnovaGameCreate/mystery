#include "header.h"
//BGMÄ¶
//Ÿ‚ÌBGM‚ÉˆÚ‚éÛ‚Í•K‚¸BGM‚ğ’â~‚µ‚Ä‚©‚çŸ‚ÉˆÚ‚é‚±‚Æ


static int bgmhandle[Bgm_none];
//‰Šú‰»
void bgm_Initialize() {
	bgmhandle[Bgm_Playing]= LoadSoundMem("bgm/ryunomai.mp3"); // sound/town.mp3‚ğƒ[ƒh‚µA¯•Ê”Ô†‚ğhandle‚ÉŠi”[
	bgmhandle[Bgm_Result] = LoadSoundMem("bgm/famipop3.wav");
}
//ˆø”‚Éİ’è‚µ‚½BGMÄ¶
void bgm_Play(Bgm se) {

		PlaySoundMem(bgmhandle[se], DX_PLAYTYPE_LOOP);
}
//BGM’â~
void bgm_Stop() {
	for (int i = 0; i < Bgm_none; i++)
		StopSoundMem(bgmhandle[i]);
}

//I—¹
void bgm_Finalize() {
	for (int i = 0; i < Bgm_none;i++)
		StopSoundMem(bgmhandle[i]);
}