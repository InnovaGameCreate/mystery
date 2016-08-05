#pragma once
#pragma once
#include <math.h>
#include "DxLib.h"


typedef enum {
	eScene_Menu,    //���j���[���
	eScene_Game,    //�Q�[�����


	eScene_None,    //����
} eScene;

//SceneMgr.cpp
void SceneMgr_Initialize();//������
void SceneMgr_Finalize();//�I������
void SceneMgr_Update();//�X�V
void SceneMgr_Draw();//�`��

					 // ���� nextScene �ɃV�[����ύX����
void SceneMgr_ChangeScene(eScene nextScene);

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

				 //fps.cpp
extern bool fps_Update();
extern void fps_Draw();
extern void fps_Wait();

extern int key_Update();
extern int Keyboard_Get(int KeyCode);