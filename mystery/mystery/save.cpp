#include "header.h"
#define _CRT_SECURE_NO_WARNINGS

static Ranking info[9];

void save_Initialize() {

	for (int i = Easy;i<Level_None ; i++) {
		for (int j = 0; j < 3; j++) {
			int id_length = strlen(info[i * 3 + j].name);
			memset(info[i * 3 + j].name, '\0', id_length);
			info[i * 3 + j].point = 0;
		}
	}
}

//�X�R�A�X�V���ǂ���
bool save_NewRecord(Level lev,int point) {
	for (int i = 0; i < 3; i++) {
		if (info[lev * 3 + i].point < point) {
			return true;
		}
	}
	return false;
}
void save_Input(Level lev,char *name,int point) {
	


	FILE* fp;
	errno_t error;
	if (error = fopen_s(&fp, "�Z�[�u�f�[�^.dat", "wb") != 0) {
		//�G���[����
		
	
	}

	for (int i = 0; i < 3; i++) {
		if (info[lev * 3 + i].point < point) {
			for (int j = 2; j >= i; j--) {
				strcpy_s(info[lev * 3 + j].name, info[lev * 3 + j - 1].name);

				info[lev * 3 + j].point = info[lev * 3 + j - 1].point;
			}
			strcpy_s(info[lev * 3 + i].name, name);
			info[lev * 3 + i].point = point;
			break;
		}
	
	}

	
	fwrite(info, sizeof(Ranking), 9, fp); // SaveData_t�\���̂̒��g���o��
	
	fclose(fp);

}

void save_LoadInfo() {
	FILE* fp;
	errno_t error;
	if (error = fopen_s(&fp, "�Z�[�u�f�[�^.dat", "rb") != 0) {
		//�G���[����
		FILE* f;
		errno_t errorr;
		if (errorr = fopen_s(&f, "�Z�[�u�f�[�^.dat", "wb") != 0) {
			//�G���[����
		
		}
	
			fwrite(info, sizeof(Ranking), 9, f); // SaveData_t�\���̂̒��g���o��
			fclose(f);
		
	}
	else {
		fread(info, sizeof(Ranking), 9, fp);
		fclose(fp);		//�G���[���ɂ͕���K�v�Ȃ�
	}

	return;
}
Ranking *save_getinfo() {
	return info;
}

