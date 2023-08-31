#pragma once
#include "EnemyBase.h"


class EnemyNormal : public EnemyBase
{
public:
	EnemyNormal();
	virtual ~EnemyNormal();

	void Init(VECTOR firstPos, int x, int z);
	void End();
	void Update();
	void NextPosChange();
	void Draw();

private:
	// 敵の動く速さ　まだ仮なのでこれは消す
	int moveCount;
	// 向き
	VECTOR m_dir;
	// ターゲット位置
	VECTOR m_targetPos;
	int m_count;
	int forX;
	int forZ;

	bool m_isStopNow = false;
	bool m_isMoveNow = false;

	bool isRandMove = false;

	std::vector<int> m_testPosX;
	std::vector<int> m_testPosZ;

	std::vector<int> m_recordX;
	std::vector<int> m_recordZ;

	std::vector<int>moveDirZ;
	std::vector<int>moveDirX;
};

