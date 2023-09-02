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

	void SetTarGetPos(VECTOR pos);
private:
	// ��C���f���n���h��
	int m_hCannon;
	int m_hCannonBaes;
	// �V���b�g�̐�
	int m_countShotNum;
	// �V���b�g�N���X
	std::vector<std::shared_ptr<ShotBase>>m_pShot;
	// �G�t�F�N�A�g�p�N���X
	EffekseerDrawer* m_pEffect;
	// �����o�֐��|�C���^
	void (ObstacleNormalShot::* m_updateFunc)();
	// �ŏ��̃V���b�g�ł��o���܂ł̃t���[���J�E���g
	int m_shotFirstDelayFrameCount;
	// �V���b�g�ĕ��o�܂ł̃t���[���J�E���g
	int m_shootFrameCount;
	// �I�u�W�F�N�g�J���[
	int m_objColor;
};

