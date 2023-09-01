#pragma once
#include "PauseBase.h"
#include "../GameData.h"

// 選択用クラス
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
	/// 設定画面を終了するかどうか
	/// </summary>
	/// <returns>設定画面を終了するどうか</returns>
	bool GetSettingEnd();

private:
	void UpdateStart();
	void UpdateMain();
	void UpdateEnd();
private:
	// 値をリセットします
	void Reset();
private:

	// 設定画面を終了するかどうか
	bool m_isSetingEnd;

	// スライド
	int m_slideY;

	// 選択用クラス
	SelectDrawer* m_pSelect;
};

