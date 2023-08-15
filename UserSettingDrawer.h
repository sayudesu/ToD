#pragma once
#include "PauseBase.h"
#include "GameData.h"

// 選択用クラス
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
	/// 設定画面を終了するかどうか
	/// </summary>
	/// <returns>設定画面を終了するどうか</returns>
	bool GetSettingEnd();

	GameData::Icon GetIcon();

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

	// アイコン選択
	int m_hIcon[8];
	int m_iconSelect;
	int m_iconSelectLeft;
	int m_iconSelectRight;

	// アイコンのデータを保管
	GameData::Icon m_iconData;

	// 選択用クラス
	SelectDrawer* m_pSelect;
};

