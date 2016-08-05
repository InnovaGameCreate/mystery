#include "header.h"

const static int EREMENT_Y = 240;    //�u�����v������y�ʒu
const static int INTERMED_Y = 270;    //�u�����v������y�ʒu
const static int SENIOR_Y = 300;    //�u�㋉�v������y�ʒu


typedef enum {
	eMenu_Erement,     //����
	eMenu_Intermed,    //����
	eMenu_Senior,      //�㋉
	eMenu_Num,        //�{���ڂ̐�
} eMenu;

static int NowSelect = eMenu_Erement;    //���݂̑I�����(�����͏����I��)

//������
void Menu_Initialize() {
}


//�I������
void Menu_Finalize() {
	}


//�X�V
void Menu_Update() {
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {//���L�[��������Ă�����
		NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
	}
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {//��L�[��������Ă�����
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
	}
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
		switch (NowSelect) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
		case eMenu_Erement://�����I�𒆂Ȃ�
			SceneMgr_ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
			break;
		case eMenu_Intermed://�����I�𒆂Ȃ�
			SceneMgr_ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
			break;
		case eMenu_Senior://�㋉�I�𒆂Ȃ�
			SceneMgr_ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
			break;
		}
	}
}

	
void Menu_Draw() {   //�`��
	DrawString(200, 150, "�I����ʂł��B", GetColor(255, 255, 255));
	DrawString(200, 170, "�㉺�L�[�������A�G���^�[�������ĉ������B", GetColor(255, 255, 255));
	DrawString(200,EREMENT_Y , "����", GetColor(255, 255, 255));
	DrawString(200,INTERMED_Y, "����", GetColor(255, 255, 255));
	DrawString(200,SENIOR_Y, "�㋉", GetColor(255, 255, 255));
	
	int y = 0;
	switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Erement://�����I�𒆂Ȃ�
		y =EREMENT_Y;    //�����̍��W���i�[
		break;
	case eMenu_Intermed://�����I�𒆂Ȃ�
		y =INTERMED_Y;    //�����̍��W���i�[
		break;
	case eMenu_Senior://�㋉�I�𒆂Ȃ�
		y =SENIOR_Y;    //�㋉�̍��W���i�[
		break;
	}
	DrawString(250, y, "��", GetColor(255, 255, 255));
}




	