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

	void GetTarGetPos(VECTOR pos);
private:
	std::vector<std::shared_ptr<ShotBase>>m_pShot;
	EffekseerDrawer* m_pEffect;
	// 最初のショット打ち出しまでのフレームカウント
	int m_shotFirstDelayFrameCount;
	// ショット再放出までのフレームカウント
	int m_shootFrameCount;
	// オブジェクトカラー
	int m_objColor;
	// メンバ関数ポインタ
	void (ObstacleNormalShot::* m_updateFunc)();
};

