#pragma once
#include "Util/Vec2.h"

class CutInDrawer
{
public:
	CutInDrawer();
	~CutInDrawer();
	void Init();
	void End();
	void Update();
	// スライド処理
	void UpdateSlide();
	// リセット
	void Reset();
	void Draw();
private:
	int m_hNewChallenger;
	int m_hSpacialAttack;

	// 停止時間をカウント
	int m_countFrameSleep;
	// どこまでスライドさせるか
	int m_slidePos;

	Vec2 m_pos;
	
};

