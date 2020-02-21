#include "StdAfx.h"
#include "CollisionMgr.h"
#include "GameObject.h"
#include "ObjMgr.h"
#include "BulletEffect.h"

CCollisionMgr* CCollisionMgr::m_pInstance = NULL;

CCollisionMgr::CCollisionMgr(void)
{
}

CCollisionMgr::~CCollisionMgr(void)
{
}

bool CCollisionMgr::Collision(eObjectType Type1, eObjectType Type2)
{
	RECT rc = {0};


	list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[Type1].begin();
	list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[Type1].end();

	for(iter; iter != iter_end; ++iter)
	{
		list<CGameObject*>::iterator iter_M = CObjMgr::GetInstance()->GetList()[Type2].begin();
		list<CGameObject*>::iterator iter_end_M = CObjMgr::GetInstance()->GetList()[Type2].end();

		for(iter_M; iter_M != iter_end_M; ++iter_M)
		{
			if( IntersectRect( &rc, (*iter)->GetRect(), (*iter_M)->GetRect() ) )
			{
				return true;
			}
		}
		
	}

	return false;
}

//칼로 때리는 모션을 하고 싶을때.

bool CCollisionMgr::CollisionNife(eObjectType Type1, eObjectType Type2)
{
	RECT rc = {0};


	list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[Type1].begin();

	list<CGameObject*>::iterator iter_M = CObjMgr::GetInstance()->GetList()[Type2].begin();
	list<CGameObject*>::iterator iter_end_M = CObjMgr::GetInstance()->GetList()[Type2].end();

		for(iter_M; iter_M != iter_end_M; ++iter_M)
		{
			if( IntersectRect( &rc, (*iter)->GetRect(), (*iter_M)->GetRect() ) )
			{
				return true;
			}
		}
		
	

	return false;
}

bool CCollisionMgr::CollisionBullet(RECT* rect1, RECT* rect2)
{
	RECT rc = {0};

	if( IntersectRect( &rc, rect1, rect2) )
	{
		return true;
	}

	return false;
}