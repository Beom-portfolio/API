#include "StdAfx.h"
#include "Player.h"
#include "SoundMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BitBmp.h"
#include "CollisionMgr.h"
#include "Factory.h"
#include "Bullet.h"
#include "Granade.h"
#include "Stage.h"
#include "SceneMgr.h"


CPlayer::CPlayer(void)
{

}

CPlayer::CPlayer(float _fx, float _fy)
{
	m_tInfo.fX = _fx;
	m_tInfo.fY = _fy;
	Initialize();
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize(void)
{
	bURTemp = false;
	bULTemp = false;
	bDRTemp  = false;
	bDLTemp = false;

	//CSoundMgr::GetInstance()->LoadSoundFile();

	iCount = 0;

	fTime = GetTickCount();
	fTimeDelayTime = 50;



	//총알
	m_fBarrelX = 60.f;
	m_fBarrelY = 60.f;

	m_ShotTime = GetTickCount();
	m_ThrowTime = GetTickCount();

	////플레이어 움직임 체크
	m_fTime	   = 0.f;
	m_bJump	   = false;

	m_fSpeed = 10.f;


	m_bDirection = false;

//칼
	m_bNifeCheck = false;


//시간 지연
	m_Time = GetTickCount();

	//m_tInfo = INFO(m_tInfo.fX, m_tInfo.fY, 400, 267);

	m_tInfo.fCX = 400;
	m_tInfo.fCY = 267;

	m_strName = "PLAYER_STAND_RIGHT";

	m_tFrame = FRAME(0, 3, 0, 100);

	m_dwState = STATE_STAND;
	m_dwPrevState = STATE_STAND;

	m_dwFrameTime = GetTickCount();
	m_SoundTime   = GetTickCount();


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
			m_tFrame = FRAME(0, 8, 0, 5);
			break;

		case STATE_UPSHOOT:
			m_tFrame = FRAME(0, 9, 0, 5);
			break;

		case STATE_SEATSHOOT:
			m_tFrame = FRAME(0, 4, 0, 30);
			break;

		case STATE_JUMPDOWNSHOOT:
			m_tFrame = FRAME(0, 3, 0, 40);
			break;

		case STATE_JUMPDOWNSEE:
			m_tFrame = FRAME(0, 0, 0, 100);
			break;
	//칼
		case STATE_KNIFEATT:
			m_tFrame = FRAME(0, 5, 0, 40);
			break;

		case STATE_SEATKNIFEATT:
			m_tFrame = FRAME(0, 3, 0, 40);
			break;

	//헤비머신건
		case STATE_MACHINGUNSHOOT:
			m_tFrame = FRAME(0, 3, 0, 20);
			break;

		case STATE_MACHINGUNCROSS:
			m_tFrame = FRAME(0, 1, 0, 50);
			break;

	//수류탄
		case STATE_THROWBOMB:
			m_tFrame = FRAME(0, 5, 0, 40);
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

	if(CStage::m_bHeavy == false)				/////////////////기본 총일때
	{
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
			if(m_SoundTime + 200 <= GetTickCount())
			{
				CSoundMgr::GetInstance()->PlaySound(L"semishoot.wav");
				m_SoundTime = GetTickCount();
			}
		}

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
	}													////////////////////////////////
	else if(CStage::m_bHeavy == true)			//헤비머신건을 먹었을때.
	{
		//서있을때
		if(dwKey & KEY_LEFT)
		{
			m_dwState = STATE_WALK;
			m_strName = "HEAVY_WALK_LEFT";

			if(m_bDirection == false)
				m_bDirection = true;

		}

		if(dwKey & KEY_RIGHT)
		{
			m_dwState = STATE_WALK;
			m_strName = "HEAVY_WALK_RIGHT";

			if(m_bDirection == true)
				m_bDirection = false;
		}

		//제자리 점프
		if(dwKey & KEY_SPACE)
		{
			m_dwState = STATE_JUMP;

			if(m_bDirection == false)
				m_strName = "HEAVY_JUMP_RIGHT";
			else
				m_strName = "HEAVY_JUMP_LEFT";

		}

		//뛰면서 점프
		if(dwKey & KEY_LEFT && dwKey & KEY_SPACE)
		{
			m_dwState = STATE_JUMP;

			m_strName = "HEAVY_RUNJUMP_LEFT";

			if(m_bDirection == false)
				m_bDirection = true;
		}

		if(dwKey & KEY_RIGHT && dwKey & KEY_SPACE)
		{
			m_dwState = STATE_JUMP;

			m_strName = "HEAVY_RUNJUMP_RIGHT";	

			if(m_bDirection == true)
				m_bDirection = false;
		}

		//앉기
		if(dwKey & KEY_DOWN)
		{
			m_dwState = STATE_SEAT;

			if(m_bDirection == false)
				m_strName = "HEAVY_SEAT_RIGHT";
			else
				m_strName = "HEAVY_SEAT_LEFT";
		}

		//앉으면서 앞으로
		if(dwKey & KEY_DOWN && dwKey & KEY_LEFT)
		{
			m_dwState = STATE_SEATMOVE;

			m_strName = "HEAVY_SEATWALK_LEFT";

			if(m_bDirection == false)
				m_bDirection = true;
		}

		if(dwKey & KEY_DOWN && dwKey & KEY_RIGHT)
		{
			m_dwState = STATE_SEATMOVE;

			m_strName = "HEAVY_SEATWALK_RIGHT";

			if(m_bDirection == true)
				m_bDirection = false;
		}

		//위로 볼때
		if(dwKey & KEY_UP)
		{
			m_dwState = STATE_UPSEE;

			if(m_bDirection == false)
				m_strName = "HEAVY_UPSEE_RIGHT";
			else
				m_strName = "HEAVY_UPSEE_LEFT";
		}

		//점프하면서 밑을 볼때
		if(m_bJump == true && dwKey & KEY_DOWN)
		{
			m_dwState = STATE_JUMPDOWNSEE;

			if(m_bDirection == false)
				m_strName = "HEAVY_JUMPDOWN_RIGHT";
			else
				m_strName = "HEAVY_JUMPDOWN_LEFT";
		}

		//총쏘기
	

		if(dwKey & KEY_CTRL)
		{
			
			CSoundMgr::GetInstance()->PlaySound(L"smgshoot.wav");
	
		}

		if(dwKey & KEY_CTRL)
		{
			m_dwState = STATE_MACHINGUNSHOOT;

			if(m_bDirection == false)
				m_strName = "HEAVY_SHOOT_RIGHT";
			else
				m_strName = "HEAVY_SHOOT_LEFT";
		}

		//숙여서 총쏘기
		if(dwKey & KEY_DOWN && dwKey & KEY_CTRL)
		{
			m_dwState = STATE_MACHINGUNSHOOT;

			if(m_bDirection == false)
				m_strName = "HEAVY_SEATSHOOT_RIGHT";
			else
				m_strName = "HEAVY_SEATSHOOT_LEFT";

		}

		//위로 총쏘기
		if(dwKey & KEY_UP && dwKey & KEY_CTRL)
		{
			m_dwState = STATE_MACHINGUNSHOOT;

			if(m_bDirection == false)
				m_strName = "HEAVY_UPSHOOT_RIGHT";
			else
				m_strName = "HEAVY_UPSHOOT_LEFT";
		}

		//점프하면서 아래로 총쏘기
		if(m_bJump == true && dwKey & KEY_DOWN && dwKey & KEY_CTRL)
		{
			m_dwState = STATE_MACHINGUNSHOOT;

			if(m_bDirection == false)
				m_strName = "HEAVY_JUMPDOWNSHOOT_RIGHT";
			else
				m_strName = "HEAVY_JUMPDOWNSHOOT_LEFT";
		}

		//위로 대각선
		if(dwKey & KEY_LEFT && dwKey & KEY_UP && dwKey & KEY_CTRL)
		{
			m_dwState = STATE_MACHINGUNCROSS;

			m_strName ="HEAVY_CROSSUP_LEFT";

			if(m_bDirection == false)
				m_bDirection = true;
		}
		
		if(dwKey & KEY_RIGHT && dwKey & KEY_UP && dwKey & KEY_CTRL)
		{
			m_dwState = STATE_MACHINGUNCROSS;

			m_strName ="HEAVY_CROSSUP_RIGHT";

			if(m_bDirection == true)
				m_bDirection = false;
		}

		//점프시 밑으로 내리면서 대각선
		
		if(m_bJump == true && dwKey & KEY_LEFT && dwKey & KEY_DOWN && dwKey & KEY_CTRL)
		{
			m_dwState = STATE_MACHINGUNCROSS;

			m_strName ="HEAVY_JUMPCROSSDOWN_LEFT";

			if(m_bDirection == false)
				m_bDirection = true;
		}
		
		if(m_bJump == true && dwKey & KEY_RIGHT && dwKey & KEY_DOWN && dwKey & KEY_CTRL)
		{
			m_dwState = STATE_MACHINGUNCROSS;

			m_strName ="HEAVY_JUMPCROSSDOWN_RIGHT";

			if(m_bDirection == true)
				m_bDirection = false;
		}

	}

	/////////////////수류탄////////////////////////////////
	//서서
	if(dwKey & KEY_Z)
	{
		m_dwState = STATE_THROWBOMB;

		if(m_bDirection == false)
				m_strName = "BOMB_THROW_RIGHT";
			else
				m_strName = "BOMB_THROW_LEFT";
	}

	//앉아서
	if(dwKey & KEY_DOWN && dwKey & KEY_Z)
	{
		m_dwState = STATE_THROWBOMB;

		if(m_bDirection == false)
				m_strName = "BOMB_SEATTHROW_RIGHT";
			else
				m_strName = "BOMB_SEATTHROW_LEFT";
	}


	//////////////칼//////////////////////////////////////
	
	if(CCollisionMgr::GetInstance()->CollisionNife(OBJ_PLAYER, OBJ_MONSTER) == false)
	{
		m_bNifeCheck = false;
	}


	if(CCollisionMgr::GetInstance()->CollisionNife(OBJ_PLAYER, OBJ_MONSTER) == true ||
		CCollisionMgr::GetInstance()->CollisionNife(OBJ_PLAYER, OBJ_BOSS) == true
		&& dwKey & KEY_CTRL)	//적이 가까이 왔을시. 조건문을 걸어야 함.
	{


		m_bNifeCheck = true;

		srand(unsigned int(time(NULL)));

		int iRan = rand() % 2;

		m_dwState = STATE_KNIFEATT;

		if(iRan == 1)
		{
			if(m_bDirection == false)
				m_strName = "PLAYER_KNIFEATT_RIGHT";
			else
				m_strName = "PLAYER_KNIFEATT_LEFT";
		}
		else
		{
			if(m_bDirection == false)
				m_strName = "PLAYER_KNIFEATT2_RIGHT";
			else
				m_strName = "PLAYER_KNIFEATT2_LEFT";
		}
	}

	else if(CCollisionMgr::GetInstance()->CollisionNife(OBJ_PLAYER, OBJ_MONSTER) == true ||
	   CCollisionMgr::GetInstance()->CollisionNife(OBJ_PLAYER, OBJ_BOSS) == true
		&& (dwKey & KEY_DOWN && dwKey & KEY_CTRL))	//적이 가까이 왔을시. 조건문을 걸어야 함.
	{
		
		m_bNifeCheck = true;

		srand(unsigned int(time(NULL)));

		int iRan = rand() % 2;

		if(iRan == 1)
		{
			m_dwState = STATE_KNIFEATT;

			if(m_bDirection == false)
				m_strName = "PLAYER_KNIFEDOWNATT_RIGHT";
			else
				m_strName = "PLAYER_KNIFEDOWNATT_LEFT";
		}
		else
		{
			m_dwState = STATE_SEATKNIFEATT;

			if(m_bDirection == false)
				m_strName = "PLAYER_KNIFEDOWNATT2_RIGHT";
			else
				m_strName = "PLAYER_KNIFEDOWNATT2_LEFT";
		}
	}




}

