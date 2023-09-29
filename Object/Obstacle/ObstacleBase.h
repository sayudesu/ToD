#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/ObjectData.h"
#include <list>

class ShotBase;
// 障害物クラスベース
class ObstacleBase
{

public:
	ObstacleBase(VECTOR pos, int no);
	virtual ~ObstacleBase() {};

	virtual void Init() = 0;
	virtual void End();
	virtual void Update();
	virtual void UpdateSetting();
	virtual void UpdateShot();
	virtual void Draw();

	// 障害物の位置
	virtual VECTOR GetPos() const;
	// 当たり判定データ
	virtual ObjectData GetCollShotDatas(int shotNum);
	// エネミーの判定用データ
	virtual void SetCollEnemyDatas(std::vector<ObjectData> collEnemyData);
	// ショットの数
	virtual int GetShotNum();
	// いらないショットの番号を受け取る
	virtual void SetEraseShotData(std::vector<ObjectData> eraseShotData) {};
	// ターゲット位置を受け取る
	virtual void SetTarGetPos(VECTOR pos);
	// 必要のないショット番号を受け取る
	virtual void SetShotErase(int shotNum, bool erase);

private:
	// 誰を狙うか
	virtual void TargetPos();
private:
	struct ShotData
	{
		// ハンドルデータ
		int handle;
		// 打ち出しまでのフレームカウント
		int shotFrameCount;
		// ターゲット位置
		VECTOR targetPos;
		// サイズ
		VECTOR scale;
		// 角度
		VECTOR rotation;
		// 半径
		float radius;
		// ダメージ
		float damage;
		// 速度
		float speed;
		// 追跡
		bool isTracking;
		// どのショットか
		int id;
	};
protected:
	// 大砲モデルハンドル
	int m_handle;
	// 位置
	VECTOR m_pos       = VGet(0.0f, 0.0f, 0.0f);
	ShotData m_shotData{};
	// 当たり判定データ
	std::vector<ObjectData> m_collShotData {};
	std::vector<ObjectData> m_collEnemyData{};
	// メンバ関数ポインタ
	void (ObstacleBase::* m_updateFunc)();
	// 最初のショット打ち出しまでのフレームカウント
	int m_shotFirstDelayFrameCount;
	// ショットクラス
	std::list<ShotBase*>m_pShot;
	// ショット再放出までのフレームカウント
	int m_shootFrameCount;
	// ショットを撃つかどうか
	bool m_isShot;
	// ショットの数
	int m_countShotNum;
	// 自身の生成番号
	int m_myNo;

	bool isDead = true;
	int no = -1;
};