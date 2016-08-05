#pragma once
#pragma once
#include <math.h>
#include "DxLib.h"
#define WINDOW_WIDE 1024
#define WINDOW_HEIGHT 600

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
	Hard			//難しい
}Level;


typedef struct {
	int x, y, w, h;	//座標　幅　高さ
	double now;        //現在のゲージ量
	int max;		//最大のゲージ量
	int count;		//経過時間
	int speed;    //ゲージのスピード    大きいほど遅い
}Gauge_Info;

typedef struct {
	int x, y,w,h;   //座標
	double flytime;
	double penaltytime;
	double xspeed, yspeed;
}Stone;

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

//game.cpp
void Game_Initialize();//初期化
void Game_Finalize();//終了処理
void Game_Update();//更新
void Game_Draw();//描画



extern int key_Update();
extern int Keyboard_Get(int KeyCode);