#include "pch.h"
#include "MainGame.h"
#include "player.h"
#include "Image.h"

RECT back = RectMake(0, 0, WINSIZEX, WINSIZEY);

/*
Initialize : 초기화
앞으로 게임을 시작하기 전에 초기화 및 생성은 여기서 진행
게임 시작하기 전에 딱 한번만 실행되는 함수
*/
void MainGame::Init()
{
	SetTimer(_hWnd, 1, 10, NULL);

	mBackBuffer = new Image();
	mBackBuffer->CreateEmpty(WINSIZEX, WINSIZEY);

	IMAGEMANAGER->LoadFromFile(L"bkground", Resources(L"bkground.bmp"), WINSIZEX, WINSIZEY, true);
	IMAGEMANAGER->LoadFromFile(L"player", Resources(L"player.bmp"), 60, 2160, 1, 36, true);
	IMAGEMANAGER->LoadFromFile(L"dynamite", Resources(L"dynamite.bmp"), 60, 480, 1, 8, true);
	IMAGEMANAGER->LoadFromFile(L"aim", Resources(L"aim.bmp"), 32,33, true);

	mPlayer = new player();
	mPlayer->Init();
}

/*
Release : 메모리 해제할 때 불러주는 함수
유니티라면 OnDestroy
해당 클래스 인스턴스가 메모리 해제 될 때 단 한번 호출해주는 녀석
*/
void MainGame::Release()
{
	KillTimer(_hWnd, 1);//타이머 꺼주자

	Random::ReleaseInstance();	//싱글톤 인스턴스 삭제

	SafeDelete(mBackBuffer);

	mPlayer->Release();
	SafeDelete(mPlayer);

}

/*
Update : 매 프레임 실행되는 함수, 여기서 연산 처리 한다.
*/
void MainGame::Update()
{
	/*
	포트리스 캐릭터 하나 띄우고, 포트리스 배경 하나 띄우고,
	캐릭터가 포탄을 쏨, 포탄이 지면에 닿으면 지면이 파인다(둥글게)
	*/
	
	mPlayer->Update();
	
	bkground::GetInstance()->Update();
	cursor::GetInstance()->Update();
}


/*
Render : 매 프레임 실행되는 함수, Update가 끝나고 Render가 실행된다.
화면에 그려주는 것들은 전부 여기서 처리

매개변수 hdc : 윈도우 창의 HDC가 들어옴
*/
void MainGame::Render(HDC hdc)
{
	//백버퍼의 HDC 가져온다
	HDC backDC = mBackBuffer->GetHDC();
	//HDC 영역을 특정 색으로 밀어버리는 녀석
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	// ==================================================
	{
		HBRUSH newb = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
		HBRUSH oldb = (HBRUSH)SelectObject(backDC, newb);
		RenderRect(backDC, back);
		SelectObject(backDC, oldb);
		DeleteObject(newb);

		bkground::GetInstance()->Render(backDC);
		cursor::GetInstance()->Render(backDC);

		mPlayer->Render(backDC);
		
	}
	//====================================================
	//후면버퍼 내용을 윈도우 창에 고속 복사
	mBackBuffer->Render(hdc, 0, 0);
}

