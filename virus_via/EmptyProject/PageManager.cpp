#include "DXUT.h"
#include "PageManager.h"
#include "TitlePage.h"
#include "page.h"
#include "FirstGamePage.h"
#include "ResultPage.h"
#include "IntroductionPage.h"
#include "GameOver.h"

PageManager::PageManager()
{

}

PageManager::~PageManager()
{

}

void PageManager::MakeTitlePage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	TitlePage* newPage = new TitlePage();
	currentPage = newPage;
}
\
void PageManager::MakeFristGamePage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	FirstGamePage* newPage = new FirstGamePage();
	currentPage = newPage;
}

void PageManager::MakeSecondGamePage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	TitlePage* newPage = new TitlePage();
	currentPage = newPage;
}

void PageManager::MakeResultPage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	ResultPage* newPage = new ResultPage();
	currentPage = newPage;
}

void PageManager::MakeIntroductionPage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	IntroductionPage* newPage = new IntroductionPage();
	currentPage = newPage;
}

void PageManager::MakeGameOverPage()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
	GameOver* newPage = new GameOver();
	currentPage = newPage;
}

void PageManager::Render()
{
	if (currentPage != nullptr)
	{
		currentPage->Render();
	}
}

void PageManager::Update()
{
	if (currentPage != nullptr)
	{
		currentPage->Update();
	}
}


void PageManager::deleteData()
{
	if (currentPage != nullptr)
	{
		delete currentPage;
	}
}