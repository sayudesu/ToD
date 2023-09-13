#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/ObjectData.h"

class ObstacleBase;
class ObstacleManager
{
public:
	ObstacleManager();
	virtual ~ObstacleManager();

	void Init();
	void End();
	void Create(VECTOR pos, int obsNo, int no);
	void Update();
	void Draw();

	// �I�u�W�F�N�g�̐���Ԃ�
	int GetNum();
	// �V���b�g�̐���Ԃ��܂�
	int GetShotNum(int objNum);
	// �񎟌��z����ꎟ���z��ɂ��Ă�Ԃ�
	ObjectData GetCollShotDatas(int objNum, int shotNum);
	// �G�̔���p�f�[�^���󂯎��
	void SetCollEnemyDatas(std::vector<ObjectData> collEnemyData);
	// �K�v�̖���shot�̔ԍ����󂯎��
	void SetEraseShotData(std::vector<ObjectData> eraseShotData);
	// �K�v�̂Ȃ��V���b�g�ԍ����󂯎��
	void SetShotErase(int objNum, int shotNum,bool erase);

private:
	std::vector<ObstacleBase*>m_pNormalObstacle;
};

