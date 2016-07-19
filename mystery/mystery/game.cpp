#include "header.h"

static Gauge gauge;		//ゲージ

//ゲージを描画

void gauge_Update(Gauge *samp) {
	if (getKey(KEY_INPUT_RETURN) == 1)
		samp->on = 0;
	if (samp->on) {
		samp->count++;
		samp->now = samp->max*(sin(samp->count / samp->speed) + 1) / 2;
	}
}
void gauge_Draw(Gauge samp) {
	int  Red = GetColor(255, 0, 0); // 赤色の値を取得

	DrawBox(samp.x, samp.y, samp.x + samp.w, samp.y + samp.h, Red, FALSE);   // 四角形を描画
	DrawBox(samp.x, samp.y, samp.x + samp.w*(samp.now / samp.max), samp.y + samp.h, Red, TRUE);   // 四角形を描画(塗りつぶし)
}


//初期化
void Game_Initialize() {
	gauge.x = 100;
	gauge.y = 100;
	gauge.w = 500;
	gauge.h = 100;
	gauge.now = 0;
	gauge.max = 100;
	gauge.count = 0;
	gauge.speed = 10;
	gauge.on = 1;


}

//終了処理
void Game_Finalize() {

}

//更新
void Game_Update() {
	gauge_Update(&gauge);

}

//描画
void Game_Draw() {
	gauge_Draw(gauge);
}