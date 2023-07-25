#pragma once
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
private:
	// �m�[�}���G�l�~�[
	std::vector<std::shared_ptr<EnemyBase>>m_pEnemyNormal;
};

