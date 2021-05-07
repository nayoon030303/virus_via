#include "DXUT.h"
#include "FirstGamePage.h"
#include "global.h"
#include <atlconv.h>



FirstGamePage::FirstGamePage()
{
    prevTime = GetTickCount();

    D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

    gameBackground = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gamebackground.png",
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
        gameBackground
    );

    D3DXCreateFont(DXUTGetD3D9Device(), 60, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        TEXT("Arial"), &font);
}

FirstGamePage::~FirstGamePage()
{
    sprite->Release();
    (*gameBackground)->Release();
    font->Release();
    
}

void FirstGamePage::Render()
{
    currentTime = (GetTickCount() - prevTime) / 1000.0f;

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR3 pos(0, 0, 0);
    sprite->Draw(*gameBackground, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();
    
    gameSystem->Render();


    USES_CONVERSION;
    char cscore[256];
    sprintf(cscore, "%s", "HP:");
    WCHAR* w = A2W(cscore);
    RECT rc = { START_X,20,500,100 };
    font->DrawText(NULL, w, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


    sprintf(cscore, "%s", "ENP:");
    w = A2W(cscore);
    rc = { START_X,100,500,100 };
    font->DrawText(NULL, w, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

}

void FirstGamePage::Update()
{
    if (!gameSystem->player->dead )
    {
        gameSystem->Update();

      
        //80퍼 센트 맵을 먹으면 끝
        if (gameSystem->myMap > WIDTH * HEIGHT * 80 / 100 && gameSystem->bosEnemy->dead == true)
        {
            prevTime = GetTickCount();
           
           //gameSystem->player->dead = true;
          // gameSystem->player->clear = true;
     
           pageManager.MakeResultPage();

           
        
        }

        //180초 (3분동안)
        if ((currentTime) >= 180.0f)
        {
           gameSystem->player->dead = true;
           gameSystem->player->clear = false;
           pageManager.MakeGameOverPage();
        }
    }
    else
    {
        gameSystem->player->dead = true;
        gameSystem->player->clear = false;
        pageManager.MakeGameOverPage();
    }
    
    
    
    
}