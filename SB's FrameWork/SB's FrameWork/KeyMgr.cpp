#include "StdAfx.h"
#include "KeyMgr.h"
#include "Include.h"

CKeyMgr* CKeyMgr::m_pInstance = NULL;

void CKeyMgr::SetKeyState(void)
{
	m_dwKey = 0;

	//플레이어
	if( GetAsyncKeyState(VK_RIGHT))
	{
		//비트 단위 연산자 : & | ^ ~
		m_dwKey |= KEY_RIGHT;
	}

	if( GetAsyncKeyState(VK_LEFT))
	{
		//비트 단위 연산자 : & | ^ ~
		m_dwKey |= KEY_LEFT;
	}

	if( GetAsyncKeyState(VK_UP))
	{
		//비트 단위 연산자 : & | ^ ~
		m_dwKey |= KEY_UP;
	}

	if( GetAsyncKeyState(VK_DOWN))
	{
		//비트 단위 연산자 : & | ^ ~
		m_dwKey |= KEY_DOWN;
	}

	if( GetAsyncKeyState(VK_SPACE))
	{
		//비트 단위 연산자 : & | ^ ~
		m_dwKey |= KEY_SPACE;
		}


	//메뉴 사용.
	if( GetAsyncKeyState('1'))
	{
		m_dwKey |= KEY_ONE;
	}

	if( GetAsyncKeyState('2'))
	{
		m_dwKey |= KEY_TWO;
	}

	if( GetAsyncKeyState('5'))
	{
		m_dwKey |= KEY_FIVE;
	}

	if( GetAsyncKeyState(VK_RETURN) )
	{
		m_dwKey |= KEY_RETURN;
	}

	//라인에디터
	if( GetAsyncKeyState('H') )
	{
		m_dwKey |= KEY_H;
	}

	if( GetAsyncKeyState('J') )
	{
		m_dwKey |= KEY_J;
	}

	if( GetAsyncKeyState('N') )
	{
		m_dwKey |= KEY_N;
	}
	

	if( GetAsyncKeyState('K') )
	{
		m_dwKey |= KEY_K;
	}

	if( GetAsyncKeyState('L') )
	{
		m_dwKey |= KEY_L;
	}

	if( GetAsyncKeyState('S') )
	{
		m_dwKey |= KEY_S;
	}
	

	
	//총쏘기
	if( GetAsyncKeyState(VK_CONTROL) )
	{
		m_dwKey |= KEY_CTRL;
	}
	
	//폭탄
	if( GetAsyncKeyState('Z') )
	{
		m_dwKey |= KEY_Z;
	}

}

DWORD CKeyMgr::GetKeyState(void)
{
	return m_dwKey;
}

CKeyMgr::CKeyMgr(void)
:m_dwKey(0)
{
}

CKeyMgr::~CKeyMgr(void)
{
}
