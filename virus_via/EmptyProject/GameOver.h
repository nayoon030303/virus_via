#pragma once
#include "page.h"

class GameOver:public Page
{
public:
	GameOver();
	virtual ~GameOver();
	void Render()override;
	void Update()override;

	ID3DXFont* font;
	LPDIRECT3DTEXTURE9* resultTex;
	

	LPD3DXSPRITE sprite;
};

