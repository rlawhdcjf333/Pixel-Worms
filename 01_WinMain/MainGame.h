#pragma once


class Image;
class playerManager;

class MainGame
{
	Image* mBackBuffer;	//후면버퍼(건들지마라)
	Image* mBack;

	playerManager* mPlayerList;


public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

