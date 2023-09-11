#pragma once
#include "ObstacleBase.h"
#include <vector>
#include <memory>

class ShotBase;
class EffekseerDrawer;

class ObstacleNormalShot : public ObstacleBase
{
public:
	ObstacleNormalShot(VECTOR pos,int no);
	virtual ~ObstacleNormalShot();

	void Init();
	void End();
	void Update();
	// �ݒu����
	void UpdateSetting();
	// �V���b�g�p�֐�
	void UpdateShot();
	void Draw();

	// ����f�[�^
	std::vector<CollData> GetCollDatas();
	// �G�l�~�[�̔���p�f�[�^
	void SetCollEnemyDatas(std::vector<CollData> collEnemyData);
	// �N��_����
	void TargetPos();
	// �V���b�g�̔��ː���n��
	int GetShotNum()override;
	// �^�[�Q�b�g�ʒu���󂯎��
	void SetTarGetPos(VECTOR pos);
	// ����Ȃ��V���b�g�̃f�[�^���󂯎��
	void SetEraseShotData(std::vector<CollData> eraseShotData);
private:
	// ��C���f���n���h��
	int m_hCannon;
	int m_hCannonBaes;
	// �V���b�g�̐�
	int m_countShotNum;
	// �V���b�g�N���X
	std::vector<ShotBase*>m_pShot;
	// �V���b�g�������ǂ���
	bool m_isShot;
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
	// �_���G��ύX���邩�ǂ���
	bool m_isTargetChange;
	// �G�̔ԍ�
	int m_tempTargetNo;
	// ���g�̐����ԍ�
	int m_myNo;
	// �����f�[�^�̔ԍ���ۑ�����
	std::vector<int>m_tempDeleteNo;
};

