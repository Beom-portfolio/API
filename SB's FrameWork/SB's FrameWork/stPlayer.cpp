#include "StdAfx.h"
#include "stPlayer.h"
#include "SceneMgr.h"
#include "BitBmp.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
#include "GameObject.h"
#include "Player.h"

CstPlayer::CstPlayer(void)
{
}

CstPlayer::~CstPlayer(void)
{
	Release();
}


void CstPlayer::Initialize(void)
{
	m_p = new CPlayer;
	m_pPlayer = m_p->GetInfo();
	//�÷��̾�

	//////////////////�̹��� �ε�/////////////////////
	m_mapBmp.insert( make_pair("DOWN",
		(new CBitBmp)->LoadBmp(L"../Sprite/Player/Right/down.bmp") ) );

	
}

int  CstPlayer::Update(void)
{
	//���ӿ�����Ʈ �Ŵ������� ������Ʈ.
	CObjMgr::GetInstance()->Update();

	return 0;
}

void CstPlayer::Render(HDC _hdc)
{
	//��� ������
	TransparentBlt(_hdc
		,0
		,0
		,iWINCX
		,iWINCY
		,m_mapBmp["DOWN"]->GetMemDC()
		,0
		,0
		,iWINCX
		,iWINCY
		,RGB(0, 255, 0)		);

}

void CstPlayer::Release(void)
{

}
