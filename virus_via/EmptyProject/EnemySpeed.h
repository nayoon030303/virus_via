#pragma once
#include "Enemy.h"

class EnemySpeed :public Enemy
{
public:
	EnemySpeed(int x, int y);
	virtual ~EnemySpeed();

	void Render()override;
	void Update()override;
	D3DXVECTOR2 getPos()override;
	bool isDead() override;
	int x, y;
	int nx, ny;
	int speed;
	bool dead;

	LPDIRECT3DTEXTURE9* enemyTex;
	LPD3DXSPRITE sprite;
};

