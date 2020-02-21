#include "StdAfx.h"
#include "ObjMgr.h"
#include "Player.h"

INIT_SINGLETON(CObjMgr);

CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
	Release();
}

void CObjMgr::Initialize(void)
{
	m_listObject[OBJ_PLAYER].push_back(new CPlayer);
}

int CObjMgr::Update(void)
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		list<CGameObject*>::iterator iter		 = m_listObject[i].begin();
		list<CGameObject*>::iterator iter_end	 = m_listObject[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->Update();
		}
	}

	return 0;
}

void CObjMgr::Render(HDC _hdc)
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		list<CGameObject*>::iterator iter		 = m_listObject[i].begin();
		list<CGameObject*>::iterator iter_end	 = m_listObject[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			(*iter)->Render(_hdc);
		}
	}
}

void CObjMgr::Release(void)
{
	for(size_t i = 0; i < OBJ_END; ++i)
	{
		list<CGameObject*>::iterator iter	  = m_listObject[i].begin();
		list<CGameObject*>::iterator iter_end = m_listObject[i].end();

		for(iter; iter != iter_end; ++iter)
		{
			delete (*iter);
			*iter = NULL;
		}
		m_listObject[i].clear();
	}
}

void CObjMgr::AddGameObject(CGameObject* pObject, eObjectType eType)
{
	m_listObject[eType].push_back(pObject);
}

int CObjMgr::FindObjectState(eObjectType eType)
{
	list<CGameObject*>::iterator iter	  = m_listObject[eType].begin();
	list<CGameObject*>::iterator iter_end = m_listObject[eType].end();

	for(iter; iter != iter_end; ++iter)
	{
		int iResult = (*iter)->Update();

		if(iResult != 0)
		{
			return iResult;
		}
	}

	return 0;
}
