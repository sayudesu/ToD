#pragma once
#include <DxLib.h>

// エフェクシア管理
class EffekseerDrawer
{
public:
	EffekseerDrawer();
	virtual~EffekseerDrawer();

	void Init();
	void End();
	void Update();
	void Draw();
	// 位置を受け取ります
	void GetPos(VECTOR pos);
	// 現在エフェクトが再生されているかどうか
	int SetPlayingNow();
private:
	VECTOR  m_pos;
	int m_hEff;
	int m_hPlayEff;
	int m_time;
};

