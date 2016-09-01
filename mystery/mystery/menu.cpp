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

typedef struct {
	int x, y;
}Point;

Point selection[3];
static int handle[4];
static int Font00,Font01;
static Level nowsel_level;

static int NowSelect = eMenu_Erement;    //���݂̑I�����(�����͏����I��)

Level get_nowsel_level() {
	return nowsel_level;
}
//������
void Menu_Initialize() {
	Font00=CreateFontToHandle("HGRPP1", 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"���C���I"  ��30pt,����3��
	Font01 = CreateFontToHandle("HGRPP1", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"���C���I"  ��30pt,����3��
	handle[0] = LoadGraph("image/mode_easy.png"); // �摜�����[�h
	handle[1] = LoadGraph("image/mode_normal.png"); // �摜�����[�h
	handle[2] = LoadGraph("image/mode_hard.png"); // �摜�����[�h
	handle[3] = LoadGraph("image/stageselect.png"); // �摜�����[�h
	NowSelect = eMenu_Erement;
	nowsel_level = Easy;
	
	DrawRotaGraph(300, 300, 1, 0, handle[0], TRUE);
	DrawRotaGraph(300, 300, 1, 0, handle[1], TRUE);
	DrawRotaGraph(300, 300, 1, 0, handle[2], TRUE);
	DrawRotaGraph(300, 300, 1, 0, handle[3], TRUE);

	for (int i = 0; i < 3; i++) {
		selection[i].x = 200 + i * 300;
		selection[i].y = 300;
	}

}


//�I������
void Menu_Finalize() {
	for (int i = 0; i<sizeof(handle) / sizeof(handle[0]); i++)
		DeleteGraph(handle[i]);

	DeleteFontToHandle(Font00);
	DeleteFontToHandle(Font01);
	}


//�X�V
void Menu_Update() {
	if (getKey(KEY_INPUT_ESCAPE) == 1)
		SceneMgr_ChangeScene(eScene_Start);

	if (getKey(KEY_INPUT_RIGHT) == 1) {//���L�[��������Ă�����
		NowSelect = (NowSelect + 1) % eMenu_Num;//�I����Ԃ��������
		se_Play(Hiscored);
	}
	if (getKey(KEY_INPUT_LEFT) == 1) {//��L�[��������Ă�����
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//�I����Ԃ���グ��
		se_Play(Hiscored);
	}
	nowsel_level = (Level)NowSelect;

	if (getKey(KEY_INPUT_RETURN) == 1) {//�G���^�[�L�[�������ꂽ��
		se_Play(Result_Ok);
		switch (nowsel_level) {//���ݑI�𒆂̏�Ԃɂ���ď����𕪊�
		case Easy://�����I�𒆂Ȃ�
			SceneMgr_ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
			break;
		case Normal://�����I�𒆂Ȃ�
			SceneMgr_ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
			break;
		case Hard://�㋉�I�𒆂Ȃ�
			SceneMgr_ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
			break;
		}
	}
}

	
void Menu_Draw() {   //�`��
	DrawBox(0, 0, WINDOW_WIDE, WINDOW_HEIGHT, GetColor(255, 100, 100), 1);
	DrawStringToHandle(300, 50, "�X�e�[�W�I��", GetColor(255, 255, 255), Font00);
	DrawStringToHandle(100, WINDOW_HEIGHT-50, "ESC�L�[�F�X�^�[�g��ʁ@ENTER�L�[�F����@�����L�[�F�I��", GetColor(255, 255, 255), Font01);
	/*DrawString(200, 150, "�I����ʂł��B", GetColor(255, 255, 255));
	DrawString(200, 170, "�㉺�L�[�������A�G���^�[�������ĉ������B", GetColor(255, 255, 255));
	DrawString(200,EREMENT_Y , "����", GetColor(255, 255, 255));
	DrawString(200,INTERMED_Y, "����", GetColor(255, 255, 255));
	DrawString(200,SENIOR_Y, "�㋉", GetColor(255, 255, 255));*/
	
	int y = 0;
	switch (NowSelect) {//���݂̑I����Ԃɏ]���ď����𕪊�
	case eMenu_Erement://�����I�𒆂Ȃ�
		DrawRotaGraph(selection[0].x, selection[0].y, 1, -(double)get_mCount()/10, handle[3], TRUE);
		break;
	case eMenu_Intermed://�����I�𒆂Ȃ�
		DrawRotaGraph(selection[1].x, selection[1].y, 1, -(double)get_mCount() / 10, handle[3], TRUE);
		break;
	case eMenu_Senior://�㋉�I�𒆂Ȃ�
		DrawRotaGraph(selection[2].x, selection[2].y, 1, -(double)get_mCount() / 10, handle[3], TRUE);
		break;
	}
	for(int i=0;i<3;i++)
	DrawRotaGraph(selection[i].x, selection[i].y, 1, 0, handle[i], TRUE);
	
	//DrawString(250, y, "��", GetColor(255, 255, 255));
}




	