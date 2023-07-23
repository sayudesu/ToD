#include <DxLib.h>

#include "game.h"
#include "SceneManager.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// �E�B���h�̃T�C�Y��ύX�ł��邩�ǂ���
	SetWindowSizeChangeEnableFlag(Game::kWindowSizeChange);
	// Log.txt�Ń��O���c�����ǂ���
	SetOutApplicationLogValidFlag(Game::kLogText);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// �t�H���g�̃��[�h
	LPCSTR fontPath = "Data/Fonts/Senobi-Gothic-Bold.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) 
	{
		ChangeFont("���̂уS�V�b�N Bold", DX_CHARSET_DEFAULT);
	}
	else 
	{
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}

	SceneManager* pScene = new SceneManager;

	pScene->Init();

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		pScene->Update();

		pScene->Draw();

		// ����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	pScene->End();

	// �t�H���g�̃A�����[�h
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) 
	{
	}
	else
	{
		MessageBox(NULL, "remove failure", "", MB_OK);
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}