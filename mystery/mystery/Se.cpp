#include "header.h"

//Se�p�n���h��
static int sehandle[Se_none];

//������
void se_Initialize() {
	//��Fsehandle[Stone_Jump] = LoadSoundMem("se/poyo.mp3"); // se/poyo.mp3 �����[�h���A���ʔԍ���Handle�Ɋi�[

}

// �����ɐݒ肵�����ʉ����Đ�����
void se_Play(Se se) {
	switch (se)
	{
	case Stone_Jump:
		//��FPlaySoundMem(sehandle[se], DX_PLAYTYPE_BACK);
		break;

	}
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