#pragma once

#include "Include.h"

class CMainGame
{
private:
	HDC		m_hdc;


public:
	void Initialize(void);
	int	 Update(void);
	void Render(void);
	void Release(void);

public:
	CMainGame(void);
	~CMainGame(void);
};
