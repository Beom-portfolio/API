#pragma once

#include "Include.h"

class CCollisionMgr
{
CREATE_SINGLETON(CCollisionMgr);

public:
	/*bool CollisionSpehere(CGameObject* pObj1, CGameObject* pObj2);
	bool CollisionSpehere(CGameObject* pObj, eObjectType eType);

	int CollisionRect(CGameObject* pObj, eObjectType eType);*/

	bool Collision(eObjectType Type1, eObjectType Type2);
	
	bool CollisionNife(eObjectType Type1, eObjectType Type2);

	bool CollisionBullet(RECT* rect1,RECT* rect2);

	//void CollsionBulletd(eObjectType Type1, eObjectType Type2);
	//CGameObject* GetCloseMonster(CGameObject* pObj);



private:
	CCollisionMgr(void);
public:
	~CCollisionMgr(void);
};
