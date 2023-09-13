#pragma once
#include "SceneBase.h"
#include <DxLib.h>

class SceneGameClear : public SceneBase
{
public:
	SceneGameClear(int a);
	virtual ~SceneGameClear();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update();
	virtual void Draw();
private:
	int m_handle;
	int m_handleSizeX;
	int m_handleSizeY;
	int m_hScreen;
	VERTEX2DSHADER Vert[6];
};

