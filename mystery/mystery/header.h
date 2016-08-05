#pragma once
#pragma once
#include <math.h>
#include "DxLib.h"


typedef enum {
	eScene_Menu,    //メニュー画面
	eScene_Game,    //ゲーム画面


	eScene_None,    //無し
} eScene;

//SceneMgr.cpp
void SceneMgr_Initialize();//初期化
void SceneMgr_Finalize();//終了処理
void SceneMgr_Update();//更新
void SceneMgr_Draw();//描画

					 // 引数 nextScene にシーンを変更する
void SceneMgr_ChangeScene(eScene nextScene);

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

				 //fps.cpp
extern bool fps_Update();
extern void fps_Draw();
extern void fps_Wait();

extern int key_Update();
extern int Keyboard_Get(int KeyCode);