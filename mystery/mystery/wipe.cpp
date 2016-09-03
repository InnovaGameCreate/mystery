#include "header.h"

#define MAXUP 0
#define SPEED 15
static int handle;
static int x, y;
static int areaset;
void wipe_Initialize() {
	handle = LoadGraph("image/wipe.png"); // ‰æ‘œ‚ðƒ[ƒh
	y = WINDOW_HEIGHT + WINDOW_HEIGHT / 2+100;
	x = WINDOW_WIDE/2;	
}

void set_Initialize() {
	y = WINDOW_HEIGHT + WINDOW_HEIGHT / 2 + 100;
	x = WINDOW_WIDE / 2;
}

void wipe_Finalize() {
	DeleteGraph(handle);
}
void wipe_Update() {

		SetDrawArea(0, y - WINDOW_HEIGHT / 2, WINDOW_WIDE, y + 1000);

		if (y > MAXUP) {
			y -= SPEED;
		}
		else {
			set_mode(0);
			SetDrawArea(0, 0, WINDOW_WIDE, WINDOW_HEIGHT);
		}
		

}

void wipe_Draw() {
	DrawRotaGraph(x, y, 1, 0, handle, TRUE);
}