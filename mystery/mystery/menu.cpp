#include "header.h"

static int mImageHandle;    //�摜�n���h���i�[�p�ϐ�


//������
void Menu_Initialize() {
	void Menu_Initialize() {
		mImageHandle = LoadGraph("Scene_Menu.png");    //�摜�̃��[�h
	}

}

//�I������
void Menu_Finalize() {
	void Menu_Finalize() {
		DeleteGraph(mImageHandle);    //�摜�̉��
	}

}

//�X�V
void Menu_Update() {
	
}
 //�`��
void Menu_Draw() {

	int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
		ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

																			 // ���j���[���ڗv�f��3���
		MenuElement_t MenuElement[5] = {
			{ 0, 100, "����",GetColor(255,255,255) },
			{ 20, 150, "����",GetColor(255,255,255) },
			{ 20, 200, "�㋉",GetColor(255,255,255) },
			
		};
		int SelectNum = 0; // ���݂̑I��ԍ�

	if (Key[KEY_INPUT_DOWN] == 1) { // ���L�[�������ꂽ�u�Ԃ�������

		SelectNum = (SelectNum + 1) % 3; // ���݂̑I�����ڂ�����ɂ��炷(���[�v����)

		for (int i = 0; i<3; i++) {   // ���j���[���ڐ��ł���3���[�v����
			if (Key[KEY_INPUT_UP] == 1) { // ��L�[�������ꂽ�u�Ԃ�������

				SelectNum = (SelectNum + 2) % 3; // ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)
			}

			if (i == SelectNum) {          // ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�
				MenuElement[i].x = 0; // ���W��0�ɂ���
			}
			else {                       // ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�
				MenuElement[i].x = 20;// ���W��20�ɂ���
			}
		}
	}

}