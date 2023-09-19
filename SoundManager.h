#pragma once
#include <unordered_map>
#include <string>
#include <DxLib.h>

/// <summary>
/// �T�E���h�̊Ǘ����s���V���O���g���N���X
/// </summary>
class SoundManager
{
public:
	// �f�X�g���N�^
	~SoundManager();

	// SoundManager�̗B��̃C���X�^���X��Ԃ�
	static SoundManager& GetInstance();

	// �t�@�C������T�E���h�̃f�[�^��ǂݎ���ăf�[�^�e�[�u���Ɋi�[
	void LoadAndSaveSoundFileData();

	// �w���2DSE��炷
	void Play(std::string fileName);

	// �w���3DSE��炷
	void Play3D(std::string fileName, VECTOR soundPos, float soundRadius);

	// �w���BGM��炷
	void PlayBGM(std::string fileName);

	// �w��̃T�E���h���Đ������`�F�b�N
	bool PlayingCheckSound(std::string fileName);

	// ����̃T�E���h���~�߂�
	void StopSound(std::string fileName);

	// ���ׂẴT�E���h���~�߂�
	void StopAllSound();

	// ���ʒ���
	void SetVolume(std::string fileName, int volume);

	// 3D�T�E���h�̃��X�i�[�̈ʒu�ƃ��X�i�[�̑O���ʒu��ݒ肷��
	void Set3DSoundListenerPosAndFrontPos_UpVecY(VECTOR pos, VECTOR angle);
private:
	// �T�E���h�̎��
	enum SoundType : int
	{
		BGM,
		SE2D,
		SE3D,
	};
	// �T�E���h�̃f�[�^�̎��
	enum SoundDataType : int
	{
		FILE_NAME,
		EXTENSION,
		SOUND_TYPE,
		VOLUM_RATE,
	};
private:
	// �T�E���h�̃f�[�^
	struct SoundData
	{
		SoundType type;		// BGM��3D��SE��2D��SE��
		std::string extension;	// �T�E���h�t�@�C���̊g���q
		float volumeRate;	// �{�����[������
		int handle;			// �n���h��
	};
private:
	// �R���X�g���N�^(�V���O���g���p�^�[���Ȃ̂�private�ɒu��)
	SoundManager();

	// �R�s�[��������֎~����
	SoundManager(const SoundManager&) = delete;			// �R�s�[�R���X�g���N�^
	void operator = (const SoundManager&) = delete;		// ������֎~

	// 2DSE�T�E���h�̃��[�h
	void LoadSoundFile2D(std::string fileName, std::string ext);

	// 3DSE�T�E���h�̃��[�h
	void LoadSoundFile3D(std::string fileName, std::string ext);
private:
	// ���[�h�����T�E���h�̃t�@�C�����ƃn���h��
	std::unordered_map<std::string, SoundData> soundNameAndHandleTable_;
};


