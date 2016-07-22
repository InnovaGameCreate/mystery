#include "header.h"

static int mImageHandle;    //画像ハンドル格納用変数


//初期化
void Menu_Initialize() {
	void Menu_Initialize() {
		mImageHandle = LoadGraph("Scene_Menu.png");    //画像のロード
	}

}

//終了処理
void Menu_Finalize() {
	void Menu_Finalize() {
		DeleteGraph(mImageHandle);    //画像の解放
	}

}

//更新
void Menu_Update() {
	
}
 //描画
void Menu_Draw() {

	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

																			 // メニュー項目要素を3つ作る
		MenuElement_t MenuElement[5] = {
			{ 0, 100, "初級",GetColor(255,255,255) },
			{ 20, 150, "中級",GetColor(255,255,255) },
			{ 20, 200, "上級",GetColor(255,255,255) },
			
		};
		int SelectNum = 0; // 現在の選択番号

	if (Key[KEY_INPUT_DOWN] == 1) { // 下キーが押された瞬間だけ処理

		SelectNum = (SelectNum + 1) % 3; // 現在の選択項目を一つ下にずらす(ループする)

		for (int i = 0; i<3; i++) {   // メニュー項目数である3個ループ処理
			if (Key[KEY_INPUT_UP] == 1) { // 上キーが押された瞬間だけ処理

				SelectNum = (SelectNum + 2) % 3; // 現在の選択項目を一つ上にずらす(逆ループする)
			}

			if (i == SelectNum) {          // 今処理しているのが、選択番号と同じ要素なら
				MenuElement[i].x = 0; // 座標を0にする
			}
			else {                       // 今処理しているのが、選択番号以外なら
				MenuElement[i].x = 20;// 座標を20にする
			}
		}
	}

}