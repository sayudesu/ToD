#pragma once
#include "ShotBase.h"

class NormalShot : public ShotBase
{
public:
	NormalShot(VECTOR pos, int originNo,int no);
	~NormalShot();

	// ������
	void Init(VECTOR taegetPos, VECTOR scale, VECTOR rotation, float radius, float damage, float speed, bool isTracking)override;
	// �������������
	void End();
	// �X�V����
	void Update();
	// �`��
	void Draw();
	// �I�u�W�F�N�g���������ǂ���
	bool IsEnabled()const;
	// �I�u�W�F�N�g���������ǂ������󂯎��
	void SetEnabled(bool isEnabled);
	// ����p�f�[�^
	ObjectData GetCollData();
};

