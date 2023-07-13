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

	// �J�����̈ʒu
	VECTOR SetPos() const { return m_pos; }
	// �}�E�X�̈ʒu�󂯎��
	void GetMouseScreenPos(VECTOR mousePos) { m_mouseScreenPos = mousePos; }
	void GetMouseWorldPos(VECTOR mousePos) { m_mouseWorldPos = mousePos; }

private:
	// �J�����̈ʒu
	VECTOR m_pos;
	// �}�E�X�̈ʒu
	VECTOR m_mouseScreenPos;
	VECTOR m_mouseWorldPos;
};

