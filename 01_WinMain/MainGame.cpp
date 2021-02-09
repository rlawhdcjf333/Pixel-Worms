#include "pch.h"
#include "MainGame.h"
#include "player.h"
#include "Image.h"

RECT back = RectMake(0, 0, WINSIZEX, WINSIZEY);

/*
Initialize : �ʱ�ȭ
������ ������ �����ϱ� ���� �ʱ�ȭ �� ������ ���⼭ ����
���� �����ϱ� ���� �� �ѹ��� ����Ǵ� �Լ�
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
Release : �޸� ������ �� �ҷ��ִ� �Լ�
����Ƽ��� OnDestroy
�ش� Ŭ���� �ν��Ͻ��� �޸� ���� �� �� �� �ѹ� ȣ�����ִ� �༮
*/
void MainGame::Release()
{
	KillTimer(_hWnd, 1);//Ÿ�̸� ������

	Random::ReleaseInstance();	//�̱��� �ν��Ͻ� ����

	SafeDelete(mBackBuffer);

	mPlayer->Release();
	SafeDelete(mPlayer);

}

/*
Update : �� ������ ����Ǵ� �Լ�, ���⼭ ���� ó�� �Ѵ�.
*/
void MainGame::Update()
{
	/*
	��Ʈ���� ĳ���� �ϳ� ����, ��Ʈ���� ��� �ϳ� ����,
	ĳ���Ͱ� ��ź�� ��, ��ź�� ���鿡 ������ ������ ���δ�(�ձ۰�)
	*/
	
	mPlayer->Update();
	
	bkground::GetInstance()->Update();
	cursor::GetInstance()->Update();
}


/*
Render : �� ������ ����Ǵ� �Լ�, Update�� ������ Render�� ����ȴ�.
ȭ�鿡 �׷��ִ� �͵��� ���� ���⼭ ó��

�Ű����� hdc : ������ â�� HDC�� ����
*/
void MainGame::Render(HDC hdc)
{
	//������� HDC �����´�
	HDC backDC = mBackBuffer->GetHDC();
	//HDC ������ Ư�� ������ �о������ �༮
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
	//�ĸ���� ������ ������ â�� ��� ����
	mBackBuffer->Render(hdc, 0, 0);
}

