#pragma once
class Image;
class player;

class cursor
{
	Singleton(cursor)

	Image* mImage= IMAGEMANAGER->FindImage(L"aim");

	float mX;
	float mY;

	RECT rc;

	player* mPlayer;
	POINT arc[20];
	
public:
	void Update();
	void Render(HDC hdc);

	void SetPlayer(player* playerptr) { mPlayer = playerptr; }

};

