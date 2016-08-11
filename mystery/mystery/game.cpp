#include "header.h"
#define MAXX 11339		//背景の右端
#define MINX 0			//背景の左端
#define STONEX 100      //石の初期x
#define FLYTIME 3		//飛ぶ時間
#define UPPOWER -18        //上方向の初期値
double const DOWNPOWER = 0.5;   //重力
#define UNDERY 350      //着地面
#define MOVECAMEX WINDOW_WIDE/2-20     //カメラの移動開始の石のx地点
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

static Level nowlevel =Easy;

static int backhandle;
static int flyhandle[3];

static int backgroundx;     //背景移動補正

static double timinglimit = 200;  //着地面までの猶予幅
static double gameoverlimit;             //ゲームオーバーまでの幅
static int minusx;//着水時のx速度の減少
static double timingradi[3];

static int sele;

int Font00,Font01;

void draw_CircleLine(int x, int y, double radi, double size, int color1, int color2) {
	DrawCircle(200, 200, radi, color1, TRUE);
	DrawCircle(200, 200, radi - size, color2, TRUE);
}
//スピードの決定
void decindeSpeed(Stone *samp, Gauge_Info gau) {
	samp->xspeed = 1 * (gau.now / gau.max) * 10+3;
	samp->yspeed = UPPOWER;
}

//ゲージ計算
void gauge_Update(Gauge_Info *samp) {
	if (getKey(KEY_INPUT_RETURN) == 1) {
		decindeSpeed(&stone, gauge);
		nowfaze = Fly;
	}
	samp->count += samp->speed;
	samp->now = (int)samp->count % 101;

}
//ゲージ描画
void gauge_Draw(Gauge_Info samp) {
	int  Red = GetColor(255, 0, 0); // 赤色の値を取得

	DrawBox(samp.x, samp.y, samp.x + samp.w, samp.y + samp.h, Red, FALSE);   // 四角形を描画
	DrawBox(samp.x, samp.y, samp.x + samp.w*(samp.now / samp.max), samp.y + samp.h, Red, TRUE);   // 四角形を描画(塗りつぶし)

}

//着地時のタイミング計算
void timingUpdate(Stone *samp) {
	gameoverlimit = UNDERY + timinglimit - samp->y;

	int sa = (UNDERY < samp->y) ? samp->y - UNDERY : UNDERY - samp->y;
	timingradi[0] = TIMINGRADI;
	timingradi[1] = gameoverlimit / (timinglimit * 2);
	timingradi[2] = 50;
	if (gameoverlimit <= 0) {
		nowfaze = Result;
		return;
	}

	if (getKey(KEY_INPUT_RETURN) == 1) {
		nowfaze = Fly;
		samp->yspeed = UPPOWER;
		samp->xspeed -= 0.1*sa;
		if (samp->xspeed <= 1) {
		nowfaze = Result;
		if (samp->yspeed < 0)
			samp->yspeed = 0;
	}
	}
}
//着地時のタイミング描画
void timing_Draw(int x, int y) {
	int blue = GetColor(0, 0, 255);
	int red = GetColor(255, 0, 0);
	int purple = GetColor(255, 0, 255);

	DrawRotaGraph(x, y, 1, 0, flyhandle[0], TRUE);
	DrawRotaGraph(x, y, 0.55, 0, flyhandle[1], TRUE);
	DrawRotaGraph(x, y, timingradi[1], 0, flyhandle[2], TRUE);
}
//背景計算
void backgrouind_Update(int x) {
	backgroundx -= x;
}

//背景描画
void backgrouind_Draw() {
	DrawRotaGraph((MAXX + MINX) / 2 + backgroundx, WINDOW_HEIGHT / 2, 1, 0, backhandle, TRUE);
}

//飛ぶ計算
void fry_Update(Stone *samp, Gauge_Info sam) {
	if (MOVECAMEX > samp->x)
		samp->x += samp->xspeed;
	else
		backgrouind_Update(samp->xspeed);
	samp->y += samp->yspeed;

	samp->yspeed += DOWNPOWER;

	if (nowfaze == Fly&&UNDERY - timinglimit < samp->y&&samp->yspeed>0)
		nowfaze = NextPoint;
}

