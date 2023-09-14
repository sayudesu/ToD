#pragma once
#include "SceneBase.h"

// �I��p�N���X
class SelectDrawer;
// �ݒ�p�N���X
class SettingDrawer;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update();
	virtual void Draw();
private:
	// �^�C�g���p�n���h��
	int m_hTitleLogo;
	int m_logoImageSizeX;
	int m_logoImageSizeY;

	// �ݒ��I���������ǂ���
	bool m_isSlectSetting;

	// �I��p�N���X
	SelectDrawer* m_pSelect;
	// �ݒ�p�N���X
	SettingDrawer* m_pGameSetting;

	// ���Ƃł���
	int m_count = 0;
	int m_imagePosX = 0;
};

