#include "SoundSettingDrawer.h"
#include <DxLib.h>
#include "../Util/game.h"
#include "../Util/Pad.h"
#include "SelectDrawer.h"
#include "../Util/SoundFunctions.h"
#include "../Save/SaveDataFunctions.h"
#include "../Util/LoadGraphFunction.h"

namespace
{
	// 猫の画像の速さ
	constexpr int kVolCatSpeed = 100;
	// スライドの速さ
	constexpr int kSlideSpeed = 50;

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

SoundSettingDrawer::SoundSettingDrawer() :
	m_hVolCat(-1),
	m_isSetingEnd(false),
	m_slideY(-Game::kScreenHeight)
{
	// 選択用クラスのインスタンス
	m_pSelect = new SelectDrawer;

	// 設置用関数に移動
	m_updateFunc = &PauseBase::UpdateStart;
}

SoundSettingDrawer::~SoundSettingDrawer()
{
	delete m_pSelect;
}

void SoundSettingDrawer::Init()
{
	m_hVolCat = LoadGraphFunction::GraphData(LoadGraphFunction::VolCat);

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
	m_SoundVolPosX[0] = SaveDataFunctions::GetSoundBarData().Bgm;
	m_SoundVolPosX[1] = SaveDataFunctions::GetSoundBarData().SE;
	m_TempSoundVolPosX[0] = m_SoundVolPosX[0];
	m_TempSoundVolPosX[1] = m_SoundVolPosX[1];

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

void SoundSettingDrawer::End()
{
}

void SoundSettingDrawer::Update()
{
	(this->*m_updateFunc)();
}

void SoundSettingDrawer::Draw()
{
	// 背景画像
	DrawExtendGraph(
		0,
		0 + m_slideY,
		Game::kScreenWidth - 0,
		Game::kScreenHeight + 100 + m_slideY,
		LoadGraphFunction::GraphData(LoadGraphFunction::Wood),
		true);


	// 調整用外枠を描画
	// 調整用背景を描画
	// 調整用猫を描画
	for (int i = 0; i < 2; i++)
	{
		DrawExtendGraph(
			m_frame[i].upLeft,
			m_frame[i].bottomLeft + m_slideY,
			m_frame[i].upRight,
			m_frame[i].bottomRight + m_slideY,
			LoadGraphFunction::GraphData(LoadGraphFunction::OutSideBarBg),
			true);

		DrawExtendGraph(
			m_volVer[i].upLeft,
			m_volVer[i].bottomLeft + m_slideY,
			m_volVer[i].upRight + m_SoundVolPosX[i],
			m_volVer[i].bottomRight + m_slideY,
			LoadGraphFunction::GraphData(LoadGraphFunction::Bar),
			true);

		DrawExtendGraph(
			m_frame[i].upLeft,
			m_frame[i].bottomLeft + m_slideY,
			m_frame[i].upRight,
			m_frame[i].bottomRight + m_slideY,
			LoadGraphFunction::GraphData(LoadGraphFunction::OutSideBar),
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
bool SoundSettingDrawer::GetSettingEnd()
{
	return m_isSetingEnd;
}

// 現在の音量
// 0から255
GameData::Sound SoundSettingDrawer::GetSoundVol()
{
	return m_saveSound;
}

void SoundSettingDrawer::UpdateStart()
{
	// スライドします
	m_slideY += kSlideSpeed;

	m_pSelect->UpdatePos(0,m_slideY);

	// スライドが終わると関数を移動
	if (m_slideY > 0)
	{
		// スライドの値を0に調整
		m_slideY = 0;
		// Main用関数に移動
		m_updateFunc = &PauseBase::UpdateMain;
	}
	m_isSetingEnd = false;	
}

void SoundSettingDrawer::UpdateMain()
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

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		// サウンド再生
		SoundFunctions::Play(SoundFunctions::SoundIdSelct);
		// End用関数に移動
		m_updateFunc = &PauseBase::UpdateEnd;
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

	// 音量を調整します
	UpdateSoundVol();
}

void SoundSettingDrawer::UpdateEnd()
{
	m_slideY -= kSlideSpeed;

	m_pSelect->UpdatePos(0, m_slideY);

	if (m_slideY < -Game::kScreenHeight)
	{
		// 変数の初期化
		Reset();
		// エンド処理が終わっているかどうか
		m_isSetingEnd = true;
		// 選択をリセットします
		m_pSelect->ResetSelectNo();

		// データを保存します
		//GameData::Input save{};
		//save.Bgm_ = m_saveSound.Bgm;
		//save.SE_ = m_saveSound.SE;
		//SaveDataFunctions::Save(save);
	}


}

void SoundSettingDrawer::SoundVolume(int changeNo,int BigVol, int MaxVol,int changeVol)
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

void SoundSettingDrawer::UpdateSoundVolume(int changeNo)
{
	// 目的のボリュームの位置まで動く
	if (m_TempSoundVolPosX[changeNo] > m_SoundVolPosX[changeNo])
	{
		// スライド更新
		m_SoundVolPosX[changeNo] += kVolCatSpeed;
		// 最大値を調整
		if (m_SoundVolPosX[changeNo] > 1000)m_SoundVolPosX[changeNo] = 1000;
	}
	if (m_TempSoundVolPosX[changeNo] < m_SoundVolPosX[changeNo])
	{
		// スライド更新
		m_SoundVolPosX[changeNo] -= kVolCatSpeed;
		// 最大値を調整
		if (m_SoundVolPosX[changeNo] < 0)m_SoundVolPosX[changeNo] = 0;
	}

	// 特別な画像変更
	if (m_SoundVolPosX[0] == 0 &&
		m_SoundVolPosX[1] == 0)
	{
		m_hVolCat = LoadGraphFunction::GraphData(LoadGraphFunction::VolCatS);
	}
}

// 音量を調整します
void SoundSettingDrawer::UpdateSoundVol()
{
	// 音量を変更
	m_saveSound.Bgm = m_SoundVolPosX[0];
	m_saveSound.SE = m_SoundVolPosX[1];

	// 0から1000の範囲を0から255に
	m_saveSound.Bgm = ((m_SoundVolPosX[0] - 0) * (255 - 0)) / (1000 - 0);
	m_saveSound.SE  = ((m_SoundVolPosX[1] - 0) * (255 - 0)) / (1000 - 0);
	// BGM
	SoundFunctions::SetVolume(SoundFunctions::SoundIdTitle, m_saveSound.Bgm);
	SoundFunctions::SetVolume(SoundFunctions::SoundIdBattle, m_saveSound.Bgm);
	SoundFunctions::SetVolume(SoundFunctions::SoundIdEnd, m_saveSound.Bgm);
	// SE
	SoundFunctions::SetVolume(SoundFunctions::SoundIdSelctChange, m_saveSound.SE);
	SoundFunctions::SetVolume(SoundFunctions::SoundIdSelct, m_saveSound.SE);
	SoundFunctions::SetVolume(SoundFunctions::SoundIdOver, m_saveSound.SE);

}

void SoundSettingDrawer::Reset()
{
	// Main用関数に移動
	m_updateFunc = &PauseBase::UpdateStart;
	// スライドの値を初期化
	m_slideY = -Game::kScreenHeight;
}


