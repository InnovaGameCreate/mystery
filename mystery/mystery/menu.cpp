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

static int NowSelect = eMenu_Erement;    //現在の選択状態(初期は初級選択中)

//初期化
void Menu_Initialize() {
}


//終了処理
void Menu_Finalize() {
	}


//更新
void Menu_Update() {
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {//下キーが押されていたら
		NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
	}
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {//上キーが押されていたら
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
	}
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1) {//エンターキーが押されたら
		switch (NowSelect) {//現在選択中の状態によって処理を分岐
		case eMenu_Erement://初級選択中なら
			SceneMgr_ChangeScene(eScene_Game);//シーンをゲーム画面に変更
			break;
		case eMenu_Intermed://中級選択中なら
			SceneMgr_ChangeScene(eScene_Game);//シーンをゲーム画面に変更
			break;
		case eMenu_Senior://上級選択中なら
			SceneMgr_ChangeScene(eScene_Game);//シーンをゲーム画面に変更
			break;
		}
	}
}

	
void Menu_Draw() {   //描画
	DrawString(200, 150, "選択画面です。", GetColor(255, 255, 255));
	DrawString(200, 170, "上下キーを押し、エンターを押して下さい。", GetColor(255, 255, 255));
	DrawString(200,EREMENT_Y , "初級", GetColor(255, 255, 255));
	DrawString(200,INTERMED_Y, "中級", GetColor(255, 255, 255));
	DrawString(200,SENIOR_Y, "上級", GetColor(255, 255, 255));
	
	int y = 0;
	switch (NowSelect) {//現在の選択状態に従って処理を分岐
	case eMenu_Erement://初級選択中なら
		y =EREMENT_Y;    //初級の座標を格納
		break;
	case eMenu_Intermed://中級選択中なら
		y =INTERMED_Y;    //中級の座標を格納
		break;
	case eMenu_Senior://上級選択中なら
		y =SENIOR_Y;    //上級の座標を格納
		break;
	}
	DrawString(250, y, "■", GetColor(255, 255, 255));
}




	