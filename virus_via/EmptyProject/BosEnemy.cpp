#include "DXUT.h"
#include "BosEnemy.h"
#include "global.h"
#define ENEMY_WIDTH 80
#define ENEMY_HEIGHT 80

BosEnemy::BosEnemy(int px, int py)
{
    dead = false;

    D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

    enemyTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/bosenemy.png",
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
        enemyTex
    );

    speed = 3;

    x = px;
    y = py;

    nx = 1;
    ny = 1;
}

BosEnemy::~BosEnemy()
{
    (*enemyTex)->Release();
    sprite->Release();
}

void BosEnemy::Render()
{
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR3 pos(START_X + x, START_Y + y, 0);
    sprite->Draw(*enemyTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();
}

void BosEnemy::Update()
{


    if (map[y * WIDTH + x] == MAP_PROPERTY_VISIT ||
        map[y * WIDTH + x + ENEMY_WIDTH] == MAP_PROPERTY_VISIT ||
        map[(y + ENEMY_HEIGHT) * WIDTH + x] == MAP_PROPERTY_VISIT ||
        map[(y + ENEMY_HEIGHT) * WIDTH + x + ENEMY_WIDTH] == MAP_PROPERTY_VISIT
        )
    {
        dead = true;
    }



    for (int i = 0; i < speed; ++i)
    {
        int nextx = x + nx;
        int nexty = y + ny;

        bool returnY = false;
        bool returnX = false;

        for (int i = 1; i < ENEMY_WIDTH; ++i)
        {
            if ((map[nexty * WIDTH + nextx + i] == MAP_PROPERTY_EDGE) ||
                (map[(nexty + ENEMY_HEIGHT) * WIDTH + nextx + i] == MAP_PROPERTY_EDGE))
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
        for (int i = 1; i < ENEMY_HEIGHT; ++i)
        {
            if ((map[(nexty + i) * WIDTH + nextx] == MAP_PROPERTY_EDGE) ||
                (map[(nexty + i) * WIDTH + nextx + ENEMY_WIDTH] == MAP_PROPERTY_EDGE))
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





}

bool BosEnemy::isDead()
{
    return dead;
}

D3DXVECTOR2 BosEnemy::getPos()
{
    return D3DXVECTOR2(x, y);
}