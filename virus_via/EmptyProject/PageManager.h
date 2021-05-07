#pragma once


class Page;

class PageManager
{
public:
	PageManager();
	virtual ~PageManager();

	void Render();
	void Update();
	void MakeTitlePage();
	void MakeFristGamePage();
	void MakeSecondGamePage();
	void MakeResultPage();
	void MakeIntroductionPage();
	void MakeGameOverPage();
	void deleteData();
	Page* currentPage;

};