//키입력
void CPlayer::KeyInput(void)
{
	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState();

	if(dwKey & KEY_J)
	{
		m_fSpeed = 100;
	}

	if(!(dwKey))
	{
		m_fSpeed = 10.f;
	}

	if(!(dwKey))
	{
		if(CStage::m_bHeavy == true)
		{
			if(m_bDirection == false)
			{
				m_fBarrelX = 60.f;
				m_fBarrelY = 60.f;
				m_dwState = STATE_STAND;
				m_strName = "HEAVY_STAND_RIGHT";
			}
			else
			{
				m_fBarrelX = -60.f;
				m_fBarrelY = 60.f;
				m_dwState = STATE_STAND;
				m_strName = "HEAVY_STAND_LEFT";
			}
		}
		else if(CStage::m_bHeavy == false)
		{
			if(m_bDirection == false)
			{
				m_fBarrelX = 60.f;
				m_fBarrelY = 60.f;
				m_dwState = STATE_STAND;
				m_strName = "PLAYER_STAND_RIGHT";
			}
			else
			{
				m_fBarrelX = -60.f;
				m_fBarrelY = 60.f;
				m_dwState = STATE_STAND;
				m_strName = "PLAYER_STAND_LEFT";
			}
		}
	}

	////BackGroundX : 15326
	float fBackGroundX = (CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].front())->GetInfo().fCX;
	//
	////BackGroundY : 2080
	float fBackGroundY = (CObjMgr::GetInstance()->GetList()[OBJ_BACKGROUND].front())->GetInfo().fCY;

	if(dwKey & KEY_LEFT)
	{
		m_fBarrelX = -60.f;
		m_fBarrelY = 60.f;
		m_tInfo.fX -= m_fSpeed;
		
		if (m_fBarrelX > 0)
			m_fBarrelX *= -1;

		if(m_ptScroll.x < 0 && m_tInfo.fX < (fBackGroundX - iWINCX / 2.f) )
			m_ptScroll.x += (long)m_fSpeed;
	}

	if(dwKey & KEY_RIGHT)
	{
		m_fBarrelX = 60.f;
		m_fBarrelY = 60.f;

		m_tInfo.fX += m_fSpeed;

		if (m_fBarrelX < 0)
			m_fBarrelX *= -1;

		if(m_tInfo.fX >= iWINCX / 2.f && m_ptScroll.x > - (fBackGroundX - iWINCX) )
			m_ptScroll.x -= (long)m_fSpeed;
	}

	//위를 볼때.
	if(dwKey & KEY_UP)
	{
		m_fBarrelX = 0.f;
		m_fBarrelY = 90.f;


	}

	if(!(dwKey & KEY_UP))
	{
		//m_fBarrelX = 60.f;
		//m_fBarrelY = 10.f;
	}

	//쭈그릴때. (점프할때는 실행 안함)
	if(m_bJump == false)
	{
		if(dwKey & KEY_DOWN)
		{
			m_fBarrelY = 40.f;
		
			m_fSpeed = 5.f;
		}
		if(!(dwKey & KEY_DOWN))
		{	
			//m_fBarrelY = 10.f;

			m_fSpeed = 10.f;
		}
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
	if(m_bJump == true)
	{
		if(dwKey & KEY_DOWN)
		{
			if(m_bDirection == false)
			{
				m_fBarrelX = 10.f;
				m_fBarrelY = -80.f;
			}
			else
			{
				m_fBarrelX = -15.f;
				m_fBarrelY = -80.f;
			}
		}
	}
	//else
	//	m_bJumpDown = false;

	//총을 쏠때!
	if(m_bNifeCheck == false)
	{

		if(CStage::m_bHeavy == false)
		{
			if(m_ShotTime + 200 <= GetTickCount())
			{
				//서서
				if(!(dwKey & KEY_UP) && !(dwKey & KEY_DOWN) && dwKey & KEY_CTRL )
				{
					if(m_bDirection == false)
					{
						Shot(m_tInfo.fX + m_fBarrelX, m_tInfo.fY - m_fBarrelY, BULLET_RIGHT, BULLET_PISTOL);
					}
					else
					{
						Shot(m_tInfo.fX + m_fBarrelX, m_tInfo.fY - m_fBarrelY, BULLET_LEFT, BULLET_PISTOL);
					}
				}
				//앉아(지상에서만)
				if(m_bJump == false && dwKey & KEY_DOWN && dwKey & KEY_CTRL)
				{
					if(m_bDirection == false)
					{
						Shot(m_tInfo.fX + m_fBarrelX, m_tInfo.fY - m_fBarrelY, BULLET_RIGHT, BULLET_PISTOL);
					}
					else
					{
						Shot(m_tInfo.fX + m_fBarrelX, m_tInfo.fY - m_fBarrelY, BULLET_LEFT, BULLET_PISTOL);
					}
				}
				//위로
				if(dwKey & KEY_UP && dwKey & KEY_CTRL)
				{
					Shot(m_tInfo.fX + m_fBarrelX, m_tInfo.fY - m_fBarrelY, BULLET_UP, BULLET_PISTOL);
				}
				//아래로(공중에서만)
				if(m_bJump == true && dwKey & KEY_DOWN && dwKey & KEY_CTRL)
				{
					Shot(m_tInfo.fX + m_fBarrelX, m_tInfo.fY - m_fBarrelY, BULLET_DOWN, BULLET_PISTOL);
				}

				m_ShotTime = GetTickCount();
			}

		}
		else
		{
				//서서
				if(!(dwKey & KEY_UP) && !(dwKey & KEY_DOWN) && dwKey & KEY_CTRL )
				{
					if(m_bDirection == false)
					{
						ShotHeavy(m_tInfo.fX + m_fBarrelX , m_tInfo.fY - m_fBarrelY,  BULLET_RIGHT, BULLET_HEAVY, 0, RIGHT);
					}
					else
					{
						ShotHeavy(m_tInfo.fX + m_fBarrelX , m_tInfo.fY - m_fBarrelY,  BULLET_LEFT, BULLET_HEAVY, 0, LEFT);
					}
				}
				//앉아(지상에서만)
				if(m_bJump == false && dwKey & KEY_DOWN && dwKey & KEY_CTRL)
				{
					if(m_bDirection == false)
					{
						ShotHeavy(m_tInfo.fX + m_fBarrelX , m_tInfo.fY - m_fBarrelY - 20,  BULLET_RIGHT, BULLET_HEAVY, 0, RIGHT);
					}
					else
					{
						ShotHeavy(m_tInfo.fX + m_fBarrelX , m_tInfo.fY - m_fBarrelY - 20,  BULLET_LEFT, BULLET_HEAVY, 0, LEFT);
					}
				}
				//위로
				if(!(dwKey & KEY_LEFT) && !(dwKey & KEY_RIGHT) && dwKey & KEY_UP && dwKey & KEY_CTRL)
				{
					if(m_bDirection == false)
					{
						//균형
						ShotHeavy(m_tInfo.fX + m_fBarrelX - 20 , m_tInfo.fY - m_fBarrelY,  BULLET_UP, BULLET_HEAVY, 0, UP);
					}
					else
					{
						ShotHeavy(m_tInfo.fX + m_fBarrelX, m_tInfo.fY - m_fBarrelY,  BULLET_UP, BULLET_HEAVY, 0, UP);
					}
				}
				//아래로(공중에서만)
				if(!(dwKey & KEY_RIGHT) && !(dwKey & KEY_LEFT) && m_bJump == true && dwKey & KEY_DOWN && dwKey & KEY_CTRL)
				{
					ShotHeavy(m_tInfo.fX + m_fBarrelX , m_tInfo.fY - m_fBarrelY,  BULLET_DOWN, BULLET_HEAVY, 0, DOWN);
				}
				
				//대각선	
				if(dwKey & KEY_RIGHT)
				{
					//우 > 위
					if(dwKey & KEY_UP && dwKey & KEY_CTRL)
					{
						bURTemp = true;
					}
					
					//우 > 아래
					if(m_bJump == true && dwKey & KEY_DOWN && dwKey & KEY_CTRL)
					{
						bDRTemp = true;	
					}
				}

				if(dwKey & KEY_LEFT)
				{
					//좌 > 위
					if(dwKey & KEY_UP && dwKey & KEY_CTRL)
					{
						bULTemp = true;
					}
					
					//좌 > 아래
					if(m_bJump == true && dwKey & KEY_DOWN && dwKey & KEY_CTRL)
					{
						bDLTemp = true;
					}
				}
		}

	}
	else
	{	//칼
		//서서
		if(dwKey & KEY_CTRL)
		{
			list<CGameObject*>::iterator iter = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].begin();
			list<CGameObject*>::iterator iter_end = CObjMgr::GetInstance()->GetList()[OBJ_MONSTER].end();

			for(iter; iter != iter_end; ++iter)
			{
				if( CCollisionMgr::GetInstance()->CollisionBullet((*iter)->GetRect(), &m_Rect) == true )
				{
					(*iter)->SetDamage(1);
				}
			}
			
			list<CGameObject*>::iterator iter_B = CObjMgr::GetInstance()->GetList()[OBJ_BOSS].begin();
			list<CGameObject*>::iterator iter_B_end = CObjMgr::GetInstance()->GetList()[OBJ_BOSS].end();

			for(iter_B; iter_B != iter_B_end; ++iter_B)
			{
				if( CCollisionMgr::GetInstance()->CollisionBullet((*iter_B)->GetRect(), &m_Rect) == true )
				{
					(*iter_B)->SetDamage(1);
				}
			}

		}
	}

	//폭탄을 던질때
	if(m_ThrowTime + 300 <= GetTickCount())
	{
		if(dwKey & KEY_Z)
		{
			if(CStage::m_bGranade == true)
			{
				if(m_bDirection == false)
				{
					Throw(m_tInfo.fX + 40, m_tInfo.fY - 30, GRANADE_PLAYER, m_bDirection);
					--CStage::m_iGranadeBullet;
				}
				else
				{
					Throw(m_tInfo.fX - 40, m_tInfo.fY - 30, GRANADE_PLAYER, m_bDirection);
					--CStage::m_iGranadeBullet;
				}
			}
			else
			{
				//없음
			}
		}


		m_ThrowTime = GetTickCount();
	}
	
	//배럴 제자리 위치

}

