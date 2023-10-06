#pragma once
#include <DxLib.h>
#include <vector>
#include "../../Util/ObjectData.h"
#include "../../Util/ObstructSelectNo.h"

class ObstacleBase;
class ObstacleManager
{
public:
	ObstacleManager();
	virtual ~ObstacleManager();

	void Init();
	void End();
	/// <summary>
	/// �I�������I�u�W�F�N�g�𐶐�
	/// </summary>
	/// <param name="pos">  �ݒu�ʒu</param>
	/// <param name="obsNo">�ݒu����I�u�W�F�N�gID</param>
	/// <param name="no">   �ݒu���Ԃ̔ԍ�</param>
	/// <param name="mapCihpX">   �}�b�v�`�b�v��ł�X�ԍ�</param>
	/// <param name="mapCihpY">   �}�b�v�`�b�v��ł�Y�ԍ�</param>
	void Create(VECTOR pos, int obsNo, int no, int mapCihpX, int mapCihpY);
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
	// ��������I�u�W�F�N�g��T��
	void SetPowerUpPos(ObstructSelectNo no,int mapChipX, int mapChipY);

private:
	std::vector<ObstacleBase*>m_pObstacle;
};