//石描画
void stone_Draw(Stone samp) {
	if (samp.y > UNDERY&&nowfaze==Result)
		return;
	int  Green = GetColor(0, 255, 0); // 赤色の値を取得
	DrawBox(samp.x, samp.y, samp.x + samp.w, samp.y + samp.h, Green, TRUE);
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
	gauge.speed = 3;

	//石初期値
	stone.x = STONEX;
	stone.y = UNDERY;
	stone.w = 100;
	stone.h = 100;
	stone.flytime = 0;
	stone.penaltytime = 0;
	stone.xspeed = 0;
	stone.yspeed = 0;

	backgroundx = 0;

	sele = 0;

	flyhandle[0] = LoadGraph("image/timing_back.png"); // 画像をロード
	flyhandle[1] = LoadGraph("image/good_timing.png"); // 画像をロード
	flyhandle[2] = LoadGraph("image/maintiming.png"); // 画像をロード

	Font00 = CreateFontToHandle("メイリオ", 70, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"メイリオ"  の30pt,太さ3のフォントを作成
	Font01 = CreateFontToHandle("メイリオ", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"メイリオ"  の30pt,太さ3のフォントを作成
	switch (nowlevel) {
	case Easy:
		backhandle = LoadGraph("image/background_easy.png"); // 画像をロード
		minusx = 1;
		break;
	case Normal:
		backhandle = LoadGraph("image/background_normal.png"); // 画像をロード
		minusx = 5;
		break;
	case Hard:
		backhandle = LoadGraph("image/background_hard.png"); // 画像をロード
		minusx = 10;
		break;
	}
}

//終了処理
void Game_Finalize() {
	DeleteGraph(backhandle);
	for(int i=0;i<sizeof(flyhandle)/sizeof(flyhandle[0]);i++)
	DeleteGraph(flyhandle[i]);
	DeleteFontToHandle(Font00);
	DeleteFontToHandle(Font01);
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
		if (getKey(KEY_INPUT_DOWN) == 1 && sele == 1)
			sele = 2;
		if (getKey(KEY_INPUT_UP) == 1 && sele == 2)
			sele = 1;
		if (getKey(KEY_INPUT_RETURN)==1 )
			
			switch (sele) {
			case 0:
				sele = 1;
				break;
			case 1:
				SceneMgr_ChangeScene(eScene_Game);
				break;
			case 2:
				//(eScene_Menu);
				break;
			}
		

		stone.y += stone.yspeed;
		stone.yspeed += DOWNPOWER;
		break;
	
	}

}


void info_Draw() {
	DrawFormatStringToHandle(100, 10, GetColor(0, 255, 0), Font00, "%d m",(stone.x-STONEX-backgroundx)/20);

}

//描画
void Game_Draw() {
	int red = GetColor(255, 0, 0);
	int white = GetColor(255, 255, 255);
	backgrouind_Draw(); 
	stone_Draw(stone);
	info_Draw();
	switch (nowfaze) {
	case Gauge:
		gauge_Draw(gauge);

		break;
	case NextPoint:
		timing_Draw(200, 200);
		break;
	case Result:
		if (stone.y > UNDERY&&nowfaze == Result) {
			DrawStringToHandle(100, 100, "ランキング", GetColor(255, 255, 255), Font01);
			switch (sele)
			{
			case 0:
				
				break;
			case 1:
				DrawStringToHandle(WINDOW_WIDE - 300, WINDOW_HEIGHT - 200, "もう一度", red, Font01);
				DrawStringToHandle(WINDOW_WIDE - 300, WINDOW_HEIGHT - 100, "難易度選択", white, Font01);
				break;
			case 2:
				DrawStringToHandle(WINDOW_WIDE - 300, WINDOW_HEIGHT - 200, "もう一度", white, Font01);
				DrawStringToHandle(WINDOW_WIDE - 300, WINDOW_HEIGHT - 100, "難易度選択", red, Font01);
				break;
			default:
				break;
			}
		

		}
		break;
	}
	

}