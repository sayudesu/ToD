#pragma once
#include <DxLib.h>
#include <vector>
#include <memory>

class EnemyBase;
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();

	void Init();
	void End();
	void Create(int num);
	void Update();
	void Draw();
	// �m�[�}���G�l�~�[�̈ʒu
	VECTOR SetNormalPos(int num);
	int SetNormalNum();

	void SetMapChip(std::vector<int>mapChip);

private:
	// �m�[�}���G�l�~�[
	std::vector<std::shared_ptr<EnemyBase>>m_pEnemyNormal;
};

