#include "DXUT.h"
#include "TitlePage.h"
#include "global.h"

#define TEX_X 1400
#define TEX_Y 440
#define TEX_WIDTH 230
#define TEX_HEIGHT 110
#define START_Y TEX_Y
#define INTRODUCTIO_Y TEX_Y+TEX_HEIGHT
#define RANKING_Y TEX_Y+TEX_HEIGHT*2
#define CREDIT_Y TEX_Y+TEX_HEIGHT*3
#define EXIT_Y TEX_Y+TEX_HEIGHT*4

TitlePage::TitlePage()
{
    D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

    titleTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/title.png",
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
        titleTex
    );

    startTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gamestart.png",
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
        startTex
    );

    introductionTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gameintroduction.png",
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
        introductionTex
    );

    rankingTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gameranking.png",
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
        rankingTex
    );

    creditTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gamecredit.png",
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
        creditTex
    );

    exitTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gameexit.png",
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
        exitTex
    );
    

    /*border*/
    startBordTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gamestart._bord.png",
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
        startBordTex
    );

    introductionBordTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gameintroduction_bord.png",
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
        introductionBordTex
    );

    rankingBordTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gameranking_bord.png",
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
        rankingBordTex
    );

    creditBordTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gamecredit_bord.png",
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
        creditBordTex
    );

    exitBordTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gameexit_bord.png",
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
        exitBordTex
    );

    startState = startTex;
    introductionState = introductionTex;
    rankingState = rankingTex;
    creditState = creditTex;
    exitState = exitTex;
}

TitlePage::~TitlePage()
{
    (*titleTex)->Release();
    (*startTex)->Release();
    (*introductionTex)->Release();
    (*rankingTex)->Release();
    (*creditTex)->Release();
    (*exitTex)->Release();

    (*startBordTex)->Release();
    (*introductionBordTex)->Release();
    (*rankingBordTex)->Release();
    (*creditBordTex)->Release();
    (*exitBordTex)->Release();

  /*  (*startState)->Release();
    (*introductionState)->Release();
    (*rankingState)->Release();
    (*creditState)->Release();
    (*exitState)->Release();*/

    (*introductionBordTex)->Release();
    (*introductionBordTex)->Release();


    sprite->Release();
}

void TitlePage::Update()
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(DXUTGetHWND(), &pt);

    //start
    if (pt.x > TEX_X && pt.x<TEX_X + TEX_WIDTH && 
        pt.y>START_Y && pt.y < START_Y + TEX_HEIGHT)
    {
        startState = startBordTex;
        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
        {
           /* gameSystem->clear();
            gameSystem->player->clearPlayer();*/
            pageManager.MakeFristGamePage();
        }
    }
    else
    {
        startState = startTex;
    }

    //introduction
    if (pt.x > TEX_X && pt.x<TEX_X + TEX_WIDTH && 
        pt.y>INTRODUCTIO_Y && pt.y < INTRODUCTIO_Y + TEX_HEIGHT)
    {
        introductionState = introductionBordTex;
        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
        {

            pageManager.MakeIntroductionPage();
        }
    }
    else
    {
        introductionState = introductionTex;
    }

    //ranking
    if (pt.x > TEX_X && pt.x<TEX_X + TEX_WIDTH && 
        pt.y>RANKING_Y && pt.y < RANKING_Y + TEX_HEIGHT)
    {
        rankingState = rankingBordTex;
        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
        {

            int a = 0;
        }
    }
    else
    {
        rankingState = rankingTex;
    }

    //credit
    if (pt.x > TEX_X && pt.x<TEX_X + TEX_WIDTH &&
        pt.y>CREDIT_Y && pt.y < CREDIT_Y + TEX_HEIGHT)
    {
        creditState = creditBordTex;
        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
        {

            int a = 0;
        }
    }
    else
    {
        creditState = creditTex;
    }

    //exit
    if (pt.x > TEX_X && pt.x<TEX_X + TEX_WIDTH &&
        pt.y>EXIT_Y && pt.y < EXIT_Y + TEX_HEIGHT)
    {
        exitState = exitBordTex;
        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
        {

            PostQuitMessage(0);
        }
    }
    else
    {
        exitState = exitTex;
    }
    
}

void TitlePage::Render()
{
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR3 pos(0, 0, 0);
    sprite->Draw(*titleTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    pos = D3DXVECTOR3(TEX_X, TEX_Y, 0);
    sprite->Draw(*startState, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    pos = D3DXVECTOR3(TEX_X, TEX_Y+TEX_HEIGHT, 0);
    sprite->Draw(*introductionState, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    pos = D3DXVECTOR3(TEX_X, TEX_Y + TEX_HEIGHT*2, 0);
    sprite->Draw(*rankingState, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    pos = D3DXVECTOR3(TEX_X, TEX_Y + TEX_HEIGHT * 3, 0);
    sprite->Draw(*creditState, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    pos = D3DXVECTOR3(TEX_X, TEX_Y + TEX_HEIGHT * 4, 0);
    sprite->Draw(*exitState, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();


}