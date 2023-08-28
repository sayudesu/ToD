#pragma once
#include <DxLib.h>

// ショットクラス
class ShotBase
{
public:
	ShotBase(VECTOR pos);
	virtual~ShotBase();

	void Update();
	void Draw();

	// ショットの位置
	VECTOR SetPos()const{ return m_pos; }
	// ターゲット位置
	void GetTargetPos(VECTOR pos) { m_targetPos = pos; }
private:
	// 移動の計算をしています
	void VecCalculation();
private:
	// 3Dモデルハンドル
	int m_hShot;
	// 位置
	VECTOR m_pos;
	// 向き
	VECTOR m_dir;
	// ターゲット位置
	VECTOR m_targetPos;
	// 画面外処理
	bool m_isScreenOut;
};

