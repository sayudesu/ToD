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
	m_pSelect->Add(
		Game::kScreenWidth / 2,
		Game::kScreenHeight / 2 + 250,
		-200,
		-25,
		"ゲームスタート",
		0xffffff,
		52);

	m_pSelect->Add(
		Game::kScreenWidth / 2,
		Game::kScreenHeight / 2 + 350,
		-150,
		-25,
		"クレジット",
		0xffffff,
		52);
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
