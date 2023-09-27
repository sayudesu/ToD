#include "SelectDrawer.h"
#include <DxLib.h>
#include <cassert>
#include "../Util/Pad.h"
#include "../Util/SoundFunctions.h"
#include "../Util/LoadGraphFunction.h"

namespace 
{
	// フォント関連
	const char* kFont = "Data/Fonts/Senobi-Gothic-Medium.ttf";// フォントパス
	const char* kFontName = "せのびゴシック Medium";// フォントの名前

	// 選択用枠
	// パス
	const char* kSelectFramePath = "Data/Image/SelectFrame.png";
	const char* kSelectCatHandPath = "Data/Image/nikukyu_S.png";

	// 角度
	constexpr int kAngle = DX_PI_F / 180;
}

//////////////////////
// CreateTextクラス //
//////////////////////
SelectDrawer::SelectDrawer():
	m_isSelect(false),
	selectNum(-1),
	m_selectNow(0),
	m_selectNo(-1),
	selectRad(0),
	m_catHandPosY(0),
	m_tempPosY(0)
{
	// 肉球画像の位置
	m_catHandPosX[0] = -300;
	m_catHandPosX[1] = 300;

	m_stickPressFrameCount[0] = 0;
	m_stickPressFrameCount[1] = 0;
}

SelectDrawer::~SelectDrawer()
{
	for (auto& text : m_pText)
	{
		text.reset();
	}
}

void SelectDrawer::Add(int frameX, int frameY, int stringX, int stringY, const char* text, int color, int size)
{
	// インスタンスを作成
	m_pText.push_back(std::make_shared<StringDrawer>(frameX, frameY, stringX, stringY, text, color, size, LoadGraphFunction::GraphData(LoadGraphFunction::SelectFrame), LoadGraphFunction::GraphData(LoadGraphFunction::SelectCatHand)));
	selectNum++;
}

void SelectDrawer::End()
{
}

void SelectDrawer::Update()
{
	if (!m_isSelect)
	{
		// 選択
		if (Pad::isPress(PAD_INPUT_UP))
		{
			m_stickPressFrameCount[0]++;
			// サウンド追加
			SoundFunctions::Play(SoundFunctions::SoundIdSelctChange);

			if (m_stickPressFrameCount[0] == 1)
			{
					m_selectNow--;
			}
			if (m_stickPressFrameCount[0] > 30)
			{
				m_selectNow--;
			}

			if (m_selectNow < 0)
			{
				m_selectNow = selectNum;
			}

			m_isSelect = false;
		}
		else
		{
			m_stickPressFrameCount[0] = 0;
		}
		if (Pad::isPress(PAD_INPUT_DOWN))
		{
			m_stickPressFrameCount[1]++;
			// サウンド追加
			SoundFunctions::Play(SoundFunctions::SoundIdSelctChange);
			if (m_stickPressFrameCount[1] == 1)
			{
					m_selectNow++;
			}
			if (m_stickPressFrameCount[1] > 30)
			{
				m_selectNow++;
			}

			if (m_selectNow > selectNum)
			{
				m_selectNow = 0;				
			}

			m_isSelect = false;
		}
		else
		{
			m_stickPressFrameCount[1] = 0;
		}
	}
	
	// 選択をする
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		// サウンド追加
		SoundFunctions::Play(SoundFunctions::SoundIdSelct);
		m_isSelect = true;
	}

	// 選択したら100フレーム後にその画面に切り替わる
	if (m_isSelect)
	{
		m_pText[m_selectNow]->SetSelectRadius(selectRad += 6);

		if (selectRad > 100)
		{
			m_selectNo = m_selectNow;
			m_isSelect = false;
		}
	}

	// 全て選択フレームを表示させない
	for (int i = 0; i < m_pText.size(); i++)
	{
		m_pText[i]->SetBlendMode(100);
	}
	// 選択中の文字は選択フレームを表示させる
	m_pText[m_selectNow]->SetBlendMode(255);

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
	// スライドの為の値を受けとる
	 m_catHandSlideY = y;
}

void SelectDrawer::UpdateCatHandPos()
{
	if (m_tempPosY == m_selectNow)
	{
		m_catHandPosY = m_pText[m_selectNow]->GetFramePosY();
	}

	if (m_catHandPosY < m_pText[m_selectNow]->GetFramePosY() + 10)
	{
		m_catHandPosY += 60;
		m_tempPosY++;
	}
	if (m_catHandPosY > m_pText[m_selectNow]->GetFramePosY() + 10)
	{
		m_catHandPosY -= 60;
		m_tempPosY--;
	}

	// 選択用肉球を描画
	for (int i = 0; i < kCatHandNum; i++)
	{
		DrawRotaGraph(m_pText[m_selectNow]->GetFramePosX() + m_catHandPosX[i],
			m_catHandPosY + m_catHandSlideY,
			0.2,
			kAngle,
			LoadGraphFunction::GraphData(LoadGraphFunction::SelectCatHand),
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

/// <returns>何番目を選択しかたを返す</returns>
int SelectDrawer::GetSelectNo()
{
	return m_selectNo;
}

/// <returns>現在選択中の番号を返す</returns>
int SelectDrawer::GetSelectNowNo()
{
	return m_selectNow;
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
	m_slideY(0),
	m_text(text),
	m_color(color),
	m_rad(0),
	m_blend(255),
	m_hSelectFrame(frameHnadle)
{
	// フォントデータを作成
	m_fontHandle = CreateFontToHandle(kFontName, size, 3);
//	m_fontHandle = CreateFontToHandle("a", size, 3);
	assert(m_fontHandle != -1);

}

StringDrawer::~StringDrawer()
{
	DeleteFontToHandle(m_fontHandle);
}

void StringDrawer::UpdatePos(int x,int y)
{
//	m_slideY = x;
	m_slideY = y;
}

void StringDrawer::Draw()
{
	// 文字枠を描画
	DrawRotaGraph(
		m_frameX,
		m_frameY + m_slideY,
		1,
		kAngle,
		m_hSelectFrame,
		true);

	// 描画ブレンドモードをαブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_PMA_ALPHA, m_blend);
	// フォントデータを使い文字を描画
	DrawStringToHandle(
		m_stringX + m_changePosX,
		m_stringY + m_changePosY + m_slideY,
		m_text,
		m_color,
		m_fontHandle);
	// 描画ブレンドモードをノーブレンドにする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 円の大きさを変更
	if(m_rad != 0)DrawCircle(m_frameX, m_frameY + m_slideY, m_rad, 0xff0000,false);
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