//점프
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
}

int  CPlayer::Update(void)
{
	//m_tInfo = INFO(m_tInfo.fX, m_tInfo.fY, 400, 267);

	DWORD dwKey = CKeyMgr::GetInstance()->GetKeyState(); 

	CGameObject::Update();

	m_Rect.left = m_Rect.left + 170	 + m_ptScroll.x;
	m_Rect.top  = m_Rect.top  +  40  + m_ptScroll.y;
	m_Rect.right = m_Rect.right - 190 + m_ptScroll.x;
	m_Rect.bottom = m_Rect.bottom - 140 + m_ptScroll.y;;			// 렉트 조정 (충돌처리를 위해)

	SetFrame();
	FrameMove();
	KeyInput();		//플레이어 조정
	Jump();			//점프

	CollisionLine(m_bJump);
	
	////대각선발사
	if(bURTemp)
		CreateUR();
	if(bULTemp)
		CreateUL();
	if(bDRTemp)
		CreateDR();
	if(bDLTemp)
		CreateDL();


	//y 스크롤 조정
	if(m_tInfo.fX >= 5825 && m_tInfo.fX < 6730)
	{
		if(dwKey & KEY_RIGHT)
		{
			m_ptScroll.y -= 2;  
		}
		
		if(dwKey & KEY_LEFT)
		{
			m_ptScroll.y += 2;  
		}
	}

	if(m_tInfo.fX >= 6731 && m_tInfo.fX < 7000)
	{
		if(dwKey & KEY_RIGHT)
		{
			m_ptScroll.y -= 8;  
		}

		if(dwKey & KEY_LEFT)
		{
			m_ptScroll.y += 8;  
		}
	}

	if(m_tInfo.fX >= 7700 && m_tInfo.fX < 7910)
	{
		if(dwKey & KEY_RIGHT)
		{
			m_ptScroll.y -= 20;  
		}

		if(dwKey & KEY_LEFT)
		{
			m_ptScroll.y += 20;  
		}
	}

	if(m_tInfo.fX >= 8600 && m_tInfo.fX < 9040)
	{
		if(dwKey & KEY_RIGHT)
		{
			m_ptScroll.y -= 9;  
		}

		if(dwKey & KEY_LEFT)
		{
			m_ptScroll.y += 9;  
		}
	}

	if(m_tInfo.fX >= 12540 && m_tInfo.fX < 14370)
	{
		if(dwKey & KEY_RIGHT)
		{
			m_ptScroll.y -= 1.5f;  
		}

		if(dwKey & KEY_LEFT)
		{
			m_ptScroll.y += 1.5f;  
		}
	}

	system("cls");
	cout << "X: " << m_tInfo.fX << endl;
	cout << "Y: " << m_tInfo.fY << endl;

	return 0;
}

