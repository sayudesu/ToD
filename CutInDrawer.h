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

	// スライドが最後まで終わったかどうか
	bool IsGetEnd();
	void IsSetEndReset();
private:
	int m_hNewChallenger;
	int m_hSpacialAttack;
	int m_hSpShot;

	// 停止時間をカウント
	int m_countFrameSleep;
	// どこまでスライドさせるか
	int m_slidePos;
	// 演出が終わったかどうか
	bool m_isEnd;
	Vec2 m_pos;
	
};

