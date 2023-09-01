#pragma once
#include "PauseBase.h"
#include "../GameData.h"

// �I��p�N���X
class SelectDrawer;
class ManualDrawer : public PauseBase
{
public:
	ManualDrawer();
	~ManualDrawer();

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
private:
	// �l�����Z�b�g���܂�
	void Reset();
private:

	// �ݒ��ʂ��I�����邩�ǂ���
	bool m_isSetingEnd;

	// �X���C�h
	int m_slideY;

	// �I��p�N���X
	SelectDrawer* m_pSelect;
};

