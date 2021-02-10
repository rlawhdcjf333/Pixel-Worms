#include "pch.h"
#include "MainGame.h"
#include "playerManager.h"
#include "Image.h"

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

	IMAGEMANAGER->LoadFromFile(L"back", Resources(L"back.bmp"), WINSIZEX * 2, WINSIZEY * 2, false);
	IMAGEMANAGER->LoadFromFile(L"bkground", Resources(L"bkground.bmp"), WINSIZEX*2, WINSIZEY*2, true);
	IMAGEMANAGER->LoadFromFile(L"player", Resources(L"player.bmp"), 60, 2160, 1, 36, true);
	IMAGEMANAGER->LoadFromFile(L"dynamite", Resources(L"dynamite.bmp"), 60, 480, 1, 8, true);
	IMAGEMANAGER->LoadFromFile(L"aim", Resources(L"aim.bmp"), 32,33, true);

	mBack = IMAGEMANAGER->FindImage(L"back");

	mPlayerList = new playerManager();
	mPlayerList->Init();

	Camera::GetInstance()->Init();

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

	mPlayerList->Release();

	SafeDelete(mPlayerList);

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
	
	mPlayerList->Update();

	Camera::GetInstance()->Update();
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
		mBack->Render(backDC, -CAMERAX, -CAMERAY);
		bkground::GetInstance()->Render(backDC);
		cursor::GetInstance()->Render(backDC);

		mPlayerList->Render(backDC);
		
		SetBkMode(backDC, OPAQUE);
		wstring copyright = L"Copyright @ �������Ϲ���";
		TextOut(backDC, 1100, 700, copyright.c_str(), copyright.size());


	}
	//====================================================
	//�ĸ���� ������ ������ â�� ��� ����
	mBackBuffer->Render(hdc, 0, 0);
}

