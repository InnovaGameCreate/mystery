#include "header.h"
#define MAXX 5905		//�w�i�̉E�[
#define MINX 0			//�w�i�̍��[
#define FLYTIME 3		//��Ԏ���
#define UPPOWER -18        //������̏����l
double const DOWNPOWER = 0.5;   //�d��
#define UNDERY 350      //���n��
#define MOVECAMEX WINDOW_WIDE/2-20
#define TIMINGRADI 100    //�^�C�~���O�Q�[�W�̔��a


typedef enum {
	Gauge,
	Fly,
	NextPoint,
	Result
}GameFaze;

static Gauge_Info gauge;		//�Q�[�W

static Stone stone;    //��

static GameFaze nowfaze;

static Level nowlevel= Easy;

static int backhandle[3];

static int backgroundx;     //�w�i�ړ��␳

static int timinglimit = 300;  //���n�ʂ܂ł̗P�\��
static int gameoverlimit;             //�Q�[���I�[�o�[�܂ł̕�

static double timingradi[3];
//�X�s�[�h�̌���
void decindeSpeed(Stone *samp,Gauge_Info gau) {
	samp->xspeed = 1*(gau.now / gau.max)*20;
	samp->yspeed = UPPOWER;
}

//�Q�[�W�v�Z
void gauge_Update(Gauge_Info *samp) {
	if (getKey(KEY_INPUT_RETURN) == 1) {
		decindeSpeed(&stone,gauge);
		nowfaze = Fly;
	}
		samp->count+= samp->speed;
		samp->now = samp->count % 100;
	
}
//�Q�[�W�`��
void gauge_Draw(Gauge_Info samp) {
	int  Red = GetColor(255, 0, 0); // �ԐF�̒l���擾

	DrawBox(samp.x, samp.y, samp.x + samp.w, samp.y + samp.h, Red, FALSE);   // �l�p�`��`��
	DrawBox(samp.x, samp.y, samp.x + samp.w*(samp.now / samp.max), samp.y + samp.h, Red, TRUE);   // �l�p�`��`��(�h��Ԃ�)

}

//���n���̃^�C�~���O�v�Z
void timingUpdate(Stone *samp) {
	gameoverlimit = UNDERY+timinglimit - samp->y;
	
	int sa = (UNDERY < samp->y) ? samp->y - UNDERY : UNDERY - samp->y;
	timingradi[0] = TIMINGRADI;
	timingradi[1] = ((double)gameoverlimit / (UNDERY + timinglimit - (UNDERY - timinglimit)))*TIMINGRADI;
	timingradi[2] = ((double)gameoverlimit / (UNDERY + timinglimit - (UNDERY - timinglimit)))*TIMINGRADI-5;
	if (gameoverlimit <= 0) {
		nowfaze = Result;
		return;
	}
	
	if (getKey(KEY_INPUT_RETURN) == 1) {
		nowfaze = Fly;
		samp->yspeed = UPPOWER;
	}
}
//���n���̃^�C�~���O�`��
void timing_Draw(Stone samp) {
	int blue = GetColor(0, 0,255);
	int red = GetColor(255, 0, 0);
	DrawCircle(200, 200,timingradi[0], blue, TRUE);
	DrawCircle(200, 200,  timingradi[1], red, TRUE);
	DrawCircle(200, 200, timingradi[2], blue, TRUE);
}
//�w�i�v�Z
void backgrouind_Update(int x) {
	backgroundx-=x;
}

//�w�i�`��
void backgrouind_Draw() {
	DrawRotaGraph((MAXX + MINX) / 2+backgroundx, WINDOW_HEIGHT / 2, 1, 0, backhandle[0], TRUE);
}

//��Ԍv�Z
void fry_Update(Stone *samp,Gauge_Info sam) {
	if (MOVECAMEX > samp->x)
		samp->x += samp->xspeed;
	else
		backgrouind_Update(samp->xspeed);
	samp->y += samp->yspeed;

	samp->yspeed += DOWNPOWER;

	if (nowfaze==Fly&&UNDERY-timinglimit < samp->y&&samp->yspeed>0)
		nowfaze = NextPoint;
}

//�Ε`��
void stone_Draw(Stone samp) {
	int  Green = GetColor(0, 255, 0); // �ԐF�̒l���擾
	DrawBox(samp.x, samp.y, samp.x+ samp.w, samp.y+ samp.h, Green, TRUE);
}

//������
void Game_Initialize() {
	nowfaze = Gauge;

	//�Q�[�W�����l
	gauge.x = 100;
	gauge.y = 100;
	gauge.w = 500;
	gauge.h = 100;
	gauge.now = 0;
	gauge.max = 100;
	gauge.count = 0;
	gauge.speed = 1;

	//�Ώ����l
	stone.x = 100;
	stone.y = UNDERY;
	stone.w = 100;
	stone.h = 100;
	stone.flytime = 0;
	stone.penaltytime = 0;
	stone.xspeed = 0;
	stone.yspeed = 0;

	backgroundx = 0;

	backhandle[0] = LoadGraph("image/background1.png"); // �摜�����[�h
	backhandle[0] = LoadGraph("image/background1.png"); // �摜�����[�h
	backhandle[0] = LoadGraph("image/background1.png"); // �摜�����[�h
}

//�I������
void Game_Finalize() {
	for(int i=0;i<sizeof backhandle/sizeof backhandle[0];i++)
		DeleteGraph(backhandle[i]);
}

//�X�V
void Game_Update() {
	switch (nowfaze) {
	case Gauge:
		gauge_Update(&gauge);
		break;
	case Fly:
		fry_Update(&stone, gauge);
		break;
	case NextPoint:
		fry_Update(&stone, gauge);
		timingUpdate(&stone);
		break;
	case Result:
		break;
	}

}

//�`��
void Game_Draw() {
	backgrouind_Draw();
	stone_Draw(stone);
	gauge_Draw(gauge);
	if(nowfaze==NextPoint)

		timing_Draw(stone);

}