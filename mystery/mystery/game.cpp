#include "header.h"

static Gauge gauge;		//�Q�[�W

//�Q�[�W��`��

void gauge_Update(Gauge *samp) {
	if (getKey(KEY_INPUT_RETURN) == 1)
		samp->on = 0;
	if (samp->on) {
		samp->count++;
		samp->now = samp->max*(sin(samp->count / samp->speed) + 1) / 2;
	}
}
void gauge_Draw(Gauge samp) {
	int  Red = GetColor(255, 0, 0); // �ԐF�̒l���擾

	DrawBox(samp.x, samp.y, samp.x + samp.w, samp.y + samp.h, Red, FALSE);   // �l�p�`��`��
	DrawBox(samp.x, samp.y, samp.x + samp.w*(samp.now / samp.max), samp.y + samp.h, Red, TRUE);   // �l�p�`��`��(�h��Ԃ�)
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
	gauge.speed = 10;
	gauge.on = 1;


}

//�I������
void Game_Finalize() {

}

//�X�V
void Game_Update() {
	gauge_Update(&gauge);

}

//�`��
void Game_Draw() {
	gauge_Draw(gauge);
}