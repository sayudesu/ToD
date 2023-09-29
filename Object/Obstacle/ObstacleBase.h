#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/ObjectData.h"
#include <list>

class ShotBase;
// ��Q���N���X�x�[�X
class ObstacleBase
{

public:
	ObstacleBase(VECTOR pos, int no);
	virtual ~ObstacleBase() {};

	virtual void Init() = 0;
	virtual void End();
	virtual void Update();
	virtual void UpdateSetting();
	virtual void UpdateShot();
	virtual void Draw();

	// ��Q���̈ʒu
	virtual VECTOR GetPos() const;
	// �����蔻��f�[�^
	virtual ObjectData GetCollShotDatas(int shotNum);
	// �G�l�~�[�̔���p�f�[�^
	virtual void SetCollEnemyDatas(std::vector<ObjectData> collEnemyData);
	// �V���b�g�̐�
	virtual int GetShotNum();
	// ����Ȃ��V���b�g�̔ԍ����󂯎��
	virtual void SetEraseShotData(std::vector<ObjectData> eraseShotData) {};
	// �^�[�Q�b�g�ʒu���󂯎��
	virtual void SetTarGetPos(VECTOR pos);
	// �K�v�̂Ȃ��V���b�g�ԍ����󂯎��
	virtual void SetShotErase(int shotNum, bool erase);

private:
	// �N��_����
	virtual void TargetPos();
private:
	struct ShotData
	{
		// �n���h���f�[�^
		int handle;
		// �ł��o���܂ł̃t���[���J�E���g
		int shotFrameCount;
		// �^�[�Q�b�g�ʒu
		VECTOR targetPos;
		// �T�C�Y
		VECTOR scale;
		// �p�x
		VECTOR rotation;
		// ���a
		float radius;
		// �_���[�W
		float damage;
		// ���x
		float speed;
		// �ǐ�
		bool isTracking;
		// �ǂ̃V���b�g��
		int id;
	};
protected:
	// ��C���f���n���h��
	int m_handle;
	// �ʒu
	VECTOR m_pos       = VGet(0.0f, 0.0f, 0.0f);
	ShotData m_shotData{};
	// �����蔻��f�[�^
	std::vector<ObjectData> m_collShotData {};
	std::vector<ObjectData> m_collEnemyData{};
	// �����o�֐��|�C���^
	void (ObstacleBase::* m_updateFunc)();
	// �ŏ��̃V���b�g�ł��o���܂ł̃t���[���J�E���g
	int m_shotFirstDelayFrameCount;
	// �V���b�g�N���X
	std::list<ShotBase*>m_pShot;
	// �V���b�g�ĕ��o�܂ł̃t���[���J�E���g
	int m_shootFrameCount;
	// �V���b�g�������ǂ���
	bool m_isShot;
	// �V���b�g�̐�
	int m_countShotNum;
	// ���g�̐����ԍ�
	int m_myNo;

	bool isDead = true;
	int no = -1;
};