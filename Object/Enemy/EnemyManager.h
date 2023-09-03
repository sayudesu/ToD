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

	void Init();
	void End();
	void Create();
	void Update();
	void Draw();
	// ノーマルエネミーの位置
	VECTOR SetNormalPos(int num);
	VECTOR SetNormalPos2(int num);
	int SetNormalNum();

	void SetMapChip(std::vector<int>mapChip);

	// 判定用データを受け取る
 	virtual void SetObjCollData(std::vector<CollData> collData);

	// 配列の数
	int GetNormalNum();

private:
	// ノーマルエネミー
	std::vector<std::shared_ptr<EnemyBase>>m_pEnemyNormal;
	std::vector<int>m_mapChip;
	// 出現数をカウントします
	int m_count;
	// オブジェクトの数
	int m_objNum;
};

