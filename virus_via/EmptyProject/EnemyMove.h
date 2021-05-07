#pragma once
#include "Enemy.h"
class EnemyMove :public Enemy
{
public:
	EnemyMove(int x, int y);
	virtual ~EnemyMove();

	void Render()override;
	void Update()override;
	D3DXVECTOR2 getPos()override;
	void changeSize();
	bool isDead() override;
	int x, y;
	int nx, ny;
	int speed;
	bool dead;
	int width, height;

	int prevTime;
	int currentTime;


	LPDIRECT3DTEXTURE9* enemy1Tex;
	LPDIRECT3DTEXTURE9* enemy2Tex;
	LPDIRECT3DTEXTURE9* enemy3Tex;
	LPDIRECT3DTEXTURE9* enemyState;
	LPD3DXSPRITE sprite;
};