void CPlayer::Render(HDC _hdc)
{

	/////이미지 출력
	TransparentBlt(_hdc
		,int(m_tInfo.fX - m_tInfo.fCX / 2.f) + m_ptScroll.x
		,int(m_tInfo.fY - m_tInfo.fCY / 2.f) - 50 + m_ptScroll.y
		,(int)m_tInfo.fCX
		,(int)m_tInfo.fCY
		,(*m_mapBmp)[m_strName]->GetMemDC()	
		,int(m_tFrame.iFrameStart * m_tInfo.fCX)			//이미지에서의 시작 위치 X
		,int(m_tFrame.iFrameY * m_tInfo.fCY)			//이미지에서의 시작 위치 Y
		,(int)m_tInfo.fCX		//이미지의 범위 X
		,(int)m_tInfo.fCY		//이미지의 범위 Y
		,RGB(75, 169, 218)  );


	if(GetAsyncKeyState('Q'))
	{
		Rectangle(_hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
		MoveToEx(_hdc, m_tInfo.fX + m_ptScroll.x, m_tInfo.fY , NULL);
		LineTo(_hdc, m_tInfo.fX + m_fBarrelX  + m_ptScroll.x, m_tInfo.fY - m_fBarrelY);
	}

}


void CPlayer::Release(void)
{

}

/////////////////////////////////////////////////////////////////대각선

void CPlayer::CreateUR( void )
{

	if(fTime + fTimeDelayTime < GetTickCount())
	{
		
		switch(iCount)
		{
		case 0:
			ShotHeavy(m_tInfo.fX + 20, m_tInfo.fY - 50,  BULLET_HEAVYDIR, BULLET_HEAVY, 22.5f, RIGHT_UP_1);
			break;

		case 1:
			ShotHeavy(m_tInfo.fX + 20, m_tInfo.fY - 50,  BULLET_HEAVYDIR, BULLET_HEAVY, 45.f, RIGHT_UP_2);
			break;

		case 2:
			ShotHeavy(m_tInfo.fX + 20, m_tInfo.fY - 50,  BULLET_HEAVYDIR, BULLET_HEAVY, 67.5f, RIGHT_UP_3);
			break;
		}

		
		//
		//


		//CObjMgr::GetInstance()->AddGameObject(pBullet, OBJ_BULLET);


		++iCount;
		fTime = GetTickCount();


		if(iCount >= 3)
		{
			bURTemp = false;
			iCount = 0;

		}

	}	
}

void CPlayer::CreateDR( void )
{

	if(fTime + fTimeDelayTime < GetTickCount())
	{
		
		switch(iCount)
		{
		case 0:
			ShotHeavy(m_tInfo.fX, m_tInfo.fY,  BULLET_HEAVYDIR, BULLET_HEAVY, 315.f, RIGHT_DOWN_1);
			break;

		case 1:
			ShotHeavy(m_tInfo.fX, m_tInfo.fY,  BULLET_HEAVYDIR, BULLET_HEAVY, 337.5f, RIGHT_DOWN_2);			
			break;

		case 2:
			ShotHeavy(m_tInfo.fX, m_tInfo.fY,  BULLET_HEAVYDIR, BULLET_HEAVY, 359.f, RIGHT_DOWN_3);
			break;
		}

		
		//
		//


		//CObjMgr::GetInstance()->AddGameObject(pBullet, OBJ_BULLET);


		++iCount;
		fTime = GetTickCount();


		if(iCount >= 3)
		{
			bDRTemp = false;
			iCount = 0;

		}

	}	
}

void CPlayer::CreateUL( void )
{

	if(fTime + fTimeDelayTime < GetTickCount())
	{
		
		switch(iCount)
		{

		case 0:
			ShotHeavy(m_tInfo.fX - 20, m_tInfo.fY - 50,  BULLET_HEAVYDIR, BULLET_HEAVY, 112.5f, LEFT_UP_1);
			break;

		case 1:
			ShotHeavy(m_tInfo.fX - 20, m_tInfo.fY - 50,  BULLET_HEAVYDIR, BULLET_HEAVY, 135.f, LEFT_UP_2);
			break;

		case 2:
			ShotHeavy(m_tInfo.fX - 20, m_tInfo.fY - 50,  BULLET_HEAVYDIR, BULLET_HEAVY, 157.5f, LEFT_UP_3);
			break;
		}

		
		//
		//


		//CObjMgr::GetInstance()->AddGameObject(pBullet, OBJ_BULLET);


		++iCount;
		fTime = GetTickCount();


		if(iCount >= 3)
		{
			bULTemp = false;
			iCount = 0;

		}

	}	
}

void CPlayer::CreateDL( void )
{

	if(fTime + fTimeDelayTime < GetTickCount())
	{
		
		switch(iCount)
		{
		case 0:
			ShotHeavy(m_tInfo.fX, m_tInfo.fY,  BULLET_HEAVYDIR, BULLET_HEAVY, 202.5f, LEFT_DOWN_1);
			break;

		case 1:
			ShotHeavy(m_tInfo.fX, m_tInfo.fY,  BULLET_HEAVYDIR, BULLET_HEAVY, 225.f, LEFT_DOWN_2);
			break;

		case 2:
			ShotHeavy(m_tInfo.fX, m_tInfo.fY,  BULLET_HEAVYDIR, BULLET_HEAVY, 247.5f, LEFT_DOWN_3);
			break;
		}

		
		//
		//


		//CObjMgr::GetInstance()->AddGameObject(pBullet, OBJ_BULLET);


		++iCount;
		fTime = GetTickCount();


		if(iCount >= 3)
		{
			bDLTemp = false;
			iCount = 0;

		}

	}	
}

///////////////////////

void CPlayer::Shot(float fx, float fy, eBulletDirection _eDir, eBulletType _eType)
{
	pBullet = new CBullet(fx + m_ptScroll.x, fy + m_ptScroll.y, _eDir, _eType);

	CObjMgr::GetInstance()->AddGameObject(pBullet, OBJ_BULLET);
}

void CPlayer::ShotHeavy(float fx, float fy, eBulletDirection _eDir, eBulletType _eType, float _fAngle, DWORD _CurState)
{
	pBullet = new CBullet(fx + m_ptScroll.x, fy + m_ptScroll.y, _eDir, _eType, _fAngle, _CurState);

	CObjMgr::GetInstance()->AddGameObject(pBullet, OBJ_BULLET);
}


void CPlayer::Throw(float fx, float fy, eGranadeType _eType, bool Direction)
{
	pGranade = new CGranade(fx + m_ptScroll.x, fy + m_ptScroll.y, _eType, Direction);

	CObjMgr::GetInstance()->AddGameObject(pGranade, OBJ_GRANADE);
}

