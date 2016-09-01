#include "header.h"

const static int EREMENT_Y = 240;    //「初級」文字のy位置
const static int INTERMED_Y = 270;    //「中級」文字のy位置
const static int SENIOR_Y = 300;    //「上級」文字のy位置


typedef enum {
	eMenu_Erement,     //初級
	eMenu_Intermed,    //中級
	eMenu_Senior,      //上級
	eMenu_Num,        //本項目の数
} eMenu;

typedef struct {
	int x, y;
}Point;

Point selection[3];
static int handle[4];
static int Font00,Font01;
static Level nowsel_level;

static int NowSelect = eMenu_Erement;    //現在の選択状態(初期は初級選択中)

Level get_nowsel_level() {
	return nowsel_level;
}
//初期化
void Menu_Initialize() {
	Font00=CreateFontToHandle("HGRPP1", 60, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"メイリオ"  の30pt,太さ3の
	Font01 = CreateFontToHandle("HGRPP1", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"メイリオ"  の30pt,太さ3の
	handle[0] = LoadGraph("image/mode_easy.png"); // 画像をロード
	handle[1] = LoadGraph("image/mode_normal.png"); // 画像をロード
	handle[2] = LoadGraph("image/mode_hard.png"); // 画像をロード
	handle[3] = LoadGraph("image/stageselect.png"); // 画像をロード
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


//終了処理
void Menu_Finalize() {
	for (int i = 0; i<sizeof(handle) / sizeof(handle[0]); i++)
		DeleteGraph(handle[i]);

	DeleteFontToHandle(Font00);
	DeleteFontToHandle(Font01);
	}


//更新
void Menu_Update() {
	if (getKey(KEY_INPUT_ESCAPE) == 1)
		SceneMgr_ChangeScene(eScene_Start);

	if (getKey(KEY_INPUT_RIGHT) == 1) {//下キーが押されていたら
		NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
		se_Play(Hiscored);
	}
	if (getKey(KEY_INPUT_LEFT) == 1) {//上キーが押されていたら
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
		se_Play(Hiscored);
	}
	nowsel_level = (Level)NowSelect;

	if (getKey(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
		se_Play(Result_Ok);
		switch (nowsel_level) {//現在選択中の状態によって処理を分岐
		case Easy://初級選択中なら
			SceneMgr_ChangeScene(eScene_Game);//シーンをゲーム画面に変更
			break;
		case Normal://中級選択中なら
			SceneMgr_ChangeScene(eScene_Game);//シーンをゲーム画面に変更
			break;
		case Hard://上級選択中なら
			SceneMgr_ChangeScene(eScene_Game);//シーンをゲーム画面に変更
			break;
		}
	}
}

	
void Menu_Draw() {   //描画
	DrawBox(0, 0, WINDOW_WIDE, WINDOW_HEIGHT, GetColor(255, 100, 100), 1);
	DrawStringToHandle(300, 50, "ステージ選択", GetColor(255, 255, 255), Font00);
	DrawStringToHandle(100, WINDOW_HEIGHT-50, "ESCキー：スタート画面　ENTERキー：決定　方向キー：選択", GetColor(255, 255, 255), Font01);
	/*DrawString(200, 150, "選択画面です。", GetColor(255, 255, 255));
	DrawString(200, 170, "上下キーを押し、エンターを押して下さい。", GetColor(255, 255, 255));
	DrawString(200,EREMENT_Y , "初級", GetColor(255, 255, 255));
	DrawString(200,INTERMED_Y, "中級", GetColor(255, 255, 255));
	DrawString(200,SENIOR_Y, "上級", GetColor(255, 255, 255));*/
	
	int y = 0;
	switch (NowSelect) {//現在の選択状態に従って処理を分岐
	case eMenu_Erement://初級選択中なら
		DrawRotaGraph(selection[0].x, selection[0].y, 1, -(double)get_mCount()/10, handle[3], TRUE);
		break;
	case eMenu_Intermed://中級選択中なら
		DrawRotaGraph(selection[1].x, selection[1].y, 1, -(double)get_mCount() / 10, handle[3], TRUE);
		break;
	case eMenu_Senior://上級選択中なら
		DrawRotaGraph(selection[2].x, selection[2].y, 1, -(double)get_mCount() / 10, handle[3], TRUE);
		break;
	}
	for(int i=0;i<3;i++)
	DrawRotaGraph(selection[i].x, selection[i].y, 1, 0, handle[i], TRUE);
	
	//DrawString(250, y, "■", GetColor(255, 255, 255));
}




	