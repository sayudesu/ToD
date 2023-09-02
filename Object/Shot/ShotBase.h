#pragma once
#include <DxLib.h>

// ショットクラス
class ShotBase
{
public:
	ShotBase(VECTOR pos);
	virtual~ShotBase() {};

	virtual void Init() {};
	virtual void End() {};
	virtual void Update() {};
	virtual void Draw() {};

	// ショットの位置
	virtual VECTOR SetPos()const{ return m_pos; }
	// ターゲット位置
	virtual void SetTargetPos(VECTOR pos) { m_targetPos = pos; }
	virtual bool IsGetEnd();
protected:
	// 移動の計算をしています
	void VecCalculation(VECTOR tagetPos, float speed);
protected:
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
	// 目的地と今の距離
	float m_nowPosToNextPosX;
	float m_nowPosToNextPosZ;
};

