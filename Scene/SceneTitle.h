#pragma once
#include "SceneBase.h"

// 選択用クラス
class SelectDrawer;

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

	// 選択用クラス
	SelectDrawer* m_pSelect;
};

