#pragma once
#include "EnemyBase.h"

// 判定用
class Collision3D;

class EnemyNormal : public EnemyBase
{
public:
	EnemyNormal();
	virtual ~EnemyNormal();

	void Init(VECTOR firstPos, int x, int z);
	void End();
	void Update();
	void ChangeNextPos(bool & isMoveing);
	void Draw();
	void DrawUI();

private:
	// 判定処理
	void CheckColl();
	// HPの処理
	void CheckHp();
private:
	int m_hMouse;
	// 敵の動く速さ　まだ仮なのでこれは消す
	int moveCount;
	// 動くかどうか
	bool m_isNextMove;
	// 向き
	VECTOR m_dir;
	// ターゲット位置
	VECTOR m_targetPos;
	// 3D座標から2D座標に変換
	VECTOR m_screenPos;
	// 体力系
	float m_hp;

	int m_count;

	int forX;
	int forZ;

	bool isRandMove = false;

	std::vector<int> m_recordX;
	std::vector<int> m_recordZ;

	std::vector<int>moveDirZ;
	std::vector<int>moveDirX;

	bool m_isHit;
	bool m_isTempHit;
	int m_tempCountHit;

	// 判定用
	Collision3D* m_pColl;
};

