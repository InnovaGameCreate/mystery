#include "header.h"
//BGM�Đ�
//����BGM�Ɉڂ�ۂ͕K��BGM���~���Ă��玟�Ɉڂ邱��


static Bgm bgmhandle[Bgm_none];
//������
void bgm_Initialize() {
	//��Fplayer[Start]= LoadSoundMem("sound/town.mp3"); // sound/town.mp3�����[�h���A���ʔԍ���handle�Ɋi�[

}
//�����ɐݒ肵��BGM�Đ�
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