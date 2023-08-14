#pragma once
#include "PauseBase.h"
#include "GameData.h"

// �I��p�N���X
class SelectDrawer;
// �T�E���h�ݒ�N���X
class SoundSettingDrawer;

class ManualDrawer;

class UserSettingDrawer;

class SettingDrawer : public PauseBase
{
public:
	SettingDrawer();
	~SettingDrawer();

	void Init();
	void End();
	void Update();
	void Draw();

	/// <summary>
	/// �ݒ��ʂ��I�����邩�ǂ���
	/// </summary>
	/// <returns>�ݒ��ʂ��I������ǂ���</returns>
	bool GetSettingEnd();

private:
	void UpdateStart();
	void UpdateMain();
	void UpdateEnd();
	// �l�����Z�b�g���܂�
	void Reset();
private:
	// �ݒ��ʂ��I�����邩�ǂ���
	bool m_isSetingEnd;
	// �X���C�h
	int m_slideY;
	// �I��p�N���X
	SelectDrawer* m_pSelect;
	// �T�E���h�ݒ�N���X
	SoundSettingDrawer* m_pSoundSetting;
	// �T�E���h�̐ݒ�����Ă��邩�ǂ���
	bool m_isSoundSetting;
	// ������@
	ManualDrawer* m_pManual;
	// ������@��I�����Ă��邩�ǂ���
	bool m_isManualDraw;
	// ���[�U�[�̐ݒ�N���X
	UserSettingDrawer* m_pUserSettig;
	// ���[�U�[�̐ݒ�����Ă��邩�ǂ���
	bool m_isUserSetting;
};

