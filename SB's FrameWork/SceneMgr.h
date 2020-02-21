#pragma once

#include "Include.h"

class CScene;

class CSceneMgr
{
	CREATE_SINGLETON(CSceneMgr);

private:
	CScene* m_pScene;

public:
	void Initialize(void);
	int  Update(void);
	void Render(HDC _hdc);
	void Release(void);

public:
	void SetScene(eSceneState eState);

private:
	CSceneMgr(void);
public:
	~CSceneMgr(void);
};
