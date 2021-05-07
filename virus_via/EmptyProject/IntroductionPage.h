#pragma once
#include "page.h"

class IntroductionPage:public Page
{
public:
	IntroductionPage();
	virtual ~IntroductionPage();
	void Render()override;
	void Update()override;

	
	LPDIRECT3DTEXTURE9* resultTex;

	LPD3DXSPRITE sprite;
};

