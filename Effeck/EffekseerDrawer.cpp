#include "EffekseerDrawer.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <cassert>

EffekseerDrawer::EffekseerDrawer():
	m_pos(VGet(0,0,0)),
	m_hEff(-1),
	m_hPlayEff(-1),
	m_time(0)
{
}

EffekseerDrawer::~EffekseerDrawer()
{
}

void EffekseerDrawer::Init()
{
	// エフェクトリソースを読み込む。
	m_hEff = LoadEffekseerEffect("Data/Effect/goal.efkefc",30.0f);
	assert(m_hEff != -1);
}

void EffekseerDrawer::End()
{
	// Effekseerにより再生中の3Dエフェクトの描画を終了する。
	DrawEffekseer3D_End();
	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	DeleteEffekseerEffect(m_hEff);
	// 3D表示のエフェクトを停止する。
	StopEffekseer3DEffect(m_hPlayEff);

	m_pos = VGet(0, 0, 0);	
}

void EffekseerDrawer::Update()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
}

void EffekseerDrawer::Draw()
{
	// 定期的にエフェクトを再生する
	if (m_time % 60 == 0)
	{
		// エフェクトを再生する。
		m_hPlayEff = PlayEffekseer3DEffect(m_hEff);
	}
	m_time++;

	// 再生中のエフェクトを移動する。
	SetPosPlayingEffekseer3DEffect(m_hPlayEff, m_pos.x, m_pos.y , m_pos.z);

	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}

void EffekseerDrawer::GetPos(VECTOR pos)
{
	m_pos = pos;
}

int EffekseerDrawer::SetPlayingNow()
{
	return IsEffekseer3DEffectPlaying(m_hPlayEff);
}
