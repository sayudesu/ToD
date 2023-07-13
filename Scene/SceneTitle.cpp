#include "SceneTitle.h"
#include "Scene/SceneMain.h"
#include <DxLib.h>
#include "Util/Pad.h"
#include "Util/game.h"

namespace
{
	// タイトル関連
	// パス
	const char* kTitlePath = "Data/Image/VitalFortress.png";
	// 位置
	constexpr int kTitlePosX = Game::kScreenWidth / 2;
	constexpr int kTitlePosY = Game::kScreenHeight / 2 - 200;
	// 大きさ
	constexpr int kTitleScale = 2;
	// 角度
	constexpr int kAngle = DX_PI / 180;
}

SceneTitle::SceneTitle():
	m_hTitleLogo(-1)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	// 画像ファイルをメモリにロードします。
	m_hTitleLogo = LoadGraph(kTitlePath);
	// 画像サイズを取得
	GetGraphSize(m_hTitleLogo, &m_logoImageSizeX, &m_logoImageSizeY);
}

void SceneTitle::End()
{
	// メモリ解放
	DeleteGraph(m_hTitleLogo);
}

SceneBase* SceneTitle::Update()
{
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return new SceneMain;
	}
	return this;
}

void SceneTitle::Draw()
{
	// 背景色
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xaaaaaa, true);

	// タイトルロゴを描画
	DrawRotaGraph(kTitlePosX, kTitlePosY, kTitleScale, kAngle, m_hTitleLogo, true);
}
