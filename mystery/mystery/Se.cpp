#include "header.h"

//Se�p�n���h��
static int sehandle[Se_none];

//������
void se_Initialize() {
	sehandle[Gauge_Move] = LoadSoundMem("se/jump05.mp3"); // se/poyo.mp3 �����[�h���A���ʔԍ���Handle�Ɋi�[
	sehandle[Gauge_Ok] = LoadSoundMem("se/moveup.wav");
	sehandle[Timing_Move] = LoadSoundMem("se/jump06.mp3");
	sehandle[Timing_Ok] = LoadSoundMem("se/ccc.wav");
	sehandle[Finished] = LoadSoundMem("se/result.wav");
	sehandle[Hiscored] = LoadSoundMem("se/good.wav");
	sehandle[Result_Ok] = LoadSoundMem("se/decide.wav");
}

// �����ɐݒ肵�����ʉ����Đ�����
void se_Play(Se se) {

		PlaySoundMem(sehandle[se], DX_PLAYTYPE_BACK);

}

//�I��
void se_Finalize() {
	//�Đ���~
	for (int i = 0; i < Se_none; i++)
		StopSoundMem(sehandle[i]);

	//�t�@�C���̊J��
	for (int i = 0; i < Se_none; i++)
		DeleteSoundMem(sehandle[i]);
}