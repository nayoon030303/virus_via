#include "DXUT.h"
#include "GameOver.h"
#include "global.h"

GameOver::GameOver()
{
    D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

    resultTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gameover.png",
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
        resultTex
    );

}

GameOver::~GameOver()
{
    sprite->Release();
    (*resultTex)->Release();
    
    

}

void GameOver::Render()
{
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR3 pos(0, 0, 0);
    sprite->Draw(*resultTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();

}


void GameOver::Update()
{
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
    {
        gameSystem->clear();
        gameSystem->player->clearPlayer();
        pageManager.MakeTitlePage();
    }
}