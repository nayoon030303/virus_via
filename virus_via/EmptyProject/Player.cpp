#include "DXUT.h"
#include "Player.h"
#include "global.h"
#include <random>
#include <time.h>

using namespace std;

Player::Player()
{
   
    score = 0;
    dead = false;
    clear = false;
    px = 0;
    py = 0;
    speed = 7;
    visiting = false;
    press = false;
    setProperties = false;
    maxHp = 7;
    maxGage = 300 * speed;
    hp = maxHp;
    gage = maxGage;

    SetPosition();
  
}


Player::~Player()
{
    sprite->Release();
    (*playerTex)->Release();
    (*playerHpTex)->Release();
    (*playerGageTex)->Release();
}


void Player::Update()
{
    if (hp <= 0)
        dead = true;

    if (hp < -1)
        hp = 0;
    if (gage < -1)
        gage = 0;
    

    //3초안에 새로운 영역을 만들지 않는다면 hp-=1
    currentTime = (GetTickCount() - prevTime) / 1000.0f;
    if ((currentTime) >= 3.0f)
    {
        prevTime = GetTickCount();
        if (map[py * WIDTH + px] != MAP_PROPERTY_VISITING)
        {
            if (hp > 0)
            {
                hp -= 1;
            }
            
        }
     
    }

    if (px < 0)
        px = 0;
    if (py < 0)
        py = 0;
    if (px >= WIDTH)
        px = WIDTH - 1;
    if (py >= HEIGHT)
        py = HEIGHT - 1;

    /*CONTROL*/
    if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0)
    {
      
        press = true;
    }
    else 
    {
    
        press = false;
        if (visiting)
        {
            
            visitingReturn();
        }
    }

  
    /*left*/
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000) != 0)
    {
        playerMove(D3DXVECTOR2(-1, 0));
    }
    /*right*/
    else if ((GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0)
    {
        playerMove(D3DXVECTOR2(+1, 0));
    }
    /*left*/
    else if ((GetAsyncKeyState(VK_UP) & 0x8000) != 0)
    {
        playerMove(D3DXVECTOR2(0, -1));
    }
    /*right*/
    else if ((GetAsyncKeyState(VK_DOWN) & 0x8000) != 0)
    {
        playerMove(D3DXVECTOR2(0, +1));
    }
    else {
        if (gage < maxGage)
            gage += 1;
    }
   
 

}

void Player::visitingReturn()
{
    visiting = false;
    px = startPos.x;
    py = startPos.y;
    for (int i = 0; i < visitingPos.size(); ++i)
    {
        int nx = visitingPos[i].x;
        int ny = visitingPos[i].y;

        map[ny * WIDTH + nx] = MAP_PROPERTY_EMPTY;
    }
    visitingPos.clear();
}

void Player::SetPosition()
{

 
    srand(GetTickCount());

    int i = rand() % 4;
    if (i == 0)
    {
        py = 0;
        px = rand() % WIDTH;
    }else if(i==1)
    { 
        py = HEIGHT-1;
        px = rand() % WIDTH;
    }
    else if (i == 2)
    {
        px = rand() % WIDTH;
        px = 0;
    }
    else if (i == 3)
    {
        py = rand() % HEIGHT;
        px = WIDTH - 1;
    }
    
   
    


   /* 
   random_device rd;std::mt19937 gen(rd);
    std::uniform_int_distribution<int>dis1(0, WIDTH);
    std::uniform_int_distribution<int>dis2(0, HEIGHT);
    px = dis1(gen);
    py = dis2(gen);*/
}

void Player::playerMove(D3DXVECTOR2 pos)
{
    

    for (int i = 0; i < speed; ++i)
    {
        int nx = px + pos.x;
        int ny = py + pos.y;

        if (nx < 0 || ny<0 || nx >= WIDTH || ny>=HEIGHT)
        {
            break;
        }
        if (gage <= 0)
        {
            break;
        }

        if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE && map[ny * WIDTH + nx] == MAP_PROPERTY_EDGE)
        {
            px = nx;
            py = ny;
        }
        else if (map[py * WIDTH + px] == MAP_PROPERTY_EDGE && map[ny * WIDTH + nx] == MAP_PROPERTY_EMPTY && press)
        {
            gage -= 1;
            startPos.x = px;
            startPos.y = py;
            px = nx;
            py = ny;
            map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
            visitingPos.push_back(D3DXVECTOR2(px, py));
            visiting = true;
        }
        else if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING && map[ny * WIDTH + nx] == MAP_PROPERTY_EMPTY && press && visiting)
        {
            gage -= 1;
            px = nx;
            py = ny;
            map[py * WIDTH + px] = MAP_PROPERTY_VISITING;
            visitingPos.push_back(D3DXVECTOR2(px, py));
        }
        else if (map[py * WIDTH + px] == MAP_PROPERTY_VISITING && map[ny * WIDTH + nx] == MAP_PROPERTY_EDGE && press && visiting)
        {
            px = nx;
            py = ny;
            visiting = false;
            setProperties = true;
        }

    
    }
}

void Player::Render()
{
    //dwTimeStart = 0;

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR3 pos(START_X +px-4, START_Y+py-4, 0);
    sprite->Draw(*playerTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    pos = D3DXVECTOR3(START_X+150 , 20, 0);
    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = hp*50;
    rc.bottom = 50;
    sprite->Draw(*playerHpTex,&rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    pos = D3DXVECTOR3(START_X + 150, 120, 0);
    rc.left = 0;
    rc.top = 0;
    rc.right = gage * (0.5);
    rc.bottom = 50;
    sprite->Draw(*playerGageTex, &rc, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();


}

void Player::Load()
{
    D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

    playerTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/player.png",
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
        playerTex
    );

    playerGageTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gage.png",
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
        playerGageTex
    );

    playerHpTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/hp.png",
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
        playerHpTex
    );
}\

void Player::clearPlayer()
{
    score = 0;
    dead = false;
    clear = false;
    px = 0;
    py = 0;
    speed = 7;
    visiting = false;
    press = false;
    setProperties = false;
    maxHp = 7;
    maxGage = 300 * speed;
    hp = maxHp;
    gage = maxGage;

    SetPosition();
}