#pragma once
#include "ObstacleBase.h"
#include <vector>
#include <memory>

class ShotBase;
class EffekseerDrawer;

class ObstacleNormalShot : public ObstacleBase
{
public:
	ObstacleNormalShot(VECTOR pos,int no);
	virtual ~ObstacleNormalShot();

	void Init();
	void End();
	void Update();
	// 設置準備
	void UpdateSetting();
	// ショット用関数
	void UpdateShot();
	void Draw();

	// 判定データ
	std::vector<CollData> GetCollDatas();
	// エネミーの判定用データ
	void SetCollEnemyDatas(std::vector<CollData> collEnemyData);
	// 誰を狙うか
	void TargetPos();
	// ショットの発射数を渡す
	int GetShotNum()override;
	// ターゲット位置を受け取る
	void SetTarGetPos(VECTOR pos);
	// いらないショットのデータを受け取る
	void SetEraseShotData(std::vector<CollData> eraseShotData);
private:
	// 大砲モデルハンドル
	int m_hCannon;
	int m_hCannonBaes;
	// ショットの数
	int m_countShotNum;
	// ショットクラス
	std::vector<ShotBase*>m_pShot;
	// ショットを撃つかどうか
	bool m_isShot;
	// エフェクア使用クラス
	EffekseerDrawer* m_pEffect;
	// メンバ関数ポインタ
	void (ObstacleNormalShot::* m_updateFunc)();
	// 最初のショット打ち出しまでのフレームカウント
	int m_shotFirstDelayFrameCount;
	// ショット再放出までのフレームカウント
	int m_shootFrameCount;
	// オブジェクトカラー
	int m_objColor;
	// 狙う敵を変更するかどうか
	bool m_isTargetChange;
	// 敵の番号
	int m_tempTargetNo;
	// 自身の生成番号
	int m_myNo;
	// 消すデータの番号を保存する
	std::vector<int>m_tempDeleteNo;
};

