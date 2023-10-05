#pragma once
#include "ShotBase.h"

class NormalShot : public ShotBase
{
public:
	NormalShot(VECTOR pos, int originNo,int no);
	~NormalShot();

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="handle">   モデルのハンドル  </param>
	/// <param name="shotFrameCount"></param>
	/// <param name="taegetPos">ターゲット位置    </param>
	/// <param name="scale">    モデルの大きさ    </param>
	/// <param name="rotation"> モデルの角度      </param>
	/// <param name="radius">   当たり判定用の半径</param>
	/// <param name="damage">   攻撃力            </param>
	/// <param name="speed">    速度              </param>
	/// <param name="isTracking">追従させるかどうか</param>
	void Init(int handle, int shotFrameCount,VECTOR taegetPos, VECTOR scale, VECTOR rotation, float radius, float damage, float speed, bool isTracking)override;
	// 判定用データ
	ObjectData GetCollData()override;
};

