#include "DXUT.h"
#include "ResultPage.h"
#include "global.h"
#include <atlconv.h>

#define NEXT_X 1550
#define NEXT_Y 960
#define NEXT_WIDTH 2220
#define NEXT_HEIGHT 125

ResultPage::ResultPage()
{
    D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

    resultTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/resultbackground.png",
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

    nextTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/result_next.png",
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
        nextTex
    );

    nextBorderTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/result_nextbord.png",
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
        nextBorderTex
    );


    D3DXCreateFont(DXUTGetD3D9Device(), 60, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        TEXT("Arial"), &font);

    nextState = nextTex;
}

ResultPage::~ResultPage()
{
    sprite->Release();
    (*resultTex)->Release();
    (*nextTex)->Release();
    (*nextBorderTex)->Release();
    (font)->Release();
 
}

void ResultPage::Render()
{
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR3 pos(0, 0, 0);
    sprite->Draw(*resultTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();

    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    pos = D3DXVECTOR3(1550, 960, 0);
    sprite->Draw(*nextState, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();

    int score = gameSystem->player->score;
    char cscore[256];
    sprintf(cscore, "%d", score);

    USES_CONVERSION;

    WCHAR* w = A2W(cscore);

    RECT rc = { 705,500,500,100 };
    font->DrawText(NULL, w, -1, &rc, DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

}


void ResultPage::Update()
{
    POINT pt;
    GetCursorPos(&pt);
    ScreenToClient(DXUTGetHWND(), &pt);

    if (pt.x > NEXT_X && pt.x<NEXT_X + NEXT_WIDTH && pt.y> NEXT_Y && pt.y < NEXT_Y + NEXT_HEIGHT)
    {
        nextState = nextBorderTex;
        if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0)
        {
            pageManager.MakeTitlePage();
            gameSystem->clear();
            gameSystem->player->clearPlayer();
        }
    }
    else
    {
        nextState = nextTex;
    }
}