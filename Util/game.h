#pragma once

// �N�����̊�{�ݒ�
namespace Game
{
#if _DEBUG
	// �E�C���h�E���[�h�ݒ�
	constexpr bool kWindowMode = true;
	// �E�C���h�E��
	const char* const kTitleText = "���@�C�^���t�H�[�g���X_�f�o�b�O��";
#else
	constexpr bool kWindowMode = false;
	const char* const kTitleText = "���@�C�^���t�H�[�g���X";
#endif
	// �E�C���h�E�T�C�Y
	constexpr int kScreenWidth = 1920;
	constexpr int kScreenHeight = 1080;
	// �J���[���[�h
	constexpr int kColorDepth = 32;		// 32 or 16
	// �E�B���h�E�̃T�C�Y�ύX���ł��邩�ǂ���
	constexpr bool kWindowSizeChange = true;
	// Log���c�����ǂ���
	constexpr bool kLogText = false;
};