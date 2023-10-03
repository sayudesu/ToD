#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/ObjectData.h"
#include "../../MapDatas.h"

class EnemyBase
{
public:
	EnemyBase() {};
	virtual ~EnemyBase() {};

	virtual void Init(VECTOR firstPos,int x,int z);
	virtual void End();
	virtual void Update();
	virtual void Draw();
	virtual void DrawUI();
protected:
	virtual void Move();
	virtual void Attack() = 0;
public:
	// エネミーの位置
	virtual VECTOR GetPos() const   { return m_pos; }
	// 判定データを受け取る
	virtual void SetCollData(std::vector<ObjectData>collData) { m_collObstacleShotData = collData; }
	// 当たり判定データ
	virtual ObjectData GetCollDatas() { return m_collData; }
	// 通る道
	virtual void SetRoadPos(MapDatas mapChip) { m_mapChip = mapChip; }
	// 与えられるダメージを受け取る
	virtual void SetHitDamage(int damage);
	// そのデータが必要なのかどうか
	virtual bool GetErase()const;
	// 動く位置を探して移動
	virtual void ChangeNextPos(bool& isMoveing);

protected:
	// モデルハンドル
	int m_hModel;
	// モデルのファイルパス
	const char* m_filePathModel;
	// 位置
	VECTOR m_pos = VGet(0.0f, 0.0f, 0.0f);
	// 現在の体力
	float m_hp;
	// ダメージ
	int m_damage = 0;
	// マップチップデータ
	MapDatas m_mapChip;
	// プレイヤー設置オブジェクトのデータ
	std::vector<ObjectData> m_collObstacleShotData{};
	// 自身のデータ
	ObjectData m_collData{};

	
	int m_moveCount = 0;
	int m_attackCount = 0;


	// 向き
	VECTOR m_dir;
	// ターゲット位置
	VECTOR m_targetPos;
	// 3D座標から2D座標に変換
	VECTOR m_screenPos;
	// 動くかどうか
	bool m_isNextMove;
	// 最終地点まで到着したら
	bool m_isEndPos;
	// チップ番号での現在位置
	int m_chipPosX;
	int m_chipPosZ;
	// ランダムで動く処理を実行するかどうか
	bool m_isRandMove;
	// 動いた位置を記録し同じ場所を通らない様にする
	std::vector<int> m_recordX;
	std::vector<int> m_recordZ;
	// ランダムで動く場合どの方向に動くかを決める
	std::vector<int>m_moveDirX;
	std::vector<int>m_moveDirZ;
};

