#pragma once
#include "PauseBase.h"
#include "GameData.h"

// �I��p�N���X
class SelectDrawer;
class SoundSettingDrawer : public PauseBase
{
public:
	SoundSettingDrawer();
	~SoundSettingDrawer();

	void Init();
	void End();
	void Update();
	void Draw();

	/// <summary>
	/// �ݒ��ʂ��I�����邩�ǂ���
	/// </summary>
	/// <returns>�ݒ��ʂ��I������ǂ���</returns>
	bool GetSettingEnd();

	// ���݂̉���
	GameData::Sound GetSoundVol();



private:
	void UpdateStart();
	void UpdateMain();
	void UpdateEnd();

	/// <summary>
	/// �{�����[������
	/// </summary>
	/// <param name="changeNo">�ύX����z��ԍ�</param>
	/// <param name="BigVol">�ł���</param>
	/// <param name="MaxVol">��������</param>
	/// <param name="changeVol">������</param>
	void SoundVolume(int changeNo, int BigVol, int MaxVol, int changeVol);

	/// <summary>
	/// SoundVolume�̍X�V�p�֐�
	/// <summary>
	/// <param name="changeNo">�ύX����z��ԍ�</param>
	void UpdateSoundVolume(int changeNo);

	// ���ʂ𒲐����܂�
	void UpdateSoundVol();
private:
	// �l�����Z�b�g���܂�
	void Reset();
private:
	// �{�����[���L�֌W
	int m_hVolCat;
	int m_volCatDirection[2];
	int m_catPosX[2];
	int m_catPosY[2];
	// ���[�^�[�p�摜
	int m_hBar;

	// �T�E���h�ݒ�p�ʒu
	int m_SoundVolPosX[2];
	int m_TempSoundVolPosX[2];

	// �ݒ��ʂ��I�����邩�ǂ���
	bool m_isSetingEnd;

	// �����o�[�p�ϐ�
	struct Box
	{
		int upLeft = 0;
		int upRight = 0;
		int bottomLeft = 0;
		int bottomRight = 0;
	};

	Box m_frame[2];
	Box m_volVer[2];
	Box m_cat[2];

	GameData::Sound m_saveSound;

	// �X���C�h
	int m_slideY;

	// �I��p�N���X
	SelectDrawer* m_pSelect;
};

