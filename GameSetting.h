#pragma once
#include "PauseBase.h"
// 選択用クラス
class SelectDrawer;
class GameSetting : public PauseBase
{
public:
	GameSetting();
	~GameSetting();

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

	/// <summary>
	/// ボリューム調整
	/// </summary>
	/// <param name="changeNo">変更する配列番号</param>
	/// <param name="BigVol">でかい</param>
	/// <param name="MaxVol">ちいさい</param>
	/// <param name="changeVol">調整量</param>
	void SoundVolume(int changeNo, int BigVol, int MaxVol, int changeVol);

	/// <summary>
	/// SoundVolumeの更新用関数
	/// <summary>
	/// <param name="changeNo">変更する配列番号</param>
	void UpdateSoundVolume(int changeNo);
private:
	// ボリューム猫関係
	int m_hVolCat;
	int m_hVolCatD;
	int m_hVolCatS;
	int m_volCatDirection[2];
	int m_catPosX[2];
	int m_catPosY[2];

	// サウンド設定用位置
	int m_SoundVolPosX[2];
	int m_TempSoundVolPosX[2];

	// 設定画面を終了するかどうか
	bool m_isSetingEnd;

	// 調整バー用変数
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

	// スライド
	int m_slideY;

	// 選択用クラス
	SelectDrawer* m_pSelect;
};

