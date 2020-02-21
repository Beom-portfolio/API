#include "StdAfx.h"
#include "Heavy.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitBmp.h"

CHeavy::CHeavy(void)
{
}

CHeavy::~CHeavy(void)
{
	Release();
}

void CHeavy::Initialize(void)
{	
	////�÷��̾� ������ üũ

	m_fTime	   = 0.f;
	m_bJump	   = false;

	m_fSpeed = 10.f;


	m_bDirection = false;

//�ð� ����
	

	m_tInfo = CObjMgr::GetInstance()->GetList()[OBJ_PLAYER].front()->GetInfo();
	m_strName = "";

	m_tFrame = FRAME(0, 3, 0, 100);

	m_dwState = STATE_STAND;
	m_dwPrevState = STATE_STAND;

	m_dwFrameTime = GetTickCount();

}

void CHeavy::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//���°� �����.
		switch(m_dwState)
		{
		
		}

		m_dwPrevState = m_dwState;
	}

	if(m_dwFrameTime + m_tFrame.dwFrameTime < GetTickCount())
	{
		m_dwFrameTime = GetTickCount();
		++m_tFrame.iFrameStart;
	}

	if(m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
	{
		/*if(m_dwState == STATE_DEAD)
			m_tFrame.iFrameStart = 3;*/

		m_tFrame.iFrameStart = 0;

		if(m_dwState != STATE_STAND)
		{
			m_dwState = STATE_STAND;
		}
	}

}

void CHeavy::SetFrame(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	
}

//Ű�Է�
void CHeavy::KeyInput(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(!dwKey)
	{
		if(m_bDirection == false)
		{
			m_dwState = STATE_STAND;
			m_strName = "";
		}
		else
		{
			m_dwState = STATE_STAND;
			m_strName = "";
		}
	}

	if(dwKey & KEY_LEFT)
	{
		m_tInfo.fX -= m_fSpeed;

	}

	if(dwKey & KEY_RIGHT)
	{
		m_tInfo.fX += m_fSpeed;	
			
	}

	//���� ����.
	/*if(dwKey & KEY_UP)
	{
		m_bUpCheck = true;
	}
	
	if(!(dwKey & KEY_UP))
	{
		m_bUpCheck = false;
	}*/

	//�ޱ׸���. (�����Ҷ��� ���� ����)
	if(m_bJump == false)
	{
		/*if(dwKey & KEY_DOWN)
		{
			m_tInfo.fCX = 40;
			m_tInfo.fCY = 50;
			m_fSpeed = 5.f;
		}
		if(!(dwKey & KEY_DOWN))
		{
			m_tInfo.fCX = 40;
			m_tInfo.fCY = 80;
			m_fSpeed = 10.f;
		}*/
	}


	//���� ���� �ÿ��� ���� �����ϰ�

		if((dwKey & KEY_SPACE))
		{
			m_bJump = true;
			m_fTime = 0.f;
		}	
	
	//����������.

	////�����ϸ鼭 ���� �ٶ󺼶�.
	//if(m_bJump == true)
	//{
	//	//���̴� �ڼ��� �����ϰ� �ϱ� ����.
	//	m_tInfo.fCX = 40;
	//	m_tInfo.fCY = 80;
	//	m_fSpeed = 10.f;

	//	if((dwKey & KEY_DOWN) && m_bJump == true)
	//	{
	//		m_bJumpDown = true;
	//	}
	//	
	//	if( !(dwKey & KEY_DOWN) )
	//	{
	//		m_bJumpDown = false;
	//	}
	//}
	//else
	//	m_bJumpDown = false;
}


void CHeavy::Jump(void)
{
	if(m_bJump == false)
		return;

	m_fTime += 0.5f;

	//����
	//�� * -sin(90 * PI / 180) + (�߷°��ӵ�:9.8 * �ð� * �ð�) / 2
	//m_tInfo.fY += 10 * -1 + (9.8 * m_fTime * m_fTime) / 2;

	m_tInfo.fY += float(25 * -1 + (0.98 * m_fTime * m_fTime) / 2);
	
	//�ӽ� ����(�����浹 ��)
	if(m_tInfo.fY >= 500)
	{
		m_tInfo.fY = 500;
		m_bJump = false;
		return;
	}
}

int  CHeavy::Update(void)
{
	KeyInput();		//�÷��̾� ����
	Jump();			//����
	SetFrame();
	FrameMove();

	CGameObject::Update();

	return 0;
}

void CHeavy::Render(HDC _hdc)
{

	/////�̹��� ���
	TransparentBlt(_hdc
		,int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		,int(m_tInfo.fY - m_tInfo.fCY / 2.f)
		,(int)m_tInfo.fCX
		,(int)m_tInfo.fCY
		,(*m_mapBmp)[m_strName]->GetMemDC()	
		,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//�̹��������� ���� ��ġ X
		,int(m_tFrame.iFrameY * m_tInfo.fCY)			//�̹��������� ���� ��ġ Y
		,(int)m_tInfo.fCX		//�̹����� ���� X
		,(int)m_tInfo.fCY		//�̹����� ���� Y
		,RGB(75, 169, 218)  );

}

void CHeavy::Release(void)
{

}