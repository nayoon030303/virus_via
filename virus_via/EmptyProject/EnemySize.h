#pragma once
#include "Enemy.h"
class EnemySize:public Enemy
{
public:
	EnemySize(int x, int y);
	virtual ~EnemySize();

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

