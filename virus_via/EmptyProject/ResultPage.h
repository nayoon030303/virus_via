#pragma once
#include "page.h"

class ResultPage:public Page
{
public:
	ResultPage();
	virtual ~ResultPage();
	void Render()override;
	void Update()override;

	ID3DXFont* font;
	LPDIRECT3DTEXTURE9* resultTex;
	LPDIRECT3DTEXTURE9* nextTex;
	LPDIRECT3DTEXTURE9* nextBorderTex;
	LPDIRECT3DTEXTURE9* nextState;

	LPD3DXSPRITE sprite;
};

