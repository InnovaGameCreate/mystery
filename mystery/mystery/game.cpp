#include "header.h"

static Gauge gauge;		//ƒQ[ƒW

//ƒQ[ƒW‚ğ•`‰æ

void gauge_Update(Gauge *samp) {
	if (getKey(KEY_INPUT_RETURN) == 1)
		samp->on = 0;
	if (samp->on) {
		samp->count++;
		samp->now = samp->max*(sin(samp->count / samp->speed) + 1) / 2;
	}
}
void gauge_Draw(Gauge samp) {
	int  Red = GetColor(255, 0, 0); // ÔF‚Ì’l‚ğæ“¾

	DrawBox(samp.x, samp.y, samp.x + samp.w, samp.y + samp.h, Red, FALSE);   // lŠpŒ`‚ğ•`‰æ
	DrawBox(samp.x, samp.y, samp.x + samp.w*(samp.now / samp.max), samp.y + samp.h, Red, TRUE);   // lŠpŒ`‚ğ•`‰æ(“h‚è‚Â‚Ô‚µ)
}


//‰Šú‰»
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

//I—¹ˆ—
void Game_Finalize() {

}

//XV
void Game_Update() {
	gauge_Update(&gauge);

}

//•`‰æ
void Game_Draw() {
	gauge_Draw(gauge);
}