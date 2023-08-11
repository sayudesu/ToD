#include "GameSetting.h"
#include <DxLib.h>
#include "Util/game.h"
#include "Util/Pad.h"
#include "Util/SelectDrawer.h"
#include "Util/SoundFunctions.h"

namespace
{
	// 猫の画像パス
	const char* kVolCat = "Data/Image/SelectVol.png";
	const char* kVolCatS = "Data/Image/SelectVol_S.png";

	// 猫の画像のスピード
	constexpr int kVolCatSpeed = 20;

	// 選択用表示文字
	// 1
	constexpr int kFrame1PosX = Game::kScreenWidth / 2;
	constexpr int kFrame1PosY = Game::kScreenHeight / 2 - 100;
	constexpr int kString1PosX = -200;
	constexpr int kString1PosY = -25;
	const char* kStringGameStert = "BGM";
	constexpr int kString1Color = 0xffffff;
	constexpr int kString1Size = 52;
	// 2
	constexpr int kFrame2PosX = Game::kScreenWidth / 2;
	constexpr int kFrame2PosY = Game::kScreenHeight / 2 + 100;
	constexpr int kString2PosX = -200;
	constexpr int kString2PosY = -25;
	const char* kStringGameStert2 = "SE";
	constexpr int kString2Color = 0xffffff;
	constexpr int kString2Size = 52;
	// 3
	constexpr int kFrame3PosX = Game::kScreenWidth / 2;
	constexpr int kFrame3PosY = Game::kScreenHeight / 2 + 350;
	constexpr int kString3PosX = -200;
	constexpr int kString3PosY = -25;
	const char* kStringSettingEnd = "閉じる";
	constexpr int kString3Color = 0xffffff;
	constexpr int kString3Size = 52;
}

GameSetting::GameSetting() :
	m_hVolCat(-1),
	m_hVolCatD(-1),
	m_hVolCatS(-1),
	m_isSetingEnd(false),
	m_slideY(-Game::kScreenHeight)
{
	// 選択用クラスのインスタンス
	m_pSelect = new SelectDrawer;

	// 設置用関数に移動
	m_updateFunc = &PauseBase::UpdateStart;
}

GameSetting::~GameSetting()
{
	delete m_pSelect;
}

void GameSetting::Init()
{
	// 画像データの読み込み
	m_hVolCatD = LoadGraph(kVolCat);
	m_hVolCatS = LoadGraph(kVolCatS);

	m_hVolCat = m_hVolCatD;

	m_pSelect->Add(
		kFrame1PosX,
		kFrame1PosY,
		kString1PosX,
		kString1PosY,
		kStringGameStert,
		kString1Color,
		kString1Size
		);

	m_pSelect->Add(
		kFrame2PosX,
		kFrame2PosY,
		kString2PosX,
		kString2PosY,
		kStringGameStert2,
		kString2Color,
		kString2Size
	);

	m_pSelect->Add(
		kFrame3PosX,
		kFrame3PosY,
		kString3PosX,
		kString3PosY,
		kStringSettingEnd,
		kString3Color,
		kString3Size
	);

	// ボリューム
	m_SoundVolPosX[0] = 1000;
	m_SoundVolPosX[1] = 1000;
	m_TempSoundVolPosX[0] = 1000;
	m_TempSoundVolPosX[1] = 1000;

	// ボリューム枠
	m_frame[0].upLeft = Game::kScreenWidth / 2 - 500;
	m_frame[0].bottomLeft = Game::kScreenHeight / 2 - 25;
	m_frame[0].upRight = Game::kScreenWidth / 2 + 500;
	m_frame[0].bottomRight = Game::kScreenHeight / 2 + 25;

	m_frame[1].upLeft = Game::kScreenWidth / 2 - 500;
	m_frame[1].bottomLeft = kFrame2PosY + 75;
	m_frame[1].upRight = Game::kScreenWidth / 2 + 500;
	m_frame[1].bottomRight = m_frame[1].bottomLeft + 50;

	// ボリュームバー
	m_volVer[0].upLeft = Game::kScreenWidth / 2 - 500;
	m_volVer[0].bottomLeft = Game::kScreenHeight / 2 - 25;
	m_volVer[0].upRight = Game::kScreenWidth / 2 - 500;
	m_volVer[0].bottomRight = Game::kScreenHeight / 2 + 25;

	m_volVer[1].upLeft = Game::kScreenWidth / 2 - 500;
	m_volVer[1].bottomLeft = kFrame2PosY + 75;
	m_volVer[1].upRight = Game::kScreenWidth / 2 - 500;
	m_volVer[1].bottomRight = m_frame[1].bottomLeft + 50;

	// ボリューム猫
	m_catPosX[0] = Game::kScreenWidth / 2 - 500;
	m_catPosY[0] = Game::kScreenHeight / 2 - 25 + 25;

	m_catPosX[1] = Game::kScreenWidth / 2 - 500;
	m_catPosY[1] = kFrame2PosY + 75 + 25;

	// 猫の向き
	m_volCatDirection[0] = false;

	m_volCatDirection[1] = false;
}

