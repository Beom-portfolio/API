#include "StdAfx.h"
#include "Player.h"

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize(void)
{

}

int  CPlayer::Update(void)
{
	return 0;
}

void CPlayer::Render(HDC _hdc)
{
	Rectangle(_hdc, 100, 100, 200, 200);
}

void CPlayer::Release(void)
{

}