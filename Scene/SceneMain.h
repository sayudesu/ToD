#pragma once
#include "SceneBase.h"

class Camera;
class EnemyManager;
class ObstacleManager;
class Player;
class MapDrawer;

class SceneMain : public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	void Init();
	void End();

	SceneBase* Update();
	void Draw();
private:
	Camera*          m_pCamera;
	EnemyManager*    m_pEnemy;
	ObstacleManager* m_pObstacle;
	Player*          m_pPlayer;
	MapDrawer*		 m_pMap;
};