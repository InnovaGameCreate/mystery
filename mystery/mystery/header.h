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
	eScene_Start,   //�X�^�[�g���
	eScene_Menu,    //���j���[���
	eScene_Game,    //�Q�[�����


	eScene_None,    //����
} eScene;

//��Փx
typedef enum {
	Easy,			//�ȒP
	Normal,			//�ӂ�
	Hard,			//���
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
	int x, y, w, h;	//���W�@���@����
	double now;        //���݂̃Q�[�W��
	double max;		//�ő�̃Q�[�W��
	double count;		//�o�ߎ���
	double speed;    //�Q�[�W�̃X�s�[�h    �傫���قǒx��
}Gauge_Info;

typedef struct {
	int x, y,w,h;   //���W
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

//save.cpp
void save_Initialize();
void save_Input(Level lev, char *name,int point);
Ranking *save_getinfo();
void save_LoadInfo();
bool save_NewRecord(Level lev, int point);

//game.cpp
void Game_Initialize();//������
void Game_Finalize();//�I������
void Game_Update();//�X�V
void Game_Draw();//�`��

//bgm.cpp
void bgm_Initialize();
void bgm_Finalize();
void bgm_Play(Bgm se);
void bgm_Stop();

//Se.cpp
void se_Initialize();
void se_Finalize();
void se_Play(Se se);