void GameSetting::End()
{
	// 画像データのメモリ解放
	DeleteGraph(m_hVolCatD);
	DeleteGraph(m_hVolCatS);
	DeleteGraph(m_hVolCat);
}

void GameSetting::Update()
{
	(this->*m_updateFunc)();
}

void GameSetting::Draw()
{
	DrawBox(
		0,
		0 + m_slideY,
		Game::kScreenWidth,
		Game::kScreenHeight + m_slideY,
		0xaaaaaa,
		true);
	// 調整用外枠を描画
	// 調整用背景を描画
	// 調整用猫を描画
	for (int i = 0; i < 2; i++)
	{
		DrawBox(
			m_frame[i].upLeft,
			m_frame[i].bottomLeft + m_slideY,
			m_frame[i].upRight,
			m_frame[i].bottomRight + m_slideY,
			0xffffff,
			true);

		DrawBox(
			m_volVer[i].upLeft,
			m_volVer[i].bottomLeft + m_slideY,
			m_volVer[i].upRight + m_SoundVolPosX[i],
			m_volVer[i].bottomRight + m_slideY,
			0x00ff00,
			true);

		DrawRotaGraph(
			m_catPosX[i] + m_SoundVolPosX[i],
			m_catPosY[i] + m_slideY,
			0.9,
			DX_PI_F / 180.0f,
			m_hVolCat,
			true,
			m_volCatDirection[i],
			false
		);
	}

	m_pSelect->Draw();
}

/// <returns>設定画面を終了するどうか</returns>
bool GameSetting::GetSettingEnd()
{
	return m_isSetingEnd;
}

void GameSetting::UpdateStart()
{
	// Main用関数に移動
	m_updateFunc = &PauseBase::UpdateMain;

#if _DEBUG
	printfDx("Start\n");
#endif
}

void GameSetting::UpdateMain()
{
	m_pSelect->Update();
	for (int i = 0; i < 2; i++)
	{
		// ボリューム調整
		if (m_pSelect->GetSelectNowNo() == i)
		{
			if (Pad::isTrigger(PAD_INPUT_RIGHT))
			{
				SoundVolume(i,1000, m_SoundVolPosX[i], 100);
				m_volCatDirection[i] = true;
			}
			if (Pad::isTrigger(PAD_INPUT_LEFT))
			{
				SoundVolume(i,m_SoundVolPosX[i],0,-100);
				m_volCatDirection[i] = false;
			}
		}

		UpdateSoundVolume(i);
	}

	// 閉じるを選択すると設定画面を終了処理に移行します
	if (m_pSelect->GetSelectNo() == 2)
	{
		// End用関数に移動
		m_updateFunc = &PauseBase::UpdateEnd;
	}
	else
	{
		m_isSetingEnd = false;
	}
#if _DEBUG
	printfDx("Main\n");
#endif
}

void GameSetting::UpdateEnd()
{
#if _DEBUG
	printfDx("End\n");
#endif
	// Main用関数に移動
	m_updateFunc = &PauseBase::UpdateMain;
	m_pSelect->ResetSelectNo();
	m_isSetingEnd = true;
}

void GameSetting::SoundVolume(int changeNo,int BigVol, int MaxVol,int changeVol)
{
	// サウンド調整
	if (BigVol > MaxVol)
	{
		m_TempSoundVolPosX[changeNo] += changeVol;

		// サウンド再生
		SoundFunctions::Play(SoundFunctions::SoundIdSelctChange);
	}
	else
	{
		// サウンド再生
		SoundFunctions::Play(SoundFunctions::SoundIdOver);
	}
}

void GameSetting::UpdateSoundVolume(int changeNo)
{
	// 目的のボリュームの位置まで動く
	if (m_TempSoundVolPosX[changeNo] > m_SoundVolPosX[changeNo])
	{
		m_SoundVolPosX[changeNo] += kVolCatSpeed;
	}
	if (m_TempSoundVolPosX[changeNo] < m_SoundVolPosX[changeNo])
	{
		m_SoundVolPosX[changeNo] -= kVolCatSpeed;
	}

	// 特別な画像変更
	if (m_SoundVolPosX[0] == 0 &&
		m_SoundVolPosX[1] == 0)
	{
		m_hVolCat = m_hVolCatS;
	}
}


