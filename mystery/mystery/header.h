#pragma once
#pragma once
#include <math.h>
#include "DxLib.h"
#include <iostream>
#include <string.h>

#define WINDOW_WIDE 1024
#define WINDOW_HEIGHT 600
#define _CRT_SECURE_NO_WARNINGS


typedef enum {
	eScene_Start,   //スタート画面
	eScene_Menu,    //メニュー画面
	eScene_Game,    //ゲーム画面


	eScene_None,    //無し
} eScene;

//難易度
typedef enum {
	Easy,			//簡単
	Normal,			//ふつう
	Hard,			//難しい
	Level_None
}Level;

//BGM
typedef enum{
	Bgm_Start,
	Bgm_Menu,
	Bgm_Playing,
	Bgm_Result,
	Bgm_none
}Bgm;

//SE
typedef enum {
	Start_Ok,
	Menu_Select,
	Menu_Ok,
	Gauge_Move,
	Gauge_Ok,
	Timing_Move,
	Timing_Ok,
	Finished,
	Hiscored,
	Result_Ok,
	Se_none
}Se;


typedef struct {
	int x, y, w, h;	//座標　幅　高さ
	double now;        //現在のゲージ量
	double max;		//最大のゲージ量
	double count;		//経過時間
	double speed;    //ゲージのスピード    大きいほど遅い
}Gauge_Info;

typedef struct {
	int x, y,w,h;   //座標
	double flytime;
	double penaltytime;
	double xspeed, yspeed;
	double rota;
	double size;
	int animation;
}Stone;

typedef struct {
	char name[10];
	int point;
}Ranking;

//fps.cpp
extern bool fps_Update();
extern void fps_Draw();
extern void fps_Wait();

//key.cpp
extern int key_Update();
extern int getKey(int key);

//SceneMgr.cpp
void SceneMgr_Initialize();//初期化
void SceneMgr_Finalize();//終了処理
void SceneMgr_Update();//更新
void SceneMgr_Draw();//描画

					 // 引数 nextScene にシーンを変更する
void SceneMgr_ChangeScene(eScene nextScene);

//start.cpp
void start_Initialize();//初期化
void start_Finalize();//終了処理
void start_Update();//更新
void start_Draw();//描画

//menu.cpp
void Menu_Initialize();//初期化
void Menu_Finalize();//終了処理
void Menu_Update();//更新
void Menu_Draw();//描画

//save.cpp
void save_Initialize();
void save_Input(Level lev, char *name,int point);
Ranking *save_getinfo();
void save_LoadInfo();
bool save_NewRecord(Level lev, int point);

//game.cpp
void Game_Initialize();//初期化
void Game_Finalize();//終了処理
void Game_Update();//更新
void Game_Draw();//描画

//bgm.cpp
void bgm_Initialize();
void bgm_Finalize();
void bgm_Play(Bgm se);
void bgm_Stop();

//Se.cpp
void se_Initialize();
void se_Finalize();
void se_Play(Se se);
