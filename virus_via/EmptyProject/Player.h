#pragma once
#include "DXUT.h"
#include <vector>

using namespace std;

class Player
{
public:
	Player();
	virtual ~Player();

	void Render();
	void Update();
	void playerMove(D3DXVECTOR2 pos);
	void SetPosition();
	void clearPlayer();
	void Load();
	void visitingReturn();

	int score;
	int px, py;
	int hp;
	int gage;
	int maxHp;
	int maxGage;
	int move;
	int speed;
	bool visiting;
	bool press;
	bool setProperties;

	int prevTime;
	int currentTime;


	bool dead;
	bool clear;

	D3DXVECTOR2 startPos;
	vector<D3DXVECTOR2> visitingPos;

	LPDIRECT3DTEXTURE9* playerTex;
	LPDIRECT3DTEXTURE9* playerHpTex;
	LPDIRECT3DTEXTURE9* playerGageTex;
	
	LPD3DXSPRITE sprite;
};

