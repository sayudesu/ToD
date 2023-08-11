#include "SceneTitle.h"
#include "SceneMain.h"
#include <DxLib.h>
#include "../Util/Pad.h"
#include "../Util/game.h"
#include "../Util/SelectDrawer.h"
#include <string>

namespace
{
	// タイトル関連
	// パス
	const char* kTitlePath = "Data/Image/VitalFortress2.png";
	// 位置
	constexpr int kTitlePosX = Game::kScreenWidth / 2;
	constexpr int kTitlePosY = Game::kScreenHeight / 2 - 150;
	// 大きさ
	constexpr float kTitleScale = 0.8f;
	// 角度
	constexpr int kAngle = DX_PI / 180;

	// 選択用表示文字
	// 1
	constexpr int kFrame1PosX = Game::kScreenWidth / 2;
	constexpr int kFrame1PosY = Game::kScreenHeight / 2 + 250;
	constexpr int kString1PosX = -200;
	constexpr int kString1PosY = -25;
	const char* kStringGameStert = "ゲームスタート";
	constexpr int kString1Color = 0xffffff;
	constexpr int kString1Size = 52;
	// 2
	constexpr int kFrame2PosX = Game::kScreenWidth / 2;
	constexpr int kFrame2PosY = Game::kScreenHeight / 2 + 350;
	constexpr int kString2PosX = -65;
	constexpr int kString2PosY = -25;
	const char* kStringSetting = "設定";
	constexpr int kString2Color = 0xffffff;
	constexpr int kString2Size = 52;
	// 3
	constexpr int kFrame3PosX = Game::kScreenWidth / 2;
	constexpr int kFrame3PosY = Game::kScreenHeight / 2 + 450;
	constexpr int kString3PosX = -150;
	constexpr int kString3PosY = -25;
	const char* kStringCredit = "クレジット";
	constexpr int kString3Color = 0xffffff;
	constexpr int kString3Size = 52;
}

SceneTitle::SceneTitle():
	m_hTitleLogo(-1)
{
	// 選択用クラスのインスタンス
	m_pSelect = new SelectDrawer;
}

SceneTitle::~SceneTitle()
{
	// メモリ解放
	delete m_pSelect;
	m_pSelect = nullptr;
}

void SceneTitle::Init()
{
	// 画像ファイルをメモリにロードします。
	m_hTitleLogo = LoadGraph(kTitlePath);
	// 画像サイズを取得
	GetGraphSize(m_hTitleLogo, &m_logoImageSizeX, &m_logoImageSizeY);

	// 選択肢を追加
	// 1
	m_pSelect->Add(
		kFrame1PosX,
		kFrame1PosY,
		kString1PosX,
		kString1PosY,
		kStringGameStert,
		kString1Color,
		kString1Size);
	// 2
	m_pSelect->Add(
		kFrame2PosX,
		kFrame2PosY,
		kString2PosX,
		kString2PosY,
		kStringSetting,
		kString2Color,
		kString2Size);
	// 3
	m_pSelect->Add(
		kFrame3PosX,
		kFrame3PosY,
		kString3PosX,
		kString3PosY,
		kStringCredit,
		kString3Color,
		kString3Size);
}

void SceneTitle::End()
{
	// メモリ解放
	m_pSelect->End();
	DeleteGraph(m_hTitleLogo);
}

SceneBase* SceneTitle::Update()
{
	// ゲームスタートを押した場合
	if(m_pSelect->GetSelectNo() == 0)
	{
		m_isChangeScene = true;
		m_isSliderOpen = true;
	}

	if (m_isChangeScene)
	{
		if (SceneBase::UpdateSliderClose())
		{
			return new SceneMain;
		}
	}

	// セレクト関連更新処理
	m_pSelect->Update();

	// スライドを開ける
	SceneBase::UpdateSlider(m_isSliderOpen);

	return this;
}

void SceneTitle::Draw()
{
	// 背景色
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaaaa, true);

	// タイトルロゴを描画
	DrawRotaGraph(kTitlePosX, kTitlePosY, kTitleScale, kAngle, m_hTitleLogo, true);

	// セレクト関連描画
	m_pSelect->Draw();

	SceneBase::DrawSliderDoor();
}
