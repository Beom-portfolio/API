#pragma once
#include "scene.h"


class CStage:
	public CScene
{
private:
	CGameObject*	pObject;
	CGameObject*	pEnemy;
	CGameObject*	pItem;

	DWORD	m_dwTime;
	int		m_iTime;
//UI
public:
	
	static bool		m_bPistolInfiniteBullet;

	static bool		m_bHeavy;
	static int		m_iHeavyBullet;

	static bool		m_bGranade;
	static int		m_iGranadeBullet;

	static int		m_iLife;

	static bool		m_bZombie;
	static bool		m_bZombieDeadCheck;

//몬스터 소환
public:
	bool	m_bFirstCast;
	bool	m_bSecondCast;
	bool	m_bThirdCast;
	bool	m_bForthCast;
	bool	m_bFifthCast;

public:
	virtual void Initialize(void);
	virtual int  Update(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);


public:
	void MonsterSpawn(void);


public:
	CStage(void);
	virtual ~CStage(void);
};
