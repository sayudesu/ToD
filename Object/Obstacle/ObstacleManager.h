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
	void Create(VECTOR pos);
	void Update();
	void Draw();

	VECTOR GetPos(int num);

	// �񎟌��z����ꎟ���z��ɂ��Ă�Ԃ�
	std::vector<CollData> GetCollDatas();
	// �G�̔���p�f�[�^���󂯎��
	void SetCollEnemyDatas(std::vector<CollData> collEnemyData);

	// �z��̐���n��
	int GetNormalNum();

private:
	std::vector<std::shared_ptr<ObstacleBase>>m_pNormalObstacle;
	// �o�������J�E���g���܂�
	int m_count;
};

