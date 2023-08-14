#pragma once
#include "PauseBase.h"
#include "GameData.h"

// 選択用クラス
class SelectDrawer;
// サウンド設定クラス
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
	/// 設定画面を終了するかどうか
	/// </summary>
	/// <returns>設定画面を終了するどうか</returns>
	bool GetSettingEnd();

private:
	void UpdateStart();
	void UpdateMain();
	void UpdateEnd();
	// 値をリセットします
	void Reset();
private:
	// 設定画面を終了するかどうか
	bool m_isSetingEnd;
	// スライド
	int m_slideY;
	// 選択用クラス
	SelectDrawer* m_pSelect;
	// サウンド設定クラス
	SoundSettingDrawer* m_pSoundSetting;
	// サウンドの設定をしているかどうか
	bool m_isSoundSetting;
	// 操作方法
	ManualDrawer* m_pManual;
	// 操作方法を選択しているかどうか
	bool m_isManualDraw;
	// ユーザーの設定クラス
	UserSettingDrawer* m_pUserSettig;
	// ユーザーの設定をしているかどうか
	bool m_isUserSetting;
};

