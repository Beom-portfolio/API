#include "StdAfx.h"
#include "Stage.h"

CStage::CStage(void)
{
}

CStage::~CStage(void)
{
	Release();
}

void CStage::Initialize(void)
{

}

int  CStage::Update(void)
{
	return 0;
}

void CStage::Render(HDC _hdc)
{
	Ellipse(_hdc, 400, 400, 500, 500);
}

void CStage::Release(void)
{

}
