#include "header.h"
#define TITLE_X WINDOW_WIDE/2
#define TITLE_Y 200 
static int Handle[3];
static int Font00;
static int sel;
static double rota[2];
static int rankhandle;
static int uihandle;
static int Font01;
void start_Initialize() {
	Handle[0] = LoadGraph("image/title_back.png");
	Handle[1] = LoadGraph("image/title_font1.png");
	Handle[2] = LoadGraph("image/title_font2.png");
	uihandle = LoadGraph("image/UIback.png");
	rankhandle = LoadGraph("image/ranking.png");
	Font01 = CreateFontToHandle("HGRPP1", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"���C���I"  ��30pt,����3��
	Font00 = CreateFontToHandle("HGRPP1", 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"���C���I"  ��30pt,����3�̃t�H���g���쐬
	sel = 0;
}

void start_Finalize() {
	for (int i = 0; i < sizeof(Handle) / sizeof(Handle[0]); i++)
		DeleteGraph(Handle[i]);
	DeleteFontToHandle(Font00);
	DeleteFontToHandle(Font01);
	DeleteGraph(rankhandle);
	DeleteGraph(uihandle);
}

void start_Update() {
	rota[0] = 0.1*sin((double)get_mCount() / 10), Handle[1];
	rota[1] = 0.1*cos((double)get_mCount() / 10), Handle[1];
	switch (sel) {
	case 0:
		if (getKey(KEY_INPUT_RETURN) == 1) {
			sel = 1;
			se_Play(Result_Ok);
		}
		break;
	case 1:
		if (getKey(KEY_INPUT_RETURN) == 1) {
			SceneMgr_ChangeScene(eScene_Menu);
			se_Play(Result_Ok);
		}
		if (getKey(KEY_INPUT_DOWN) == 1) {
			sel = 2;
			se_Play(Hiscored);
		}
		break;
	case 2:
		if (getKey(KEY_INPUT_RETURN) == 1) {
			SceneMgr_ChangeScene(eScene_Rank);
			se_Play(Result_Ok);
		}
		if (getKey(KEY_INPUT_UP) == 1) {
			sel = 1;
			se_Play(Hiscored);
		}

		if (getKey(KEY_INPUT_DOWN) == 1) {
			sel = 3;
			se_Play(Hiscored);
		}

		break;
	case 3:
		if (getKey(KEY_INPUT_RETURN) == 1) {
			save_Initialize();
			se_Play(Result_Ok);
		}
		if (getKey(KEY_INPUT_UP) == 1) {
			sel = 2;
			se_Play(Hiscored);
		}

		break;
	}
}

void start_Draw() {


	DrawRotaGraph(WINDOW_WIDE/2, WINDOW_HEIGHT/2, 1, 0, uihandle, TRUE);
	SetDrawMode(DX_DRAWMODE_BILINEAR);

	DrawRotaGraph(TITLE_X, TITLE_Y, 1, 0, Handle[0], TRUE);
	DrawRotaGraph(TITLE_X, TITLE_Y, 1, rota[0], Handle[1],TRUE);
	DrawRotaGraph(TITLE_X, TITLE_Y, 1, rota[1], Handle[2], TRUE);
	SetDrawMode(DX_DRAWMODE_NEAREST);

	switch (sel) {
	case 0:
		if (get_mCount() % 60 < 30)
			DrawStringToHandle(250, 480, "ENTER�L�[�������Ă�������", GetColor(255, 255, 255), Font00);
		break;
	case 1:
		DrawStringToHandle(100, WINDOW_HEIGHT - 50, "�㉺�����L�[�F�I���@ENTER�L�[�F����", GetColor(255, 255, 255), Font01);
		DrawStringToHandle(350, 380, "�Q�[���X�^�[�g", GetColor(255, 0, 0), Font00);
		DrawStringToHandle(350, 380 + 50, "�����L���O������", GetColor(255, 255, 255), Font00);
		DrawStringToHandle(350, 380 + 100, "�f�[�^������", GetColor(255, 255, 255), Font00);
		break;
	case 2:
		DrawStringToHandle(100, WINDOW_HEIGHT - 50, "�㉺�����L�[�F�I���@ENTER�L�[�F����", GetColor(255, 255, 255), Font01);
		DrawStringToHandle(350, 380, "�Q�[���X�^�[�g", GetColor(255, 255, 255), Font00);
		DrawStringToHandle(350, 380 + 50, "�����L���O������", GetColor(255, 0, 0), Font00);
		DrawStringToHandle(350, 380 + 100, "�f�[�^������", GetColor(255, 255, 255), Font00);
		break;
	case 3:
		DrawStringToHandle(100, WINDOW_HEIGHT - 50, "�㉺�����L�[�F�I���@ENTER�L�[�F����", GetColor(255, 255, 255), Font01);
		DrawStringToHandle(350, 380, "�Q�[���X�^�[�g", GetColor(255, 255, 255), Font00);
		DrawStringToHandle(350, 380 + 50, "�����L���O������", GetColor(255, 255, 255), Font00);
		DrawStringToHandle(350, 380 + 100, "�f�[�^������", GetColor(255, 0, 0), Font00);
		break;
	}
	
}