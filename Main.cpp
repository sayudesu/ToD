#include <DxLib.h>
#include <EffekseerForDXLib.h>

#include "Scene/SceneManager.h"
#include "Util/game.h"
#include "Util/SoundFunctions.h"

#include "Save/SaveDataFunctions.h"
#include "Util/LoadGraphfunction.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
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

	// �g�p���� Direct3D �̃o�[�W������ 9EX �ɐݒ�
	SetUseDirect3DVersion(DX_DIRECT3D_9EX);
	// DirectX9���g�p����悤�ɂ���B(DirectX11����)
	// Effekseer���g�p����ɂ͕K���ݒ肷��B
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// 3D�֘A�̐ݒ�
	// Z�o�b�t�@��L���ɂ���B
	SetUseZBuffer3D(true);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���B
	// Effekseer���g�p����ꍇ�A2D�Q�[���ł�Z�o�b�t�@���g�p����B
	SetWriteZBuffer3D(true);

	// �|���S���̗��ʂ�`�悵�Ȃ�
	SetUseBackCulling(true);

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	//// �t�H���g�̃��[�h
	//LPCSTR fontPath = "Data/Fonts/Senobi-Gothic-Bold.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	//if (AddFontResourceEx(fontPath, FR_PRIVATE, NULL) > 0) 
	//{
	//	ChangeFont("���̂уS�V�b�N Bold", DX_CHARSET_DEFAULT);
	//}
	//else 
	//{
	//	// �t�H���g�Ǎ��G���[����
	//	MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	//}

	// �t�@�C���̓ǂݍ���
	SaveDataFunctions::Load();
	// �T�E���h�ǂݍ���
	SoundFunctions::Load(SaveDataFunctions::GetSoundData());
	// �摜�f�[�^�̓ǂݍ���
	LoadGraphFunction::Load();

	SceneManager* pScene = new SceneManager;
		
	pScene->Init();


	// ���_�f�[�^�̏���
	VERTEX2DSHADER Vert[6];
	Vert[0].pos = VGet(0.0f, 0.0f, 0.0f);
	Vert[1].pos = VGet(Game::kScreenWidth - 1, 0.0f, 0.0f);
	Vert[2].pos = VGet(0.0f, Game::kScreenHeight - 1, 0.0f);
	Vert[3].pos = VGet(Game::kScreenWidth - 1, Game::kScreenHeight - 1, 0.0f);
	Vert[0].dif = GetColorU8(255, 255, 255, 255);
	Vert[0].spc = GetColorU8(0, 0, 0, 0);
	Vert[0].u = 0.0f; Vert[0].v = 0.0f;
	Vert[1].u = 1.0f; Vert[1].v = 0.0f;
	Vert[2].u = 0.0f; Vert[2].v = 1.0f;
	Vert[3].u = 1.0f; Vert[3].v = 1.0f;
	Vert[0].su = 0.0f; Vert[0].sv = 0.0f;
	Vert[1].su = 1.0f; Vert[1].sv = 0.0f;
	Vert[2].su = 0.0f; Vert[2].sv = 1.0f;
	Vert[3].su = 1.0f; Vert[3].sv = 1.0f;
	Vert[0].rhw = 1.0f;
	Vert[1].rhw = 1.0f;
	Vert[2].rhw = 1.0f;
	Vert[3].rhw = 1.0f;
	Vert[4] = Vert[2];
	Vert[5] = Vert[1];

	// �s�N�Z���V�F�[�_�[�o�C�i���R�[�h�̓ǂݍ���
	int m_shader = LoadPixelShader("Shader/SamplePS.pso");
//	assert(m_shader != -1);

	int m_hScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight);

	SetUseTextureToShader(0, m_hScreen);

	SetUsePixelShader(m_shader);

	// �V�F�[�_�[���̈���
	float level = 30.0f;
	SetPSConstSF(GetConstIndexToShader("alpha", m_shader), 1.0f);
	SetPSConstSF(GetConstIndexToShader("mosLv", m_shader), level);

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();

		pScene->Update();

		// ��ʂ̃N���A
		ClearDrawScreen();

		pScene->Draw();
		if (DxLib::CheckHitKey(KEY_INPUT_1))
		{
			level -= 0.3f;
		}
		if (DxLib::CheckHitKey(KEY_INPUT_2))
		{
			level += 0.3f;
		}
		SetPSConstSF(GetConstIndexToShader("mosLv", m_shader), level);

#if false	
		SetDrawScreen(DX_SCREEN_BACK);
		DrawPrimitive2DToShader(Vert, 6, DX_PRIMTYPE_TRIANGLELIST);
		SetDrawScreen(m_hScreen);
#endif

#if _DEBUG
		DrawFormatString(0, 0, 0xffffff,  "FPS       = %1.2f",DxLib::GetFPS());
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

	//// �t�H���g�̃A�����[�h
	//if (RemoveFontResourceEx(fontPath, FR_PRIVATE, NULL)) 
	//{
	//}
	//else
	//{
	//	MessageBox(NULL, "remove failure", "", MB_OK);
	//}

	pScene->End();

	// �T�E���h���������
	SoundFunctions::UnLoad();

	// �摜�f�[�^�̃��������
	LoadGraphFunction::UnLoad();

	// Effekseer���I������B
	Effkseer_End();

	// �c�w���C�u�����g�p�̏I������
	DxLib_End();				

	// �\�t�g�̏I��
	return 0;				 
}