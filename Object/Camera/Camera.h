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

private:
	// カメラの位置
	VECTOR m_pos;
	// マウスの位置
	VECTOR m_mouseScreenPos;
	VECTOR m_mouseWorldPos;
	// ターゲット
	VECTOR m_targetPos;
	// トラッキングをおこなうかどうか
	Tracking trackingData;
};

