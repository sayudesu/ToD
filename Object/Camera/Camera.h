#pragma once
#include <DxLib.h>
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
	void GetTargetPos(VECTOR targetPos);
	// マウスの位置受け取る
	void GetMouseScreenPos(VECTOR mousePos) { m_mouseScreenPos = mousePos; }
	void GetMouseWorldPos(VECTOR mousePos) { m_mouseWorldPos = mousePos; }

private:
	// カメラの位置
	VECTOR m_pos;
	// マウスの位置
	VECTOR m_mouseScreenPos;
	VECTOR m_mouseWorldPos;
	// ターゲット
	VECTOR m_targetPos;
};

