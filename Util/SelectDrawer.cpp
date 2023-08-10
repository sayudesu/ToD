#include "SelectDrawer.h"
#include <DxLib.h>
#include "Pad.h"
#include <cassert>

namespace 
{
	// フォント関連
	const char* kFont = "Data/Fonts/Senobi-Gothic-Medium.ttf";// フォントパス
	const char* kFontName = "せのびゴシック Medium";// フォントの名前

	// 選択用枠
	// パス
	const char* kSelectFramePath = "Data/Image/SelectFrame.png";
	const char* kSelectCatHandPath = "Data/Image/nikukyu.png";

	// 角度
	constexpr int kAngle = DX_PI / 180;
}

//////////////////////
// CreateTextクラス //
//////////////////////
SelectDrawer::SelectDrawer():
	m_isSelect(false),
	selectNum(-1),
	selectNow(0),
	m_selectNo(-1),
	selectRad(0),
	m_hSelectFrame(-1),
	m_hCatHand(-1)
{
	// 画像ファイルをメモリにロードします。
	m_hSelectFrame = LoadGraph(kSelectFramePath);
	m_hCatHand = LoadGraph(kSelectCatHandPath);

	// 肉球画像の位置
	m_catHandPosX[0] = -300;
	m_catHandPosX[1] = 300;
}

SelectDrawer::~SelectDrawer()
{
	// メモリ解放
	DeleteGraph(m_hSelectFrame);
	DeleteGraph(m_hCatHand);

	for (auto& text : m_pText)
	{
		text.reset();
	}
}

void SelectDrawer::Add(int frameX, int frameY, int stringX, int stringY, const char* text, int color, int size)
{
	// インスタンスを作成
	m_pText.push_back(std::make_shared<StringDrawer>(frameX, frameY, stringX, stringY, text, color, size, m_hSelectFrame, m_hCatHand));
	selectNum++;
}

void SelectDrawer::Update()
{
	if (!m_isSelect)
	{
		// 選択
		if (Pad::isTrigger(PAD_INPUT_UP))
		{
			if (selectNow > 0)
			{
				selectNow--;
			}
			else
			{
				selectNow = selectNum;
			}

			m_isSelect = false;
		}
		if (Pad::isTrigger(PAD_INPUT_DOWN))
		{
			if (selectNow < selectNum)
			{
				selectNow++;
			}
			else
			{
				selectNow = 0;
			}

			m_isSelect = false;
		}
	}
	
	// 選択をする
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_isSelect = true;
	}

	// 選択したら100フレーム後にその画面に切り替わる
	if (m_isSelect)
	{
		m_pText[selectNow]->SetSelectRadius(selectRad += 6);

		if (selectRad > 100)
		{
			m_selectNo = selectNow;
			m_isSelect = false;
		}
	}

	// 全て選択フレームを表示させない
	for (int i = 0; i < m_pText.size(); i++)
	{
		m_pText[i]->SetBlendMode(100);
	}
	// 選択中の文字は選択フレームを表示させる
	m_pText[selectNow]->SetBlendMode(255);

#if true
	// デバッグ用
	if (selectRad > 100)
	{
		m_isSelect = false;
		selectRad = 0;

		for (int i = 0; i < m_pText.size(); i++)
		{
			m_pText[i]->SetSelectRadius(0);
		}
	}

#endif
}

void SelectDrawer::UpdatePos(int x, int y)
{
	for (auto& text : m_pText)
	{
		text->UpdatePos(x, y);
	}
}

void SelectDrawer::UpdateCatHandPos()
{
	static int y = 0;
	if (y < m_pText[selectNow]->GetFramePosY() + 10)
	{
		y += 26;
	}
	if (y > m_pText[selectNow]->GetFramePosY() + 10)
	{
		y -= 26;
	}

	// 選択用肉球を描画
	for (int i = 0; i < kCatHandNum; i++)
	{
		DrawRotaGraph(m_pText[selectNow]->GetFramePosX() + m_catHandPosX[i],
					y,
					0.2,
					kAngle,
					m_hCatHand,
					true);
	}
}

void SelectDrawer::Draw()
{
	for (auto& text : m_pText)
	{
		text->Draw();
	}

	UpdateCatHandPos();
}

void SelectDrawer::ResetSelectNo()
{
	m_selectNo = -1;
}

////////////////
// Textクラス //
////////////////
StringDrawer::StringDrawer(int frameX, int frameY, int stringX, int stringY, const char* text, int color, int size,int frameHnadle,int selectHandle):
	m_frameX(frameX),
	m_frameY(frameY),
	m_stringX(frameX + stringX),
	m_stringY(frameY + stringY),
	m_changePosX(0),
	m_changePosY(0),
	m_text(text),
	m_color(color),
	m_rad(0),
	m_blend(255),
	m_hSelectFrame(frameHnadle)
{
	// フォントデータを作成
	m_fontHandle = CreateFontToHandle(kFontName, size, 3);
	assert(m_fontHandle != -1);

}

StringDrawer::~StringDrawer()
{
	DeleteFontToHandle(m_fontHandle);
}

void StringDrawer::UpdatePos(int x,int y)
{
	m_changePosX = x;
	m_changePosY = y;
}

void StringDrawer::Draw()
{
	// 文字枠を描画
	DrawRotaGraph(m_frameX, m_frameY, 1, kAngle, m_hSelectFrame, true);

	// 描画ブレンドモードをαブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, m_blend);
	// フォントデータを使い文字を描画
	DrawStringToHandle(m_stringX + m_changePosX, m_stringY + m_changePosY, m_text, m_color, m_fontHandle);
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 円の大きさを変更
	if(m_rad != 0)DrawCircle(m_frameX, m_frameY, m_rad, 0xff0000,false);
}

// 円の大きさ
void StringDrawer::SetSelectRadius(int rad)
{
	m_rad = rad;
}
// ブレンド率
void StringDrawer::SetBlendMode(int blendLevel)
{
	m_blend = blendLevel;
}
// 枠の位置X
int StringDrawer::GetFramePosX()
{
	return m_frameX;
}
// 枠の位置Y
int StringDrawer::GetFramePosY()
{
	return m_frameY;
}

