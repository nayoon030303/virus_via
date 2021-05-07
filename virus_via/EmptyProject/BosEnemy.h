#pragma once
#include "Enemy.h"


class BosEnemy :public Enemy
{public:
	BosEnemy(int x, int y);
	virtual ~BosEnemy();

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

