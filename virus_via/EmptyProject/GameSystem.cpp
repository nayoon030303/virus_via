#include "DXUT.h"
#include "GameSystem.h"
#include "global.h"
#include <stack>
#include "EnemySpeed.h"
#include "EnemySize.h"
#include "EnemyMove.h"
#include "BosEnemy.h"`
#include <random>
#include <time.h>


using namespace std;

GameSystem::GameSystem()
{
  // Load();

    player = new Player();  
    //myMap = 0;
    
  
    /*Map √ ±‚»≠*/
    myMap = 0;
    for (int i = 0; i < WIDTH * HEIGHT; ++i)
    {
        map[i] = MAP_PROPERTY_EMPTY;
        binaryMap[i] = MAP_PROPERTY_EMPTY;
    }
    for (int x = 0; x < WIDTH; ++x)
    {
        map[0 * WIDTH + x] = MAP_PROPERTY_EDGE;
        map[(HEIGHT - 1) * WIDTH + x] = MAP_PROPERTY_EDGE;
        binaryMap[0 * WIDTH + x] = MAP_PROPERTY_VISIT;
        binaryMap[(HEIGHT - 1) * WIDTH + x] = MAP_PROPERTY_VISIT;
        myMap += 2;
    }
    for (int y = 0; y < HEIGHT; ++y)
    {
        map[y * WIDTH + 0] = MAP_PROPERTY_EDGE;
        map[y * WIDTH + (WIDTH - 1)] = MAP_PROPERTY_EDGE;
        binaryMap[y * WIDTH + 0] = MAP_PROPERTY_VISIT;
        binaryMap[y * WIDTH + (WIDTH - 1)] = MAP_PROPERTY_VISIT;
        myMap += 2;
    }
}

GameSystem::~GameSystem()
{
    sprite->Release();
    (*maskTex)->Release();
    (*playerMapTex)->Release();
    (*enemyMapTex)->Release();
    (*dotTex)->Release();
   
}

void GameSystem::clear()
{
    enemies.clear();
    addEnemies();
    myMap = 0;
    for (int i = 0; i < WIDTH * HEIGHT; ++i)
    {
        map[i] = MAP_PROPERTY_EMPTY;
        binaryMap[i] = MAP_PROPERTY_EMPTY;
    }
    for (int x = 0; x < WIDTH; ++x)
    {
        map[0 * WIDTH + x] = MAP_PROPERTY_EDGE;
        map[(HEIGHT - 1) * WIDTH + x] = MAP_PROPERTY_EDGE;
        binaryMap[0 * WIDTH + x] = MAP_PROPERTY_VISIT;
        binaryMap[(HEIGHT - 1) * WIDTH + x] = MAP_PROPERTY_VISIT;
        myMap += 2;
    }
    for (int y = 0; y < HEIGHT; ++y)
    {
        map[y * WIDTH + 0] = MAP_PROPERTY_EDGE;
        map[y * WIDTH + (WIDTH - 1)] = MAP_PROPERTY_EDGE;
        binaryMap[y * WIDTH + 0] = MAP_PROPERTY_VISIT;
        binaryMap[y * WIDTH + (WIDTH - 1)] = MAP_PROPERTY_VISIT;
        myMap += 2;
    }

    maskTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/mask.png",
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
        maskTex
    );
}

void GameSystem::addEnemies()
{
    srand(GetTickCount()+100);
    int px = rand() % (WIDTH - 200) + 100;
    int py = rand() % (HEIGHT - 200) + 100;
    bosEnemy = new BosEnemy(px,py);
    for (int i = 0; i < 3; ++i)
    {
        srand((GetTickCount()+i)+50);
        int px = rand() % (WIDTH - 200) + 100;
        int py = rand() % (HEIGHT - 200) + 100;

        if (i == 0)
        {
            Enemy* enemyspeed = new EnemySpeed(px, py);
            enemies.push_back(enemyspeed);
        }
        else if (i == 1)
        {
            Enemy* enemySize = new EnemySize(px, py);
            enemies.push_back(enemySize);
        }
        else if (i == 2)
        {

            Enemy* enemyMove = new EnemyMove(px, py);
            enemies.push_back(enemyMove);
        }


    }
    
}

