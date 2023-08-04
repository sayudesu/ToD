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
	// �ݒu����
	void UpdateSetting();
	// �V���b�g�p�֐�
	void UpdateShot();
	void Draw();

	void GetTarGetPos(VECTOR pos);
private:
	std::vector<std::shared_ptr<ShotBase>>m_pShot;
	EffekseerDrawer* m_pEffect;
	// �ŏ��̃V���b�g�ł��o���܂ł̃t���[���J�E���g
	int m_shotFirstDelayFrameCount;
	// �V���b�g�ĕ��o�܂ł̃t���[���J�E���g
	int m_shootFrameCount;
	// �I�u�W�F�N�g�J���[
	int m_objColor;
	// �����o�֐��|�C���^
	void (ObstacleNormalShot::* m_updateFunc)();
};

