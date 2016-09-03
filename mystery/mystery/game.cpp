#include "header.h"
#define MAXX 15000		//�w�i�̉E�[
#define MINX 0			//�w�i�̍��[
#define STONEX 100      //�΂̏���x
#define FLYTIME 3		//��Ԏ���
#define UPPOWER -18        //������̏����l
double const DOWNPOWER = 0.5;   //�d��
#define UNDERY 500      //���n��
#define MOVECAMEX WINDOW_WIDE/2-20     //�J�����̈ړ��J�n�̐΂�x�n�_
#define TIMINGRADI 100    //�^�C�~���O�Q�[�W�̔��a
#define STONEFRAME 3
static int InputHandle;
static char name[10];

typedef enum {
	Gauge,
	Fly,
	NextPoint,
	Result
}GameFaze;

static Gauge_Info gauge;		//�Q�[�W

static Stone stone;    //��

static GameFaze nowfaze;

static Level nowlevel =Easy;

static int backgroundhandle;
static int flyhandle[3];
static int stonehandle;
static int gaugehandle[3];
static int watersplash[3];
static int gaugemaskhandle;
static int numberhandle[11];
static int rankhandle[3];
static int backhandle;

static double timingrota[3];

static int maskini;

static int backgroundx;     //�w�i�ړ��␳

static double timinglimit = 200; 
//���n�ʂ܂ł̗P�\��
static double gameoverlimit;             //�Q�[���I�[�o�[�܂ł̕�
static int minusx;//��������x���x�̌���
static double timingradi[3];

static int sele;

static int Font00,Font01,Font02;

void draw_CircleLine(int x, int y, double radi, double size, int color1, int color2) {
	DrawCircle(200, 200, radi, color1, TRUE);
	DrawCircle(200, 200, radi - size, color2, TRUE);
}
//�X�s�[�h�̌���
void decindeSpeed(Stone *samp, Gauge_Info gau) {
	samp->xspeed = 1 * (gau.now / gau.max) * 10+3;
	samp->yspeed = UPPOWER;
}

