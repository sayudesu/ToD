#pragma once
#include <DxLib.h>
#include "../../Util/Tracking.h"
class Camera
{
public:
	Camera();
	virtual ~Camera();

	void Init();
	void End();
	void Update();

	// カメラの位置
	VECTOR SetPos() const;
	// マウスの位置受け取る
	void SetMouseScreenPos(VECTOR mousePos) { m_mouseScreenPos = mousePos; }
	void SetMouseWorldPos(VECTOR mousePos) { m_mouseWorldPos = mousePos; }

	// トラッキングデータを受け取る
	void SeTrackingData(Tracking data);
	// プレイヤーの位置を受け取る
	void SetPosPlayer(VECTOR pos);

private:
	// カメラの位置
	VECTOR m_pos;
	// マウスの位置
	VECTOR m_mouseScreenPos;
	VECTOR m_mouseWorldPos;
	// ターゲット
	VECTOR m_targetPos;
	VECTOR m_targetNowPos;
	
	// トラッキングをおこなうかどうか
	Tracking trackingData;

	VECTOR m_tempPos;
};