void GameSystem::addEnemy()
{
    srand(GetTickCount());
    int px = rand() % (WIDTH - 200) + 100;
    int py = rand() % (HEIGHT - 200) + 100;
    int i = rand() % 3;

    if (i == 0)
    {
        Enemy* enemyspeed = new EnemySpeed(px, py);
        enemies.push_back(enemyspeed);
    }
    else if (i == 1)
    {
        Enemy* enemySize = new EnemySize(px, py);
        enemies.push_back(enemySize);
    }
    else if (i == 2)
    {

        Enemy* enemyMove = new EnemyMove(px, py);
        enemies.push_back(enemyMove);
    }


}

void GameSystem::collistion()
{
    for (auto iter = enemies.begin(); iter != enemies.end();)
    {
        int x = (*iter)->getPos().x;
        int y = (*iter)->getPos().y;
        if (map[y*WIDTH+x] == MAP_PROPERTY_VISITING)
        {
            player->visitingReturn();
            break;
        }
        iter++;
    }

    int x= bosEnemy->getPos().x;
    int y = bosEnemy->getPos().y;

    if (map[y * WIDTH + x] == MAP_PROPERTY_VISITING)
    {
        player->hp -= 5;
        player->visitingReturn();
    }
}

void GameSystem::Update()
{
    if (!player->dead)
    {
        if (player->setProperties)
        {
            SetProperty();
        }
        player->score += myMap;
        
        player->Update();
        
        if (enemies.size() > 0)
        {
            for (auto iter = enemies.begin(); iter != enemies.end();)
            {
                if (!(*iter)->isDead())
                {
                    (*iter)->Update();
                    iter++;
                }
                else
                {
                    player->score += 10;
                    player->maxHp += 2;
                    player->maxGage += 10;
                    player->hp = player->maxHp;
                    player->gage = player->maxGage;
                    (*iter)->~Enemy();
                    iter = enemies.erase(iter);
                }

            }
        }
 
        bosEnemy->Update();

        collistion();
    }
    
 
}

void GameSystem::Render()
{
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR3 pos(START_X, START_Y, 0);
    sprite->Draw(*maskTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();


    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    for (int i = 0; i < player->visitingPos.size(); ++i)
    {
        int x = player->visitingPos[i].x;
        int y = player->visitingPos[i].y;
        D3DXVECTOR3 pos(START_X+x, START_Y+y, 0);
        sprite->Draw(*dotTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    }
    sprite->End();

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
 
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            if (map[y * WIDTH + x] == MAP_PROPERTY_EDGE)
            {
                pos = D3DXVECTOR3(START_X+x, START_Y+y, 0);
                sprite->Draw(*dotTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 0, 0));
            }
    
        }
    } 
    sprite->End();
   

    if (enemies.size() > 0)
    {
        for (auto iter = enemies.begin(); iter != enemies.end();)
        {
            if (!(*iter)->isDead())
            {
                (*iter)->Render();
            }
            else
            {
                int a = 0;
            }
            iter++;
        }
    }
   
    bosEnemy->Render();
    player->Render();


    
}

void GameSystem::FloodFill(int index)
{
    stack<int> stackIndex;
    stackIndex.push(index);

    while (!stackIndex.empty())
    {
        int new_index = stackIndex.top();
        stackIndex.pop();
        int nx = new_index % WIDTH;
        int ny = new_index / WIDTH;

        if (nx < 0)continue;
        if (ny < 0)continue;
        if (nx >= WIDTH)continue;
        if (ny >= HEIGHT)continue;
        if (map[ny * WIDTH + nx] != MAP_PROPERTY_EMPTY)continue;
        map[ny * WIDTH + nx] = MAP_PROPERTY_TEMP;

        stackIndex.push((ny-1) * WIDTH + nx);
        stackIndex.push((ny+1) * WIDTH + nx);
        stackIndex.push(ny * WIDTH + (nx-1));
        stackIndex.push(ny * WIDTH + (nx+1));
    }
    
}