//�Q�[�W�v�Z
void gauge_Update(Gauge_Info *samp) {
	if (getKey(KEY_INPUT_RETURN) == 1) {
		se_Play(Gauge_Ok);
		decindeSpeed(&stone, gauge);
		nowfaze = Fly;
	}
	if(samp->now<3)
		se_Play(Gauge_Move);
	samp->count += samp->speed;
	samp->now = (int)samp->count % 101;

}
//�Q�[�W�`��
void gauge_Draw(Gauge_Info samp) {
	int  Red = GetColor(255, 0, 0); // �ԐF�̒l���擾

	//DrawBox(samp.x, samp.y, samp.x + samp.w, samp.y + samp.h, Red, FALSE);   // �l�p�`��`��
	//DrawBox(samp.x, samp.y, samp.x + samp.w*(samp.now / samp.max), samp.y + samp.h, Red, TRUE);   // �l�p�`��`��(�h��Ԃ�)
	//DrawRotaGraph(samp.x, samp.y, 1, 0, gaugehandle[0], TRUE);
	DrawRotaGraph(samp.x, samp.y, 1, 0, gaugehandle[2], TRUE);
	CreateMaskScreen();
	DrawMask(0,0, maskini, DX_MASKTRANS_BLACK);
	DrawMask(samp.x-200+ samp.w*(samp.now / samp.max)- samp.w, samp.y-50, gaugemaskhandle, DX_MASKTRANS_WHITE);
	
	DrawRotaGraph(samp.x, samp.y, 1, 0, gaugehandle[0], TRUE);


	DeleteMaskScreen();
	DrawRotaGraph(samp.x, samp.y, 1, 0, gaugehandle[1], TRUE);
}
void result_Initialize() {
	// �L�[���̓n���h�������(�L�����Z���Ȃ��S�p�����L�萔�l���͂���Ȃ�)
	InputHandle = MakeKeyInput(8, FALSE, FALSE, FALSE);
	// �쐬�����L�[���̓n���h�����A�N�e�B�u�ɂ���
	SetActiveKeyInput(InputHandle);


}
//���n���̃^�C�~���O�v�Z
void timingUpdate(Stone *samp) {
	gameoverlimit = UNDERY + timinglimit - samp->y;

	int sa = (UNDERY < samp->y) ? samp->y - UNDERY : UNDERY - samp->y;
	timingradi[0] = TIMINGRADI;
	timingradi[1] = gameoverlimit / (timinglimit * 2);
	timingradi[2] = 50;

	timingrota[0]-=0.1;
	timingrota[1]++;

	if (gameoverlimit <= 0) {//�Q�[���I�[�o�[
		result_Initialize();
		nowfaze = Result;
		bgm_Stop();
		bgm_Play(Bgm_Result);
		return;
	}

	if (getKey(KEY_INPUT_RETURN) == 1) {
		se_Play(Timing_Ok);
		nowfaze = Fly;
		samp->yspeed = UPPOWER;
		samp->xspeed -= 0.1*sa;
		if (stone.animation==0)
		stone.animation++;
		if (samp->xspeed <= 1) {//�Q�[���I�[�o�[
			result_Initialize();
		nowfaze = Result;
		bgm_Stop();
		bgm_Play(Bgm_Result);

		if (samp->yspeed < 0)
			samp->yspeed = 0;
	}
	}
	
}
//���n���̃^�C�~���O�`��
void timing_Draw(int x, int y) {
	int blue = GetColor(0, 0, 255);
	int red = GetColor(255, 0, 0);
	int purple = GetColor(255, 0, 255);

	DrawRotaGraph(x, y, 1, 0, flyhandle[0], TRUE);
	DrawRotaGraph(x, y, 0.50,0, flyhandle[1], TRUE);
	DrawRotaGraph(x, y, timingradi[1], timingrota[0], flyhandle[2], TRUE);
}
//�w�i�v�Z
void backgrouind_Update(int x) {
	backgroundx -= x;
}

//�w�i�`��
void backgrouind_Draw() {
	DrawRotaGraph((MAXX + MINX) / 2 + backgroundx, WINDOW_HEIGHT / 2, 1, 0, backgroundhandle, TRUE);
}


//��Ԍv�Z
void fry_Update(Stone *samp, Gauge_Info sam) {
	if (MOVECAMEX > samp->x)
		samp->x += samp->xspeed;
	else
		backgrouind_Update(samp->xspeed);
	samp->y += samp->yspeed;

	samp->yspeed += DOWNPOWER;
	samp->rota += 0.03*samp->xspeed;

	if (nowfaze == Fly&&UNDERY - timinglimit < samp->y&&samp->yspeed>0)
		nowfaze = NextPoint;
}

//�Ε`��
void stone_Draw(Stone samp) {
	if (samp.y > UNDERY&&nowfaze == Result)
		return;
	if (samp.animation != 0) {
	if (samp.animation < STONEFRAME)
		DrawRotaGraph(samp.x, samp.y, 1, 0, watersplash[0], TRUE);
	else if (samp.animation < STONEFRAME*2)
		DrawRotaGraph(samp.x, samp.y, 1, 0, watersplash[1], TRUE);
	else if (samp.animation < STONEFRAME*3)
		DrawRotaGraph(samp.x, samp.y, 1, 0, watersplash[2], TRUE);
}
	
	DrawRotaGraph(samp.x, samp.y, samp.size, samp.rota, stonehandle, TRUE);
}

