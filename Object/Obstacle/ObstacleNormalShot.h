#pragma once
#include "ObstacleBase.h"
#include <vector>
#include <memory>

class ShotBase;
class EffekseerDrawer;
class ObstacleNormalShot : public ObstacleBase
{
public:
	ObstacleNormalShot(VECTOR pos);
	virtual ~ObstacleNormalShot();

	void Init();
	void End();
	void Update();
	// 設置準備
	void UpdateSetting();
	// ショット用関数
	void UpdateShot();
	void Draw();

	void SetTarGetPos(VECTOR pos);
private:
	// 大砲モデルハンドル
	int m_hCannon;
	int m_hCannonBaes;
	// ショットの数
	int m_countShotNum;
	// ショットクラス
	std::vector<std::shared_ptr<ShotBase>>m_pShot;
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
};

