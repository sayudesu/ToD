#pragma once
#include <DxLib.h>

#include "../../Util/CollDatas.h"

// ショットクラス
class ShotBase
{
public:
	ShotBase(VECTOR pos);
	virtual~ShotBase() {};

	virtual void Init  (VECTOR taegetPos, VECTOR scale, VECTOR rotation, float speed, bool isTracking) {};
	virtual void End   ()    {};
	virtual void Update()    {};
	virtual void Draw  ()    {};

	// ショット判定データ
	virtual CollData GetCollData ()           { return m_collData; }
	// ショットの位置
	virtual VECTOR   SetPos      ()const      { return m_pos;      }
	// ターゲット位置
	virtual void     SetTargetPos(VECTOR pos) { m_targetPos = pos; }
	virtual bool     IsGetEnd    ();
protected:
	// 移動の計算をしています
	void VecCalculation(VECTOR tagetPos, float speed, bool isTracking);
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
	// 判定用データ
	CollData m_collData;
	// 速度
	float m_speed;
	// 半径
	float m_radius;
	// 追跡するかどうか
	bool m_isTracking;
};