void GameSystem::SetProperty()
{
    int ax = bosEnemy->getPos().x;
    int ay = bosEnemy->getPos().y;
 
   FloodFill(ay*WIDTH+ax);

   for (int i = 0; i < WIDTH * HEIGHT; ++i)
   {
       if (map[i] == MAP_PROPERTY_TEMP)
       {
           binaryMap[i] = MAP_PROPERTY_EMPTY;
       }
       else
       {
           binaryMap[i] = MAP_PROPERTY_VISIT;;
           myMap += 1;
       }
   }

   memcpy(map, binaryMap, WIDTH * HEIGHT * 4);

   RECT tdr = { 0,0,WIDTH,HEIGHT };
   D3DLOCKED_RECT tlr;
   if (SUCCEEDED((*maskTex)->LockRect(0, &tlr, &tdr, 0)))
   {
       DWORD* p = (DWORD*)tlr.pBits;
       for (int i = 0; i < WIDTH * HEIGHT; ++i)
       {
           if (map[i] == MAP_PROPERTY_VISIT)
           {
               p[i] = playerMap[i];
              
           }
       }
       (*maskTex)->UnlockRect(0);
   }
 
   MakeEdge();
   player->visitingPos.clear();
   player->setProperties = false;

}

void GameSystem::MakeEdge()
{
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            if (map[y * WIDTH + x] == MAP_PROPERTY_VISIT)
            {
                if (
                    map[(y - 1) * WIDTH + x] == MAP_PROPERTY_EMPTY ||
                    map[(y + 1) * WIDTH + x] == MAP_PROPERTY_EMPTY ||
                    map[y * WIDTH + (x - 1)] == MAP_PROPERTY_EMPTY ||
                    map[y * WIDTH + (x + 1)] == MAP_PROPERTY_EMPTY ||
                    map[(y - 1) * WIDTH + (x - 1)] == MAP_PROPERTY_EMPTY ||
                    map[(y - 1) * WIDTH + (x + 1)] == MAP_PROPERTY_EMPTY ||
                    map[(y + 1) * WIDTH + (x - 1)] == MAP_PROPERTY_EMPTY ||
                    map[(y + 1) * WIDTH + (x + 1)] == MAP_PROPERTY_EMPTY
                    )
                {
                    map[y * WIDTH + x] = MAP_PROPERTY_EDGE;
                }
             
                
            }
        }
    }
}

void GameSystem::Load()
{
    D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

    dotTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/dot.png",
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
        dotTex
    );

    maskTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/mask.png",
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
        maskTex
    );

    playerMapTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/background.png",
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
        playerMapTex
    );

    enemyMapTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/enemybackground.png",
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
        enemyMapTex
    );

    RECT tdr = { 0,0,WIDTH,HEIGHT };
    D3DLOCKED_RECT tlr;

    if (SUCCEEDED((*playerMapTex)->LockRect(0, &tlr, &tdr, 0)))
    {
        DWORD* p = (DWORD*)tlr.pBits;
        memcpy(playerMap, p, WIDTH * HEIGHT * sizeof(int));
        (*playerMapTex)->UnlockRect(0);
    }

    if (SUCCEEDED((*enemyMapTex)->LockRect(0, &tlr, &tdr, 0)))
    {
        DWORD* p = (DWORD*)tlr.pBits;
        memcpy(enemyMap, p, WIDTH * HEIGHT * sizeof(int));
        (*enemyMapTex)->UnlockRect(0);
    }
}

void GameSystem::deleteData()
{
    delete player;

    for (auto iter = enemies.begin(); iter != enemies.end();)
    {
        delete (*iter);

        iter++;
    }
    delete bosEnemy;
}