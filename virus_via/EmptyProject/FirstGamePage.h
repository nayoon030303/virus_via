#pragma once
#include "DXUT.h"
#include "page.h"
#include "GameSystem.h"


class FirstGamePage:public Page
{
public:	
	FirstGamePage();
	virtual ~FirstGamePage();
	void Render()override;
	void Update() override;


	//GameSystem gameSystem;
	LPDIRECT3DTEXTURE9* gameBackground;
	LPD3DXSPRITE sprite;
	ID3DXFont* font;

	int prevTime;
	int currentTime;

	int time = 0;
};

