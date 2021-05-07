#include "DXUT.h"
#include "EnemyMove.h"
#include "global.h"
#include <random>

#define ENEMY_1_WIDTH 49
#define ENEMY_1_HEIGHT 34
#define ENEMY_2_WIDTH 70
#define ENEMY_2_HEIGHT 55
#define ENEMY_3_WIDTH 100
#define ENEMY_3_HEIGHT 90

EnemyMove::EnemyMove(int px, int py)
{
    dead = false;

    D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

    enemy1Tex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/enemy3_1.png",
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT_NONPOW2,
        0,
        0,
        D3DFMT_UNKNOWN,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        nullptr,
        nullptr,
        enemy1Tex
    );

    enemy2Tex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/enemy3_2.png",
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT_NONPOW2,
        0,
        0,
        D3DFMT_UNKNOWN,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        nullptr,
        nullptr,
        enemy2Tex
    );

    enemy3Tex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/enemy3_3.png",
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT_NONPOW2,
        0,
        0,
        D3DFMT_UNKNOWN,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        nullptr,
        nullptr,
        enemy3Tex
    );

    speed = 200;

    x = px;
    y = py;

    nx = 1;
    ny = 1;

    enemyState = enemy2Tex;
    width = ENEMY_2_WIDTH;
    height = ENEMY_2_HEIGHT;

    prevTime = GetTickCount();
}

EnemyMove::~EnemyMove()
{
    (*enemy1Tex)->Release();
    (*enemy2Tex)->Release();
    (*enemy3Tex)->Release();
    sprite->Release();
}

void EnemyMove::Render()
{
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR3 pos(START_X + x, START_Y + y, 0);
    sprite->Draw(*enemyState, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();
}

void EnemyMove::Update()
{



    if (map[y * WIDTH + x] == MAP_PROPERTY_VISIT ||
        map[y * WIDTH + x + width] == MAP_PROPERTY_VISIT ||
        map[(y + height) * WIDTH + x] == MAP_PROPERTY_VISIT ||
        map[(y + height) * WIDTH + x + width] == MAP_PROPERTY_VISIT
        )
    {
        dead = true;
    }

    currentTime = (GetTickCount() - prevTime) / 1000.0f;
    if ((currentTime) >= 2.0f)
    {

        for (int i = 0; i < speed; ++i)
        {
            int nextx = x + nx;
            int nexty = y + ny;

            bool returnY = false;
            bool returnX = false;

            for (int i = 1; i < width; ++i)
            {
                if ((map[nexty * WIDTH + nextx + i] == MAP_PROPERTY_EDGE) ||
                    (map[(nexty + height) * WIDTH + nextx + i] == MAP_PROPERTY_EDGE))
                {
                    returnY = true;
                    break;
                }
                else
                {
                    x = nextx;
                    y = nexty;
                }
            }
            for (int i = 1; i < height; ++i)
            {
                if ((map[(nexty + i) * WIDTH + nextx] == MAP_PROPERTY_EDGE) ||
                    (map[(nexty + i) * WIDTH + nextx + width] == MAP_PROPERTY_EDGE))
                {
                    returnX = true;
                    break;
                }
                else
                {
                    x = nextx;
                    y = nexty;
                }
            }

            if (returnY)
                ny *= -1;
            if (returnX)
                nx *= -1;

        }






        prevTime = GetTickCount();
        changeSize();
    }
    

    

  
}

void EnemyMove::changeSize()
{
    srand(GetTickCount());
    int i = rand() % 3;

    if (i == 0)
    {
        enemyState = enemy1Tex;
        width = ENEMY_1_WIDTH;
        height = ENEMY_1_HEIGHT;
    }
    else if (i == 1)
    {
        enemyState = enemy2Tex;
        width = ENEMY_2_WIDTH;
        height = ENEMY_2_HEIGHT;
    }
    else if (i == 2)
    {
        enemyState = enemy3Tex;
        width = ENEMY_3_WIDTH;
        height = ENEMY_3_HEIGHT;
    }
        
  
   
}

bool EnemyMove::isDead()
{
    return dead;
}

D3DXVECTOR2 EnemyMove::getPos()
{
    return D3DXVECTOR2(x, y);
}