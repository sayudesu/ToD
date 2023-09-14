#pragma once
#include "SceneBase.h"

// 選択用クラス
class SelectDrawer;
// 設定用クラス
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
	// タイトル用ハンドル
	int m_hTitleLogo;
	int m_logoImageSizeX;
	int m_logoImageSizeY;

	// 設定を選択したかどうか
	bool m_isSlectSetting;

	// 選択用クラス
	SelectDrawer* m_pSelect;
	// 設定用クラス
	SettingDrawer* m_pGameSetting;

	// あとでけす
	int m_count = 0;
	int m_imagePosX = 0;
};

