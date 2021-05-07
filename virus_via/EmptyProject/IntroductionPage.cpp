#include "DXUT.h"
#include "global.h"
#include "IntroductionPage.h"

IntroductionPage::IntroductionPage()
{
    D3DXCreateSprite(DXUTGetD3D9Device(), &sprite);

    resultTex = new LPDIRECT3DTEXTURE9();
    D3DXCreateTextureFromFileExA(
        DXUTGetD3D9Device(),
        "source/img/gameintroductionbackground.png",
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

IntroductionPage::~IntroductionPage()
{
    sprite->Release();
    (*resultTex)->Release();
   

}

void IntroductionPage::Render()
{
    sprite->Begin(D3DXSPRITE_ALPHABLEND);
    D3DXVECTOR3 pos(0, 0, 0);
    sprite->Draw(*resultTex, nullptr, nullptr, &pos, D3DCOLOR_ARGB(255, 255, 255, 255));
    sprite->End();

 
}


void IntroductionPage::Update()
{
    if ((GetAsyncKeyState(VK_SPACE) & 0x8000) != 0)
    {
        pageManager.MakeTitlePage();
    }
}