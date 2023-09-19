#include "SoundManager.h"
#include "Util/Game.h"
//#include "SaveData.h"
#include <cassert>
#include <fstream>
#include <sstream>
#include <cassert>

namespace
{
	// �T�E���h�̃t�@�C���p�X
	const std::string data_file_path = "Data/Sound/";

	// TODO:�������̊֐��ʂ̂Ƃ���ł��g������t�@�C������Ĉڂ�
	/// <summary>
	/// ���������؂�(�����̕�����ɕϊ�)
	/// </summary>
	/// <param name="input">��؂肽��������</param>
	/// <param name="delimiter">���������؂镶��</param>
	/// <returns>��؂���������</returns>
	std::vector<std::string> Split(std::string& input, char delimiter)
	{
		std::istringstream stream(input);	// string��getline�Ŏg����f�[�^�ɕϊ�
		std::string field;					// ��������������1�����i�[����
		std::vector<std::string> result;			// ������̕�����̔z��
		while (getline(stream, field, delimiter))
		{
			result.push_back(field);
		}
		return result;
	}
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
SoundManager::SoundManager()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SoundManager::~SoundManager()
{
}

/// <summary>
/// SoundManager�̗B��̃C���X�^���X��Ԃ�
/// </summary>
/// <returns>�B��̎��Ԃ̎Q��</returns>
SoundManager& SoundManager::GetInstance()
{
	// �B��̎���
	static SoundManager instance;

	// �B��̎��ԎQ�Ƃ�Ԃ�
	return instance;
}

/// <summary>
/// 2D�T�E���h�̃��[�h
/// </summary>
/// <param name="fileName">���[�h�������T�E���h�t�@�C����(�g���q�Ȃ�)</param>
/// <param name="extension">���[�h�����T�E���h�̊g���q</param>
void SoundManager::LoadSoundFile2D(std::string fileName, std::string extension)
{
	std::string path = data_file_path;
	path += fileName;
	path += extension;
	int handle = LoadSoundMem(path.c_str());
	assert(handle != -1);
	soundNameAndHandleTable_[fileName].handle = handle;
}

/// <summary>
/// 3D�T�E���h�̃��[�h
/// </summary>
/// <param name="fileName">���[�h�������T�E���h�t�@�C����(�g���q�Ȃ�)</param>
/// <param name="extension">���[�h�����T�E���h�̊g���q</param>
void SoundManager::LoadSoundFile3D(std::string fileName, std::string extension)
{
	std::string path = data_file_path;
	path += fileName;
	path += extension;
	SetCreate3DSoundFlag(TRUE);
	int handle = LoadSoundMem(path.c_str());
	SetCreate3DSoundFlag(FALSE);
	assert(handle != -1);
	soundNameAndHandleTable_[fileName].handle = handle;
}

/// <summary>
/// �t�@�C������T�E���h�̃f�[�^��ǂݎ���ăf�[�^�e�[�u���Ɋi�[
/// </summary>
void SoundManager::LoadAndSaveSoundFileData()
{
	// �t�@�C�����̓ǂݍ���(�ǂݍ��݂Ɏ��s������~�߂�)
	std::ifstream ifs("Data/Csv/Sound.csv");
	assert(ifs);

	// csv�f�[�^��1�s���ǂݎ��
	std::string line;
	while (getline(ifs, line))
	{
		// csv�f�[�^�P�s��','�ŕ����̕�����ɕϊ�
		std::vector<std::string>	strvec = Split(line, ',');

		// �������K�؂ȃf�[�^�^�ɕϊ����Ċi�[
		SoundData data;
		data.handle = -1;	// ������
		data.volumeRate = stof(strvec[SoundDataType::VOLUM_RATE]);	// string�^����float�^�ɕϊ����i�[
		data.extension = strvec[SoundDataType::EXTENSION];			// string�^�Ŋi�[

		// �T�E���h�^�C�v�̕ۑ�
		// �ϊ������f�[�^���t�@�C�������L�[�Ƃ��Ċi�[
		// �T�E���h�̃^�C�v�ɂ���Ă��ꂼ�ꃍ�[�h
		switch (stoi(strvec[SoundDataType::SOUND_TYPE]))
		{
		case SoundType::BGM:
			data.type = SoundType::BGM;
			soundNameAndHandleTable_[strvec[SoundDataType::FILE_NAME]] = data;
			LoadSoundFile2D(strvec[SoundDataType::FILE_NAME], data.extension);
			break;
		case SoundType::SE2D:
			data.type = SoundType::SE2D;
			soundNameAndHandleTable_[strvec[SoundDataType::FILE_NAME]] = data;
			LoadSoundFile2D(strvec[SoundDataType::FILE_NAME], data.extension);
			break;
		case SoundType::SE3D:
			data.type = SoundType::SE3D;
			soundNameAndHandleTable_[strvec[SoundDataType::FILE_NAME]] = data;
			LoadSoundFile3D(strvec[SoundDataType::FILE_NAME], data.extension);
			break;
		default:
			// ���蓾�Ȃ��l�Ȃ̂Ŏ~�߂�
			assert(0);
			break;
		}
	}
}

/// <summary>
/// �w���2DSE��炷(�T�E���h�����[�h����Ă��Ȃ��ꍇ�A2DSE�ȊO�̏ꍇ�͎~�܂�)
/// </summary>
/// <param name="name">�Đ��������T�E���h�̃t�@�C����(�g���q�͊܂܂Ȃ�)</param>
void SoundManager::Play(std::string fileName)
{
	assert(soundNameAndHandleTable_.find(fileName) != soundNameAndHandleTable_.end());	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	assert(soundNameAndHandleTable_[fileName].type == SoundType::SE2D);					// 2DSE�ȊO�̏ꍇ�͎~�߂�
	PlaySoundMem(soundNameAndHandleTable_[fileName].handle, DX_PLAYTYPE_BACK);
	SetVolume(fileName, 255);
}

/// <summary>
/// �w���BGM��炷(�T�E���h�����[�h����Ă��Ȃ��ꍇ�ABGM�ȊO�̏ꍇ�͎~�܂�)
/// </summary>
/// <param name="fileName">�Đ��������T�E���h�̃t�@�C����</param>
void SoundManager::PlayBGM(std::string fileName)
{
	assert(soundNameAndHandleTable_.find(fileName) != soundNameAndHandleTable_.end());	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	assert(soundNameAndHandleTable_[fileName].type == SoundType::BGM);					// BGM�ȊO�̏ꍇ�͎~�߂�
	PlaySoundMem(soundNameAndHandleTable_[fileName].handle, DX_PLAYTYPE_LOOP);
	SetVolume(fileName, 255);
}

/// <summary>
/// ����̃T�E���h���Đ������`�F�b�N(�T�E���h�����[�h����Ă��Ȃ�������~�߂�)
/// </summary>
/// <param name="fileName">�Đ����Ă��邩�`�F�b�N�������T�E���h�̃t�@�C����</param>
/// <returns>true : �Đ����Afalse : �Đ����Ă��Ȃ�</returns>
bool SoundManager::PlayingCheckSound(std::string fileName)
{
	assert(soundNameAndHandleTable_.find(fileName) != soundNameAndHandleTable_.end());	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	bool sound = CheckSoundMem(soundNameAndHandleTable_[fileName].handle);
	return sound;
}

/// <summary>
/// ����̃T�E���h���~�߂�(�T�E���h�����[�h����Ă��Ȃ�������~�߂�)
/// </summary>
/// <param name="fileName">�~�߂����T�E���h�̃t�@�C����(�g���q�͊܂܂Ȃ�)</param>
void SoundManager::StopSound(std::string fileName)
{
	assert(soundNameAndHandleTable_.find(fileName) != soundNameAndHandleTable_.end());	// ���[�h���Ă��Ȃ��ꍇ�͎~�߂�
	StopSoundMem(soundNameAndHandleTable_[fileName].handle);
}

/// <summary>
/// ���ׂẴT�E���h���~�߂�
/// </summary>
void SoundManager::StopAllSound()
{
	for (auto& sound : soundNameAndHandleTable_)
	{
		StopSoundMem(sound.second.handle);
	}
}

/// <summary>
/// ���ʒ���
/// </summary>
/// <param name="fileName">���ʒ��߂������T�E���h�̃t�@�C����(�g���q�͊܂܂Ȃ�)</param>
/// <param name="volume">�ݒ肵��������(0~255)</param>
void SoundManager::SetVolume(std::string fileName, int volume)
{
	// �T�E���h�ɐݒ肳�ꂽ���ʒ���
	int setVolume = volume;
	setVolume = static_cast<int>(volume * soundNameAndHandleTable_[fileName].volumeRate);

	// �R���t�B�O�Őݒ肵�����ʒ���
	int configVolume = 255;
	// BGM
	if (soundNameAndHandleTable_[fileName].type == SoundType::BGM)
	{
	//	configVolume = SaveData::GetInstance().GetBgmVolume();
	}
	// SE
	else
	{
	//	configVolume = SaveData::GetInstance().GetSeVolume();
	}

	// �ݒ肵�������ʂƃT�E���h�ɐݒ肳�ꂽ���ʂƃR���t�B�O�Őݒ肳�ꂽ���ʂ��狁�߂��ŏI�I�ȉ��ʂɐݒ�
	float configRate = static_cast<float>(configVolume) / 255;
	setVolume = static_cast<int>(setVolume * configRate);
	ChangeVolumeSoundMem(setVolume, soundNameAndHandleTable_[fileName].handle);
}
