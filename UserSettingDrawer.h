#pragma once
#include "PauseBase.h"
#include "GameData.h"

// �I��p�N���X
class SelectDrawer;
class UserSettingDrawer : public PauseBase
{
public:
	UserSettingDrawer();
	~UserSettingDrawer();

	void Init();
	void End();
	void Update();
	void Draw();

	/// <summary>
	/// �ݒ��ʂ��I�����邩�ǂ���
	/// </summary>
	/// <returns>�ݒ��ʂ��I������ǂ���</returns>
	bool GetSettingEnd();

	GameData::Icon GetIcon();

private:
	void UpdateStart();
	void UpdateMain();
	void UpdateEnd();
private:
	// �l�����Z�b�g���܂�
	void Reset();
private:

	// �ݒ��ʂ��I�����邩�ǂ���
	bool m_isSetingEnd;

	// �X���C�h
	int m_slideY;

	// �A�C�R���I��
	int m_hIcon[8];
	int m_iconSelect;
	int m_iconSelectLeft;
	int m_iconSelectRight;

	// �A�C�R���̃f�[�^��ۊ�
	GameData::Icon m_iconData;

	// �I��p�N���X
	SelectDrawer* m_pSelect;
};

