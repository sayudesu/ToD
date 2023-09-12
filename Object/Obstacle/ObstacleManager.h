#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>
#include "../../Util/CollDatas.h"

class ObstacleBase;
class ObstacleManager
{
public:
	ObstacleManager();
	virtual ~ObstacleManager();

	void Init();
	void End();
	void Create(VECTOR pos, int no);
	void Update();
	void Draw();

	// �I�u�W�F�N�g�̐���Ԃ�
	int GetNum();
	// �V���b�g�̐���Ԃ��܂�
	int GetShotNum(int objNum);
	// �񎟌��z����ꎟ���z��ɂ��Ă�Ԃ�
	CollData GetCollShotDatas(int objNum, int shotNum);
	// �G�̔���p�f�[�^���󂯎��
	void SetCollEnemyDatas(std::vector<CollData> collEnemyData);
	// �K�v�̖���shot�̔ԍ����󂯎��
	void SetEraseShotData(std::vector<CollData> eraseShotData);
	// �K�v�̂Ȃ��V���b�g�ԍ����󂯎��
	void SetShotErase(int objNum, int shotNum,bool erase);

private:
	std::vector<std::shared_ptr<ObstacleBase>>m_pNormalObstacle;
	// �o�������J�E���g���܂�
	int m_countCreate;
};

