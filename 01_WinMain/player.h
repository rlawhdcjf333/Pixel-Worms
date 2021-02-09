#pragma once
class Image;
class projectile;

class player
{
	float mX;
	float mY;
	int mSpeed;

	float mFiringPower;

	int mFrameCount;
	int mFrameX;
	int mFrameY;

	Image* mImage;

	RECT rc;

	vector <projectile*> mBullets;

	bool mCooldown;


public:
	void Init();
	void Render(HDC hdc);
	void Release();
	void Update();

	inline const float GetX() { return mX; }
	inline const float GetY() { return mY; }
	inline const float GetFiringPower() { return mFiringPower; }

};

