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
	////플레이어 움직임 체크

	m_fTime	   = 0.f;
	m_bJump	   = false;

	m_fSpeed = 10.f;


	m_bDirection = false;

//시간 지연
	

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
		//상태가 변경됨.
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

//키입력
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

	//위를 볼때.
	/*if(dwKey & KEY_UP)
	{
		m_bUpCheck = true;
	}
	
	if(!(dwKey & KEY_UP))
	{
		m_bUpCheck = false;
	}*/

	//쭈그릴때. (점프할때는 실행 안함)
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


	//지상에 있을 시에만 점프 가능하게

		if((dwKey & KEY_SPACE))
		{
			m_bJump = true;
			m_fTime = 0.f;
		}	
	
	//점프했을때.

	////점프하면서 밑을 바라볼때.
	//if(m_bJump == true)
	//{
	//	//숙이는 자세를 안취하게 하기 위함.
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

	//공식
	//힘 * -sin(90 * PI / 180) + (중력가속도:9.8 * 시간 * 시간) / 2
	//m_tInfo.fY += 10 * -1 + (9.8 * m_fTime * m_fTime) / 2;

	m_tInfo.fY += float(25 * -1 + (0.98 * m_fTime * m_fTime) / 2);
	
	//임시 방편(라인충돌 전)
	if(m_tInfo.fY >= 500)
	{
		m_tInfo.fY = 500;
		m_bJump = false;
		return;
	}
}

int  CHeavy::Update(void)
{
	KeyInput();		//플레이어 조정
	Jump();			//점프
	SetFrame();
	FrameMove();

	CGameObject::Update();

	return 0;
}

void CHeavy::Render(HDC _hdc)
{

	/////이미지 출력
	TransparentBlt(_hdc
		,int(m_tInfo.fX - m_tInfo.fCX / 2.f)
		,int(m_tInfo.fY - m_tInfo.fCY / 2.f)
		,(int)m_tInfo.fCX
		,(int)m_tInfo.fCY
		,(*m_mapBmp)[m_strName]->GetMemDC()	
		,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
		,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
		,(int)m_tInfo.fCX		//이미지의 범위 X
		,(int)m_tInfo.fCY		//이미지의 범위 Y
		,RGB(75, 169, 218)  );

}

void CHeavy::Release(void)
{

}