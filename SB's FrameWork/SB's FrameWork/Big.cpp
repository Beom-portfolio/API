#include "StdAfx.h"
#include "Big.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitBmp.h"

CBig::CBig(void)
{
}

CBig::~CBig(void)
{
	Release();
}

void CPlayer::Initialize(void)
{	
	////플레이어 움직임 체크

	m_fTime	   = 0.f;
	m_bJump	   = false;
	m_bJumpDown = false;

	m_fSpeed = 10.f;


	m_bDirection = false;

//시간 지연
	m_Time = GetTickCount();


	m_tInfo = INFO(400, 200, 400, 267);
	m_strName = "PLAYER_STAND_RIGHT";

	m_tFrame = FRAME(0, 3, 0, 100);

	m_dwState = STATE_STAND;
	m_dwPrevState = STATE_STAND;

	m_dwFrameTime = GetTickCount();

}

void CPlayer::FrameMove(void)
{
	if(m_dwState != m_dwPrevState)
	{
		//상태가 변경됨.
		switch(m_dwState)
		{
		case STATE_STAND:
			m_tFrame = FRAME(0, 3, 0, 100);
			break;

		case STATE_WALK:
			m_tFrame = FRAME(0, 11, 0, 50);
			break;

		case STATE_JUMP:
			m_tFrame = FRAME(0, 5, 0, 100);
			break;

		case STATE_SEAT:
			m_tFrame = FRAME(0, 3, 0, 100);
			break;

		case STATE_SEATMOVE:
			m_tFrame = FRAME(0, 6, 0, 100);
			break;

		case STATE_UPSEE:
			m_tFrame = FRAME(0, 3, 0, 100);
			break;

		case STATE_SHOOT:
			m_tFrame = FRAME(0, 8, 0, 40);
			break;

		case STATE_UPSHOOT:
			m_tFrame = FRAME(0, 9, 0, 40);
			break;

		case STATE_SEATSHOOT:
			m_tFrame = FRAME(0, 4, 0, 40);
			break;

		case STATE_JUMPDOWNSHOOT:
			m_tFrame = FRAME(0, 3, 0, 40);
			break;

		case STATE_JUMPDOWNSEE:
			m_tFrame = FRAME(0, 0, 0, 100);
			break;
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

void CPlayer::SetFrame(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	//서있을때
	if(dwKey & KEY_LEFT)
	{
		m_dwState = STATE_WALK;
		m_strName = "PLAYER_WALK_LEFT";

		if(m_bDirection == false)
			m_bDirection = true;

	}

	if(dwKey & KEY_RIGHT)
	{
		m_dwState = STATE_WALK;
		m_strName = "PLAYER_WALK_RIGHT";

		if(m_bDirection == true)
			m_bDirection = false;
	}

	//제자리 점프
	if(dwKey & KEY_SPACE)
	{

		m_dwState = STATE_JUMP;
		
		if(m_bDirection == false)
			m_strName = "PLAYER_JUMP_RIGHT";
		else
			m_strName = "PLAYER_JUMP_LEFT";
		
	}

	//뛰면서 점프
	if(dwKey & KEY_LEFT && dwKey & KEY_SPACE)
	{
		m_dwState = STATE_JUMP;

		m_strName = "PLAYER_JUMPRUN_LEFT";
		
		if(m_bDirection == false)
			m_bDirection = true;
	}

	//뛰면서 점프
	if(dwKey & KEY_RIGHT && dwKey & KEY_SPACE)
	{
		m_dwState = STATE_JUMP;

		m_strName = "PLAYER_JUMPRUN_RIGHT";	
	
		if(m_bDirection == true)
			m_bDirection = false;
	}

	//앉기
	if(dwKey & KEY_DOWN)
	{
		m_dwState = STATE_SEAT;

		if(m_bDirection == false)
			m_strName = "PLAYER_SEAT_RIGHT";
		else
			m_strName = "PLAYER_SEAT_LEFT";
	}

	//앉으면서 앞으로
	if(dwKey & KEY_DOWN && dwKey & KEY_LEFT)
	{
		m_dwState = STATE_SEATMOVE;

		m_strName = "PLAYER_SEATWALK_LEFT";

		if(m_bDirection == false)
			m_bDirection = true;
	}

	if(dwKey & KEY_DOWN && dwKey & KEY_RIGHT)
	{
		m_dwState = STATE_SEATMOVE;

		m_strName = "PLAYER_SEATWALK_RIGHT";

		if(m_bDirection == true)
			m_bDirection = false;
	}

	//위로 볼때
	if(dwKey & KEY_UP)
	{
		m_dwState = STATE_UPSEE;

		if(m_bDirection == false)
			m_strName = "PLAYER_UPSEE_RIGHT";
		else
			m_strName = "PLAYER_UPSEE_LEFT";
	}

	//점프하면서 밑을 볼때
	if(m_bJump == true && dwKey & KEY_DOWN)
	{
		m_dwState = STATE_JUMPDOWNSEE;

		if(m_bDirection == false)
			m_strName = "PLAYER_JUMPDOWNSEE_RIGHT";
		else
			m_strName = "PLAYER_JUMPDOWNSEE_LEFT";
	}

	//총쏘기
	if(dwKey & KEY_CTRL)
	{
		m_dwState = STATE_SHOOT;

		if(m_bDirection == false)
			m_strName = "PLAYER_SHOOT_RIGHT";
		else
			m_strName = "PLAYER_SHOOT_LEFT";
	}
	
	if(dwKey & KEY_DOWN && dwKey & KEY_CTRL)
	{
		m_dwState = STATE_SEATSHOOT;

		if(m_bDirection == false)
			m_strName = "PLAYER_SEATSHOOT_RIGHT";
		else
			m_strName = "PLAYER_SEATSHOOT_LEFT";

	}

	//위로 총쏘기
	if(dwKey & KEY_UP && dwKey & KEY_CTRL)
	{
		m_dwState = STATE_UPSHOOT;

		if(m_bDirection == false)
			m_strName = "PLAYER_UPSHOOT_RIGHT";
		else
			m_strName = "PLAYER_UPSHOOT_LEFT";
	}

	//점프하면서 아래로 총쏘기
	if(m_bJump == true && dwKey & KEY_DOWN && dwKey & KEY_CTRL)
	{
		m_dwState = STATE_JUMPDOWNSHOOT;

		if(m_bDirection == false)
			m_strName = "PLAYER_DOWNSHOOT_RIGHT";
		else
			m_strName = "PLAYER_DOWNSHOOT_LEFT";
	}

	if(dwKey & KEY_N)
	{
		m_dwState = STATE_KNIFEATT;
		
		if(m_bDirection == false)
			m_strName = "PLAYER_KNIFEATT_RIGHT";
		else
			m_strName = "PLAYER_KNIFEATT_LEFT";
	}
}

//키입력
void CPlayer::KeyInput(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(!dwKey)
	{
		if(m_bDirection == false)
		{
			m_dwState = STATE_STAND;
			m_strName = "PLAYER_STAND_RIGHT";
		}
		else
		{
			m_dwState = STATE_STAND;
			m_strName = "PLAYER_STAND_LEFT";
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
	if(m_Time + 600 < GetTickCount())
	{
		if((dwKey & KEY_SPACE))
		{
			m_bJump = true;
			m_fTime = 0.f;
			m_Time = GetTickCount();
		}	
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


void CPlayer::Jump(void)
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

int  CPlayer::Update(void)
{
	KeyInput();		//플레이어 조정
	Jump();			//점프
	SetFrame();
	FrameMove();

	CGameObject::Update();

	return 0;
}

void CPlayer::Render(HDC _hdc)
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

void CPlayer::Release(void)
{

}