#pragma once

typedef struct tagInfo
{
	float fX;
	float fY;
	
	float fCX;
	float fCY;
	
	tagInfo(void){;}

	tagInfo(float _fX, float _fY, float _fCX, float _fCY)
		:fX(_fX),fY(_fY),fCX(_fCX),fCY(_fCY)
	{}

}INFO, *PINFO, *pINFO;

//INFO* pInfo;


typedef struct tagLine
{
	float fStartX;
	float fStartY;

	float fEndX;
	float fEndY;

	tagLine(void){;}

	tagLine(float _fStartX, float _fStartY, float _fEndX, float _fEndY)
		:fStartX(_fStartX),fStartY(_fStartY),fEndX(_fEndX),fEndY(_fEndY)
	{}

}LINE, *PLINE, *pLINE;


typedef struct tagFrame
{
	int iFrameStart;
	int iFrameEnd;

	int	  iFrameY;
	DWORD dwFrameTime;		//스프라이트 재생속도.

	tagFrame(void){;}

	tagFrame(int _iFrameStart, int _iFrameEnd, int _iFrameY, DWORD _dwFrameTime)
		:iFrameStart(_iFrameStart),iFrameEnd(_iFrameEnd),iFrameY(_iFrameY),dwFrameTime(_dwFrameTime)
	{}

}FRAME;

