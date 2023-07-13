#include "Camera.h"
#include "Util/Pad.h"

namespace
{
	// カメラ初期位置
//	const VECTOR kCameraPos = VGet(0.0f, 300.0f, -100.0f);
	const VECTOR kCameraPos = VGet(0.0f, 500.0f, -0.00001f);
//	const VECTOR kCameraPos = VGet(0.0f, 500.0f, 0.0f);
	// カメラ初期ターゲット位置
	const VECTOR kCameraTargetPos = VGet(0.0f, 0.0f, 0.0f);
	// 視野角
	constexpr float kFov = 60.0f;
	// 視野角計算
	constexpr float kFovCalculation = kFov * DX_PI_F / 180.0f;
}

Camera::Camera():
	m_pos(kCameraPos)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	// どこから、どこまで見えるか
	SetCameraNearFar(100.0f, 2000.0f);
	// どこを居てどこをみるか
	SetCameraPositionAndTarget_UpVecY(m_pos, kCameraTargetPos);
	// 遠近法のセットアップ( ラジアン値に変換しています )
	SetupCamera_Perspective(kFovCalculation);
}

void Camera::End()
{
}

void Camera::Update()
{
	// どこを居てどこをみるか
	SetCameraPositionAndTarget_UpVecY(m_pos, kCameraTargetPos);

	//m_mouseScreenPos.y = 300.0f;
	////m_mouseWorldPos.y = 0.0f;
	//SetCameraPositionAndTarget_UpVecY(m_mouseScreenPos, m_mouseWorldPos);

	//const float cameraSpeed = 10.0f;
	//if (Pad::isPress(PAD_INPUT_UP))
	//{
	//	m_pos.y += cameraSpeed;
	//}
	//else if (Pad::isPress(PAD_INPUT_DOWN))
	//{
	//	m_pos.y -= cameraSpeed;
	//}
}
