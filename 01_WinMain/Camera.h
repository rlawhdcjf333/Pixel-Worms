#pragma once
class player;

class Camera
{
	Singleton(Camera)

	float mX;
	float mY;

	RECT rc;

	float mAngle;
	float mVec;

	player* mPlayer;

	int mTimer;
public:

	inline const float GetX() { return mX; }
	inline const float GetY() { return mY; }
	inline const RECT& GetRc() { return rc; }

	void SetPlayer(player* ptr) { mPlayer = ptr; }

	void Init();
	void Update();
	void Panning();
	void Render(HDC hdc);
};

