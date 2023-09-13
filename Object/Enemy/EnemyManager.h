#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/ObjectData.h"

class EnemyBase;
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();

	virtual void Init();
	virtual void End();
	virtual void Create();
	virtual void Update();
	virtual void Draw();
	virtual void DrawUI();

	// ノーマルエネミーの位置
	virtual VECTOR SetNormalPos(int num);
	// ノーマルエネミーの数を返します
	virtual int GetNormalNum();
	// マップチップでデータを受け取ります
	virtual void SetMapChip(std::vector<int>mapChip);
	// 判定用データを受け取る
 	virtual void SetObjCollData(std::vector<ObjectData> collData);
	// 自身の判定用データ
 	virtual std::vector<ObjectData> GetCollData();
	// 受けるダメージを受け取る
	virtual void SetHitDamage(int enemyNo,int damage);
private:
	// 必要のないオブジェクトを削除する
	virtual void EraseObject();
private:
	// ノーマルエネミー
	std::vector<EnemyBase*>m_pEnemy;
	// マップチップのデータ
	std::vector<int>m_mapChip;
};

