#include "SceneTitle.h"
#include "Scene/SceneMain.h"
#include <DxLib.h>
#include "Util/Pad.h"
#include "Util/game.h"

namespace
{
	// タイトルロゴのパス
	const char* titlePath = "Data/Image/VitalFortress.png";
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
	m_hTitleLogo = LoadGraph(titlePath);
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
	static int x = Game::kScreenWidth/2;
	static int y = Game::kScreenHeight/2 - 200.0f;
	static int scale = 2;
	// タイトルロゴを描画
	DrawRotaGraph(x, y, scale, DX_PI * 180, m_hTitleLogo, true);
}
