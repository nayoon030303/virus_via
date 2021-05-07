#pragma once
#include "DXUT.h"
#include "page.h"

class TitlePage :public Page
{
public:
	TitlePage();
	virtual ~TitlePage();
	void Render()override;
	void Update() override;

	LPDIRECT3DTEXTURE9* titleTex;
	LPDIRECT3DTEXTURE9* startTex;
	LPDIRECT3DTEXTURE9* introductionTex;
	LPDIRECT3DTEXTURE9* rankingTex;
	LPDIRECT3DTEXTURE9* creditTex;
	LPDIRECT3DTEXTURE9* exitTex;

	LPDIRECT3DTEXTURE9* startBordTex;
	LPDIRECT3DTEXTURE9* introductionBordTex;
	LPDIRECT3DTEXTURE9* rankingBordTex;
	LPDIRECT3DTEXTURE9* creditBordTex;
	LPDIRECT3DTEXTURE9* exitBordTex;

	LPDIRECT3DTEXTURE9* startState;
	LPDIRECT3DTEXTURE9* introductionState;
	LPDIRECT3DTEXTURE9* rankingState;
	LPDIRECT3DTEXTURE9* creditState;
	LPDIRECT3DTEXTURE9* exitState;

	LPD3DXSPRITE sprite;
};

