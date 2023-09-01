#include "ManualDrawer.h"
#include <DxLib.h>
#include "../Util/game.h"
#include "../Util/Pad.h"
#include "../Util/SelectDrawer.h"
#include "../Util/SoundFunctions.h"
#include "../SaveDataFunctions.h"
#include "../Util/LoadGraphFunction.h"

namespace
{
	// 猫の画像の速さ
	constexpr int kVolCatSpeed = 20;
	// スライドの速さ
	constexpr int kSlideSpeed = 50;

	// 3
	constexpr int kFrame3PosX = Game::kScreenWidth / 2;
	constexpr int kFrame3PosY = Game::kScreenHeight / 2 + 350;
	constexpr int kString3PosX = -200;
	constexpr int kString3PosY = -25;
	const char* kStringSettingEnd = "閉じる";
	constexpr int kString3Color = 0xffffff;
	constexpr int kString3Size = 52;
}

ManualDrawer::ManualDrawer():
	m_isSetingEnd(false),
	m_slideY(-Game::kScreenHeight)
{
	// 選択用クラスのインスタンス
	m_pSelect = new SelectDrawer;

	// 設置用関数に移動
	m_updateFunc = &PauseBase::UpdateStart;
}

ManualDrawer::~ManualDrawer()
{
	delete m_pSelect;
}

void ManualDrawer::Init()
{

	m_pSelect->Add(
		kFrame3PosX,
		kFrame3PosY,
		kString3PosX,
		kString3PosY,
		kStringSettingEnd,
		kString3Color,
		kString3Size
	);
}

void ManualDrawer::End()
{
}

void ManualDrawer::Update()
{
	(this->*m_updateFunc)();
}

void ManualDrawer::Draw()
{
	// 背景画像
	DrawExtendGraph(
		0,
		0 + m_slideY,
		Game::kScreenWidth - 0,
		Game::kScreenHeight + 100 + m_slideY,
		LoadGraphFunction::GraphData(LoadGraphFunction::Wood),
		true);

	DrawRotaGraph(
		Game::kScreenWidth / 2,
		Game::kScreenHeight / 2 + m_slideY,
		1,
		DX_PI_F * 180.0f,
		LoadGraphFunction::GraphData(LoadGraphFunction::GamePad),
		true);

	m_pSelect->Draw();
}

/// <returns>設定画面を終了するどうか</returns>
bool ManualDrawer::GetSettingEnd()
{
	return m_isSetingEnd;
}


void ManualDrawer::UpdateStart()
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

void ManualDrawer::UpdateMain()
{
	m_pSelect->Update();

	if (Pad::isTrigger(PAD_INPUT_2))
	{
		// サウンド再生
		SoundFunctions::Play(SoundFunctions::SoundIdSelct);
		// End用関数に移動
		m_updateFunc = &PauseBase::UpdateEnd;
	}

	// 閉じるを選択すると設定画面を終了処理に移行します
	if (m_pSelect->GetSelectNo() == 0)
	{
		// End用関数に移動
		m_updateFunc = &PauseBase::UpdateEnd;
	}
	else
	{
		m_isSetingEnd = false;
	}
}

void ManualDrawer::UpdateEnd()
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
	}
}


void ManualDrawer::Reset()
{
	// Main用関数に移動
	m_updateFunc = &PauseBase::UpdateStart;
	// スライドの値を初期化
	m_slideY = -Game::kScreenHeight;
}


