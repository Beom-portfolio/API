#ifndef _CONST_H_
#define _CONST_H_

//창 상태
const int iWINCX = 800;
const int iWINCY = 600;

//키 상태

//플레이어
const DWORD KEY_LEFT  = 0x00000001;
const DWORD KEY_RIGHT = 0x00000002;
const DWORD KEY_UP    = 0x00000004;
const DWORD KEY_DOWN  = 0x00000008;
const DWORD KEY_SPACE = 0x00000010;

const DWORD KEY_CTRL  = 0x00000020;
const DWORD KEY_Z	  = 0x00000040;


//메뉴
const DWORD KEY_ONE    = 0x00000080;
const DWORD KEY_TWO    = 0x00000100;
const DWORD KEY_FIVE   = 0x00000200;
const DWORD KEY_RETURN = 0x00000400;


//스크롤을 위한 키
const DWORD KEY_H	   = 0x00000800;
const DWORD KEY_J	   = 0x00001000;
const DWORD KEY_N	   = 0x00002000;

//
const DWORD KEY_K	   = 0x00004000;
const DWORD KEY_L	   = 0x00008000;
const DWORD KEY_S      = 0x00010000;


const DWORD STATE_STAND			 = 0x00000001;		//서있을때
const DWORD STATE_WALK			 = 0x00000002;		//걸을때
const DWORD STATE_JUMP			 = 0x00000004;		//뛸때
const DWORD STATE_SEAT			 = 0x00000008;		//앉을때
const DWORD STATE_UPSEE			 = 0x00000010;		//위로볼때
const DWORD STATE_SHOOT			 = 0x00000020;		//쏠때
const DWORD STATE_UPSHOOT		 = 0x00000040;		//위로 쏠때
const DWORD STATE_SEATSHOOT		 = 0x00000080;		//앉아서 쏠때
const DWORD STATE_JUMPDOWNSHOOT	 = 0x00000100;		//점프밑으로 쏠때
const DWORD STATE_SEATMOVE		 = 0x00000200;		//앉아서 걸을때
const DWORD STATE_JUMPDOWNSEE	 = 0x00000400;		//점프하면서 밑볼때

const DWORD STATE_KNIFEATT			= 0x00000800;	//칼공격
const DWORD STATE_SEATKNIFEATT 		= 0x00001000;	//

const DWORD STATE_MACHINGUNSHOOT	= 0x00002000;	//헤비머신건 제자리
const DWORD STATE_MACHINGUNCROSS	= 0x00004000;	//헤비머신건 대각선

const DWORD STATE_THROWBOMB			= 0x00008000;	//수류탄

const DWORD STATE_DEAD				= 0x00010000;	//죽음

#endif