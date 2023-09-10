#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include "../../Util/CollDatas.h"

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
 	virtual void SetObjCollData(std::vector<CollData> collData);
	// 自身の判定用データ
 	virtual std::vector<CollData> GetCollData();

private:
	// ノーマルエネミー
	std::vector<std::shared_ptr<EnemyBase>>m_pEnemyNormal;
	// マップチップのデータ
	std::vector<int>m_mapChip;
	// 出現数をカウントします
	int m_countCreate;
};

