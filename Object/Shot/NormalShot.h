#pragma once
#include "ShotBase.h"

class NormalShot : public ShotBase
{
public:
	NormalShot(VECTOR pos, int originNo,int no);
	~NormalShot();

	// 初期化
	void Init(VECTOR taegetPos, VECTOR scale, VECTOR rotation, float radius, float damage, float speed, bool isTracking)override;
	// メモリ解放処理
	void End();
	// 更新処理
	void Update();
	// 描画
	void Draw();
	// オブジェクトを消すかどうか
	bool IsEnabled()const;
	// オブジェクトを消すかどうかを受け取る
	void SetEnabled(bool isEnabled);
	// 判定用データ
	ObjectData GetCollData();
};

