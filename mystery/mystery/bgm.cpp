#include "header.h"
//BGM�Đ�
//����BGM�Ɉڂ�ۂ͕K��BGM���~���Ă��玟�Ɉڂ邱��


static int bgmhandle[Bgm_none];
//������
void bgm_Initialize() {
	bgmhandle[Bgm_Playing]= LoadSoundMem("bgm/ryunomai.mp3"); // sound/town.mp3�����[�h���A���ʔԍ���handle�Ɋi�[
	bgmhandle[Bgm_Result] = LoadSoundMem("bgm/famipop3.wav");
}
//�����ɐݒ肵��BGM�Đ�
void bgm_Play(Bgm se) {

		PlaySoundMem(bgmhandle[se], DX_PLAYTYPE_LOOP);
}
//BGM��~
void bgm_Stop() {
	for (int i = 0; i < Bgm_none; i++)
		StopSoundMem(bgmhandle[i]);
}

//�I��
void bgm_Finalize() {
	for (int i = 0; i < Bgm_none;i++)
		StopSoundMem(bgmhandle[i]);
}