//������
void Game_Initialize() {

	bgm_Play(Bgm_Playing);

	nowfaze = Gauge;

	//�Q�[�W�����l
	gauge.x = 300;
	gauge.y = 250;
	gauge.w = 500;
	gauge.h = 100;
	gauge.now = 0;
	gauge.max = 100;
	gauge.count = 0;
	gauge.speed = 3;
	for(int i=0;i<sizeof (timingrota)/sizeof(timingrota[0]);i++)
	timingrota[i] = 0;

	//�Ώ����l
	stone.x = STONEX;
	stone.y = UNDERY;
	stone.w = 100;
	stone.h = 100;
	stone.flytime = 0;
	stone.penaltytime = 0;
	stone.xspeed = 0;
	stone.yspeed = 0;
	stone.size = 0.8;
	stone.rota = 0;
	stone.animation = 0;
	timingradi[1] = 0;

	backgroundx = 0;

	sele = 0;

	nowlevel = get_nowsel_level();

	flyhandle[0] = LoadGraph("image/timing_back.png"); // �摜�����[�h
	flyhandle[1] = LoadGraph("image/good_timing.png"); // �摜�����[�h
	flyhandle[2] = LoadGraph("image/maintiming.png"); // �摜�����[�h

	gaugehandle[0] = LoadGraph("image/gauge.png"); // �摜�����[�h
	gaugehandle[1] = LoadGraph("image/gauge_frame.png"); // �摜�����[�h
	gaugehandle[2] = LoadGraph("image/gaugeback.png"); // �摜�����[�h
	

	rankhandle[0] = LoadGraph("image/ranking.png"); // �摜�����[�h
	rankhandle[1] = LoadGraph("image/inputname.png"); // �摜�����[�h
	rankhandle[2] = LoadGraph("image/hiscore.png"); // �摜�����[�h

	backhandle = LoadGraph("image/back.png"); // �摜�����[�h

	LoadDivGraph("image/watersplash.png", 3, 3, 1, 200, 200, watersplash); // �摜�̕����ǂݍ���
	LoadDivGraph("image/number.png", 11, 6, 2, 150, 150, numberhandle); // �摜�̕����ǂݍ���

	gaugemaskhandle= LoadMask("image/gauge_mask.png");

	maskini= LoadMask("image/maskini.png");

	Font00 = CreateFontToHandle("HGRPP1", 25, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"���C���I"  ��30pt,����3�̃t�H���g���쐬
	Font01 = CreateFontToHandle("HGRPP1", 40, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"���C���I"  ��30pt,����3�̃t�H���g���쐬
	Font02 = CreateFontToHandle("HGRPP1", 30, 3, DX_FONTTYPE_ANTIALIASING_EDGE);//"���C���I"  ��30pt,����3��
	switch (nowlevel) {
	case Easy:
		backgroundhandle = LoadGraph("image/background_easy.png"); // �摜�����[�h
		stonehandle= LoadGraph("image/stone_easy.png");
		minusx = 1;
		break;
	case Normal:
		backgroundhandle = LoadGraph("image/background_normal.png"); // �摜�����[�h
		stonehandle = LoadGraph("image/stone_normal.png");
		minusx = 5;
		break;
	case Hard:
		backgroundhandle = LoadGraph("image/background_hard.png"); // �摜�����[�h
		stonehandle = LoadGraph("image/stone_hard.png");
		minusx = 10;
		break;
	}
	info_Initialize();
	save_LoadInfo();

	for (int i = 0 ; i < sizeof(name) / sizeof(name[0]); i++)
		name[i] = '\n';
}

//�I������
void Game_Finalize() {
	DeleteGraph(backgroundhandle);
	for(int i=0;i<sizeof(flyhandle)/sizeof(flyhandle[0]);i++)
	DeleteGraph(flyhandle[i]);
	for (int i = 0; i<sizeof(gaugehandle) / sizeof(gaugehandle[0]); i++)
		DeleteGraph(gaugehandle[i]);
	for (int i = 0; i<sizeof(watersplash) / sizeof(watersplash[0]); i++)
		DeleteGraph(watersplash[i]);
	for (int i = 0; i<sizeof(numberhandle) / sizeof(numberhandle[0]); i++)
		DeleteGraph(numberhandle[i]);
	for (int i = 0; i<sizeof(rankhandle) / sizeof(rankhandle[0]); i++)
		DeleteGraph(rankhandle[i]);
	DeleteGraph(stonehandle);
	DeleteGraph(backhandle);
	DeleteFontToHandle(Font00);
	DeleteFontToHandle(Font01);
	DeleteFontToHandle(Font02);

	DeleteKeyInput(InputHandle);

	DeleteMask(maskini);
		DeleteMask(gaugemaskhandle);


		bgm_Stop();
}


//�X�V
void Game_Update() {

	if (stone.animation)
		stone.animation = (stone.animation > STONEFRAME * 3) ? 0 : stone.animation + 1;
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
		
			switch (sele) {
			case 0:
				
				if(save_NewRecord(nowlevel, (int)((stone.x - STONEX - backgroundx) / 20))==true)
				GetKeyInputString(name, InputHandle);
				
				if (CheckKeyInput(InputHandle) != 0) {
					if (getKey(KEY_INPUT_RETURN) == 1) {
						if (save_NewRecord(nowlevel, (int)((stone.x - STONEX - backgroundx) / 20)) == true)
						if (name[0] == '\0') {
							SetActiveKeyInput(InputHandle);
							break;
						}
						sele = 1;
						se_Play(Hiscored);
						if (save_NewRecord(nowlevel, (int)((stone.x - STONEX - backgroundx) / 20)) == true)
						save_Input(nowlevel,name, (int)((stone.x - STONEX - backgroundx) / 20));
					}
		}
				
			
				break;
			case 1:
				if (getKey(KEY_INPUT_RETURN) == 1) {
					SceneMgr_ChangeScene(eScene_Game);
					se_Play(Result_Ok);
				}
				break;
			case 2:
				if (getKey(KEY_INPUT_RETURN) == 1) {
					SceneMgr_ChangeScene(eScene_Menu);
					se_Play(Result_Ok);
				}
				break;
			}
		

		stone.y += stone.yspeed;
		stone.yspeed += DOWNPOWER;
		break;
	
	}

}


void info_Draw() {
	int hundred = (stone.x - STONEX - backgroundx) / 20 / 100;
	int ten = (stone.x - STONEX - backgroundx) / 20 % 100 / 10;
	int one = (stone.x - STONEX - backgroundx) / 20 % 10;
	
	if(hundred!=0)
	DrawRotaGraph(100, 60, 1, 0, numberhandle[hundred], TRUE);
	if (hundred>0||ten!=0)
	DrawRotaGraph(180, 60, 1, 0, numberhandle[ten], TRUE);
	DrawRotaGraph(260, 60, 1, 0, numberhandle[one], TRUE);
	DrawRotaGraph(380, 60, 1, 0, numberhandle[10], TRUE);
}

//�`��
void Game_Draw() {
	int red = GetColor(255, 0, 0);
	int white = GetColor(255, 255, 255);
	backgrouind_Draw(); 
	stone_Draw(stone);
	info_Draw();
	
	switch (nowfaze) {
	case Gauge:
		gauge_Draw(gauge);
		DrawStringToHandle(100, WINDOW_HEIGHT - 50, "ENTER�L�[�F����", GetColor(255, 255, 255), Font01);
		break;
	case Fly:
		timing_Draw(200, 280);
		DrawStringToHandle(100, WINDOW_HEIGHT - 50, "ENTER�L�[�F����", GetColor(255, 255, 255), Font01);
		break;
	case NextPoint:
		timing_Draw(200, 280);
		DrawStringToHandle(100, WINDOW_HEIGHT - 50, "ENTER�L�[�F����", GetColor(255, 255, 255), Font01);
		break;
	case Result:
		
		
		
		if (stone.y > UNDERY) {
			DrawRotaGraph(300, 300, 1, 0, rankhandle[0], TRUE);
			DrawStringToHandle(120, 170, "�����L���O", GetColor(255, 255, 255), Font01);
			switch (nowlevel)
			{
			case Easy:
				DrawStringToHandle(330, 170, "�`�����`", GetColor(255, 255, 255), Font01);
				break;
			case Normal:
				DrawStringToHandle(330, 170, "�`�����`", GetColor(255, 255, 255), Font01);
				break;
			case Hard:
				DrawStringToHandle(330, 170, "�`�㋉�`", GetColor(255, 255, 255), Font01);
				break;
			default:
				break;
			}


			DrawFormatStringToHandle(180, 255, GetColor(255, 255, 255), Font01, "%s", save_getinfo()[nowlevel * 3].name);
			DrawFormatStringToHandle(180, 325, GetColor(255, 255, 255), Font01, "%s", save_getinfo()[nowlevel * 3 + 1].name);
			DrawFormatStringToHandle(180, 395, GetColor(255, 255, 255), Font01, "%s", save_getinfo()[nowlevel * 3 + 2].name);

			DrawFormatStringToHandle(380, 255, GetColor(255, 255, 255), Font01, "%d m", save_getinfo()[nowlevel*3].point);
			DrawFormatStringToHandle(380, 325, GetColor(255, 255, 255), Font01, "%d m", save_getinfo()[nowlevel * 3+1].point);
			DrawFormatStringToHandle(380, 395, GetColor(255, 255, 255), Font01, "%d m", save_getinfo()[nowlevel * 3+2].point);
			switch (sele)
			{
			case 0:
				if (save_NewRecord(nowlevel, (int)((stone.x - STONEX - backgroundx) / 20)) == true) {
					DrawStringToHandle(100, WINDOW_HEIGHT - 50, "BACKSPACE�L�[�F1���폜  ENTER�L�[�F����", GetColor(255, 255, 255), Font02);
					DrawRotaGraph(750,300, 1, 0, rankhandle[1], TRUE);
					DrawRotaGraph(660, 160, 1, -0.3, rankhandle[2], TRUE);

					DrawStringToHandle(600, 210, "���O����͂��Ă�������", GetColor(255, 255, 255), Font00);
					DrawStringToHandle(600, 250, "(�p����8�����ȓ�)", GetColor(255, 255, 255), Font00);
					DrawStringToHandle(600, 290, "(����4�����ȓ�)", GetColor(255, 255, 255), Font00);
					DrawFormatStringToHandle(700, 350, GetColor(255, 255, 255), Font00, "%s", name);
				}
				break;
			case 1:
				DrawRotaGraph(WINDOW_WIDE - 200, WINDOW_HEIGHT - 150, 1.5, 0, backhandle, TRUE);
				DrawStringToHandle(100, WINDOW_HEIGHT - 50, "�㉺�����L�[�F�I��  ENTER�L�[�F����", GetColor(255, 255, 255), Font02);
				DrawStringToHandle(WINDOW_WIDE - 300, WINDOW_HEIGHT - 200, "������x", red, Font01);
				DrawStringToHandle(WINDOW_WIDE - 300, WINDOW_HEIGHT - 100, "��Փx�I��", white, Font01);
				break;
			case 2:
			
				DrawRotaGraph(WINDOW_WIDE - 200, WINDOW_HEIGHT - 150, 1.5, 0, backhandle, TRUE);
				DrawStringToHandle(100, WINDOW_HEIGHT - 50, "�㉺�����L�[�F�I��  ENTER�L�[�F����", GetColor(255, 255, 255), Font02);
				DrawStringToHandle(WINDOW_WIDE - 300, WINDOW_HEIGHT - 200, "������x", white, Font01);
				DrawStringToHandle(WINDOW_WIDE - 300, WINDOW_HEIGHT - 100, "��Փx�I��", red, Font01);
				break;
			default:
				break;
			}
			
			
		

		}
		break;
	}
	

}