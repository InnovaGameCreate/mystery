#pragma once
#pragma once
#include <math.h>
#include "DxLib.h"


typedef enum { 
	eScene_Start,   //�X�^�[�g���
	eScene_Menu,    //���j���[���
	eScene_Game,    //�Q�[�����


	eScene_None,    //����
} eScene;
//fps.cpp
extern bool fps_Update();
extern void fps_Draw();
extern void fps_Wait();

//key.cpp
extern int key_Update();
extern int getKey(int key);

//SceneMgr.cpp
void SceneMgr_Initialize();//������
void SceneMgr_Finalize();//�I������
void SceneMgr_Update();//�X�V
void SceneMgr_Draw();//�`��

					 // ���� nextScene �ɃV�[����ύX����
void SceneMgr_ChangeScene(eScene nextScene);

//start.cpp
void start_Initialize();//������
void start_Finalize();//�I������
void start_Update();//�X�V
void start_Draw();//�`��

//menu.cpp
void Menu_Initialize();//������
void Menu_Finalize();//�I������
void Menu_Update();//�X�V
void Menu_Draw();//�`��

//game.cpp
void Game_Initialize();//������
void Game_Finalize();//�I������
void Game_Update();//�X�V
void Game_Draw();//�`��



