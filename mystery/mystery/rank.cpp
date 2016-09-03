#include "header.h"

static int rank;
static int Font01;

typedef struct {
	int x, y;
}Point;
static double count;
static int radi = 250;
static Point rank_p[3];
static int uihandle;
const double roundradi = 2 * 3.14/360;
static int Font02;
void rank_Initialize() {
	rank = LoadGraph("image/ranking.png"); 
	Font01 = CreateFontToHandle("HGRPP1", 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"メイリオ"  の30pt,太さ3のフォントを作成
	Font02 = CreateFontToHandle("HGRPP1", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"メイリオ"  の30pt,太さ3の
	uihandle = LoadGraph("image/UIback.png");
	info_Initialize();
	save_LoadInfo();
	count = 0;
}


void rank_Finalize() {
	DeleteGraph(rank); 
	DeleteGraph(uihandle);
	DeleteFontToHandle(Font01);
	DeleteFontToHandle(Font02);
}

void rank_Update() {
	if (getKey(KEY_INPUT_RETURN) == 1) {
		SceneMgr_ChangeScene(eScene_Start);
		se_Play(Result_Ok);
	}

	count++;
	rank_p[0].x =WINDOW_WIDE/2+radi*cos(count/80+roundradi * 270);
	rank_p[0].y = 300+100 + radi*sin(count /80+roundradi * 270);

	rank_p[2].x = WINDOW_WIDE / 2 + radi*cos(count / 80 + roundradi * (270+120));
	rank_p[2].y = 300 + 100 + radi*sin(count / 80 + roundradi * (270 + 120));

	rank_p[1].x = WINDOW_WIDE / 2 + radi*cos(count / 80 + roundradi * (270+240));
	rank_p[1].y = 300 + 100 + radi*sin(count / 80 + roundradi * (270+240));
}

void draw_Info(int x,int y,char *level) {

	DrawRotaGraph(x, y, 1, 0, rank, TRUE);
	DrawStringToHandle(x - 180, y - 120, "ランキング", GetColor(255, 255, 255), Font01);
	DrawStringToHandle(x+70, y - 120, level, GetColor(255, 255, 255), Font01);

	int nowlevel;
	if (level == "初級")
		nowlevel = 0;

	if (level == "中級")
		nowlevel = 1;
	if (level == "上級")
		nowlevel = 2;


	DrawFormatStringToHandle(x-110, y-45, GetColor(255, 255, 255), Font01, "%s", save_getinfo()[nowlevel * 3].name);
	DrawFormatStringToHandle(x - 110, y - 45+70, GetColor(255, 255, 255), Font01, "%s", save_getinfo()[nowlevel * 3 + 1].name);
	DrawFormatStringToHandle(x - 110, y - 45 + 70+70, GetColor(255, 255, 255), Font01, "%s", save_getinfo()[nowlevel * 3 + 2].name);

	DrawFormatStringToHandle(x - 110+190, y - 45, GetColor(255, 255, 255), Font01, "%d m", save_getinfo()[nowlevel * 3].point);
	DrawFormatStringToHandle(x - 110 + 190, y - 45 + 70, GetColor(255, 255, 255), Font01, "%d m", save_getinfo()[nowlevel * 3 + 1].point);
	DrawFormatStringToHandle(x - 110 + 190, y - 45 + 70 + 70, GetColor(255, 255, 255), Font01, "%d m", save_getinfo()[nowlevel * 3 + 2].point);
}
void rank_Draw() {
	DrawBox(0, 0, WINDOW_WIDE, WINDOW_HEIGHT, GetColor(100, 255, 100), 1);
	DrawRotaGraph(WINDOW_WIDE / 2, WINDOW_HEIGHT / 2, 1, 0, uihandle, TRUE);
	DrawStringToHandle(100, WINDOW_HEIGHT - 50, "ENTERキー：スタート画面に戻る　", GetColor(255, 255, 255), Font02);
	draw_Info(rank_p[0].x, rank_p[0].y, "初級");
	draw_Info(rank_p[1].x, rank_p[1].y, "中級");
	draw_Info(rank_p[2].x, rank_p[2].y, "上級");

}