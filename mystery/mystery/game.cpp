#include "header.h"
#define MAXX 5905		//背景の右端
#define MINX 0			//背景の左端
#define FLYTIME 3		//飛ぶ時間
#define UPPOWER -18        //上方向の初期値
double const DOWNPOWER = 0.5;   //重力
#define UNDERY 350      //着地面
#define MOVECAMEX WINDOW_WIDE/2-20
#define TIMINGRADI 100    //タイミングゲージの半径


typedef enum {
	Gauge,
	Fly,
	NextPoint,
	Result
}GameFaze;

static Gauge_Info gauge;		//ゲージ

static Stone stone;    //石

static GameFaze nowfaze;

static Level nowlevel= Easy;

static int backhandle[3];

static int backgroundx;     //背景移動補正

static int timinglimit = 300;  //着地面までの猶予幅
static int gameoverlimit;             //ゲームオーバーまでの幅

static double timingradi[3];
//スピードの決定
void decindeSpeed(Stone *samp,Gauge_Info gau) {
	samp->xspeed = 1*(gau.now / gau.max)*20;
	samp->yspeed = UPPOWER;
}

//ゲージ計算
void gauge_Update(Gauge_Info *samp) {
	if (getKey(KEY_INPUT_RETURN) == 1) {
		decindeSpeed(&stone,gauge);
		nowfaze = Fly;
	}
		samp->count+= samp->speed;
		samp->now = samp->count % 100;
	
}
//ゲージ描画
void gauge_Draw(Gauge_Info samp) {
	int  Red = GetColor(255, 0, 0); // 赤色の値を取得

	DrawBox(samp.x, samp.y, samp.x + samp.w, samp.y + samp.h, Red, FALSE);   // 四角形を描画
	DrawBox(samp.x, samp.y, samp.x + samp.w*(samp.now / samp.max), samp.y + samp.h, Red, TRUE);   // 四角形を描画(塗りつぶし)

}

//着地時のタイミング計算
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
//着地時のタイミング描画
void timing_Draw(Stone samp) {
	int blue = GetColor(0, 0,255);
	int red = GetColor(255, 0, 0);
	DrawCircle(200, 200,timingradi[0], blue, TRUE);
	DrawCircle(200, 200,  timingradi[1], red, TRUE);
	DrawCircle(200, 200, timingradi[2], blue, TRUE);
}
//背景計算
void backgrouind_Update(int x) {
	backgroundx-=x;
}

//背景描画
void backgrouind_Draw() {
	DrawRotaGraph((MAXX + MINX) / 2+backgroundx, WINDOW_HEIGHT / 2, 1, 0, backhandle[0], TRUE);
}

//飛ぶ計算
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

//石描画
void stone_Draw(Stone samp) {
	int  Green = GetColor(0, 255, 0); // 赤色の値を取得
	DrawBox(samp.x, samp.y, samp.x+ samp.w, samp.y+ samp.h, Green, TRUE);
}

//初期化
void Game_Initialize() {
	nowfaze = Gauge;

	//ゲージ初期値
	gauge.x = 100;
	gauge.y = 100;
	gauge.w = 500;
	gauge.h = 100;
	gauge.now = 0;
	gauge.max = 100;
	gauge.count = 0;
	gauge.speed = 1;

	//石初期値
	stone.x = 100;
	stone.y = UNDERY;
	stone.w = 100;
	stone.h = 100;
	stone.flytime = 0;
	stone.penaltytime = 0;
	stone.xspeed = 0;
	stone.yspeed = 0;

	backgroundx = 0;

	backhandle[0] = LoadGraph("image/background1.png"); // 画像をロード
	backhandle[0] = LoadGraph("image/background1.png"); // 画像をロード
	backhandle[0] = LoadGraph("image/background1.png"); // 画像をロード
}

//終了処理
void Game_Finalize() {
	for(int i=0;i<sizeof backhandle/sizeof backhandle[0];i++)
		DeleteGraph(backhandle[i]);
}

//更新
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

//描画
void Game_Draw() {
	backgrouind_Draw();
	stone_Draw(stone);
	gauge_Draw(gauge);
	if(nowfaze==NextPoint)

		timing_Draw(stone);

}