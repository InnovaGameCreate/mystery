#include "header.h"
#define MAXX 2000		//�w�i�̉E�[
#define MINX 0			//�w�i�̍��[
#define FLYTIME 3		//��Ԏ���

static Gauge gauge;		//�Q�[�W

static Stone stone;    //��


void decindeSpeed(Stone *samp,Gauge gau) {
	samp->xspeed = 1*(gau.now / gau.max)*10;
	samp->yspeed = -20;
}
//�Q�[�W��`��
void gauge_Update(Gauge *samp) {
	if (getKey(KEY_INPUT_RETURN) == 1) {
		samp->on = 0;
		decindeSpeed(&stone,gauge);
	}
	if (samp->on) {
		samp->count+= samp->speed;
		samp->now = samp->count % 100;
	}
}
void gauge_Draw(Gauge samp) {
	int  Red = GetColor(255, 0, 0); // �ԐF�̒l���擾

	DrawBox(samp.x, samp.y, samp.x + samp.w, samp.y + samp.h, Red, FALSE);   // �l�p�`��`��
	DrawBox(samp.x, samp.y, samp.x + samp.w*(samp.now / samp.max), samp.y + samp.h, Red, TRUE);   // �l�p�`��`��(�h��Ԃ�)


}

void backgrouind_Draw() {
	DrawBox(MINX, 0, MAXX, WINDOW_HEIGHT, GetColor(0,0,255), TRUE);
}

void stone_Update(Stone *samp,Gauge sam) {
	if (sam.on)
		return;
	samp->x += samp->xspeed;
	samp->y += samp->yspeed;
}

void stone_Draw(Stone samp) {
	DrawBox(samp.x, samp.y, samp.x+ samp.w, samp.y+ samp.h, GetColor(255, 255, 255), TRUE);
}

//������
void Game_Initialize() {
	gauge.x = 100;
	gauge.y = 100;
	gauge.w = 500;
	gauge.h = 100;
	gauge.now = 0;
	gauge.max = 100;
	gauge.count = 0;
	gauge.speed = 1;
	gauge.on = 1;

	stone.x = 100;
	stone.y = 500;
	stone.w = 100;
	stone.h = 100;
	stone.flytime = 0;
	stone.penaltytime = 0;
	stone.xspeed = 0;
	stone.yspeed = 0;

}

//�I������
void Game_Finalize() {

}

//�X�V
void Game_Update() {
	gauge_Update(&gauge);
	stone_Update(&stone, gauge);
}

//�`��
void Game_Draw() {
	backgrouind_Draw();
	stone_Draw(stone);
	gauge_Draw(gauge);


}