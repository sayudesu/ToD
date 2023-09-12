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
	void ChangeNextPos(bool & isMoveing);
	void Draw();
	void DrawUI();

	// 当たり判定用データ
	CollData GetCollDatas();
	// 与えられるダメージを受け取る
	void SetHitDamage(int damage);
	// このオブジェクトが必要かどうか
	bool GetErase();
private:
	// モデルハンドル
	int m_hMouse;
	// 敵の動く速さ　まだ仮なのでこれは消す
	int m_moveCount;
	// 動くかどうか
	bool m_isNextMove;
	// 最終地点まで到着したら
	bool m_isEndPos;
	// 向き
	VECTOR m_dir;
	// ターゲット位置
	VECTOR m_targetPos;
	// 3D座標から2D座標に変換
	VECTOR m_screenPos;
	// チップ番号での現在位置
	int m_ChipPosX;
	int m_ChipPosZ;
	// ランダムで動く処理を実行するかどうか
	bool m_isRandMove;
	// 動いた位置を記録し同じ場所を通らない様にする
	std::vector<int> m_recordX;
	std::vector<int> m_recordZ;
	// ランダムで動く場合どの方向に動くかを決める
	std::vector<int>m_moveDirX;
	std::vector<int>m_moveDirZ;
};

