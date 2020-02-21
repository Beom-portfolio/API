#pragma once

#include "Include.h"

class CObjMgr
{
CREATE_SINGLETON(CObjMgr);

private:
	list<CGameObject*> m_listObject[OBJ_END];

public:
	void Initialize(void);
	int  Update(void);
	void Render(HDC _hdc);
	void Release(void);

public:
	void AddGameObject(CGameObject* pObject, eObjectType eType);

public:
	list<CGameObject*>* GetList(void)
	{
		return m_listObject;
	}

public:
	int FindObjectState(eObjectType eType);

private:
	CObjMgr(void);
public:
	~CObjMgr(void);
};
