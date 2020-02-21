#pragma once

template<class T>
class CFactory abstract
{
public:
	static CGameObject* CreateGameObject(void)
	{
		CGameObject* pObject = new T;

		pObject->Initialize();

		return pObject;
	}

	static CGameObject* CreateGameObject(float _fx, float _fy)
	{
		CGameObject* pObject = new T;

		pObject->Initialize();
		pObject->SetPos(_fx, _fy);

		return pObject;
	}

};