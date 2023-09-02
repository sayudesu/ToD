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

	void SetTarGetPos(VECTOR pos);

	VECTOR GetPos(int num);

	std::vector<std::vector<CollData>> GetCollDatas();

	// �z��̐���n��
	int GetNormalNum();

private:
	std::vector<std::shared_ptr<ObstacleBase>>m_pObstacle;
	// �o�������J�E���g���܂�
	int m_count;
};

