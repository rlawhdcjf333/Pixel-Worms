#pragma once


class Image;
class player;

class MainGame
{
	Image* mBackBuffer;	//�ĸ����(�ǵ�������)

	player* mPlayer;


public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
};

