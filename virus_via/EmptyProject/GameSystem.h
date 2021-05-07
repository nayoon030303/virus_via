#pragma once
#include "Player.h"
#include <vector>
#include "BosEnemy.h"
class Enemy;

using namespace std;

class GameSystem
{
public:
	GameSystem();
	virtual ~GameSystem();

	void Render();
	void Update();
	void clear();
	void Load();
	void FloodFill(int index);
	void SetProperty();
	void MakeEdge();
	void deleteData();
	void addEnemies();
	void addEnemy();
	void collistion();
	
	int myMap;
	vector<Enemy*>enemies;
	BosEnemy* bosEnemy;

	Player* player;
	LPDIRECT3DTEXTURE9* maskTex;
	LPDIRECT3DTEXTURE9* playerMapTex;
	LPDIRECT3DTEXTURE9* enemyMapTex;
	LPDIRECT3DTEXTURE9* dotTex;
	LPD3DXSPRITE sprite;
};

