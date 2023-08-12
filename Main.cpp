#include <DxLib.h>
#include <EffekseerForDXLib.h>

#include "Scene/SceneManager.h"
#include "Util/game.h"
#include "Util/SoundFunctions.h"

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

	// �c�w���C�u��������������
	// �G���[���N�����璼���ɏI��
	if (DxLib_Init() == -1)		
	{
		return -1;			
	}

	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effkseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}

	// DirectX9���g�p����悤�ɂ���B(DirectX11����)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
//	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// Z�o�b�t�@��L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetUseZBuffer3D(TRUE);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(TRUE);

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

	// �T�E���h�ǂݍ���
	SoundFunctions::Load();

	SceneManager* pScene = new SceneManager;

	pScene->Init();


	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		pScene->Update();

		pScene->Draw();
#if _DEBUG
		DrawFormatString(0, 0, 0xffffff,  "FPS       = %2f",DxLib::GetFPS());
		DrawFormatString(0, 10, 0xffffff, "DrawColl  = %d"  ,DxLib::GetDrawCallCount());
#endif
		// ����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	// �t�H���g�̃A�����[�h
	if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) 
	{
	}
	else
	{
		MessageBox(NULL, "remove failure", "", MB_OK);
	}

	pScene->End();

	// �T�E���h���������
	SoundFunctions::UnLoad();

	// Effekseer���I������B
	Effkseer_End();

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();				

	// �\�t�g�̏I��
	return 0;				 
}