#pragma once
class Image;
class projectile;

class player
{
protected:
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
	bool mIsTurnOver;

public:
	void Init();
	void Render(HDC hdc);
	void Release();
	void Update();

	inline bool GetTurnOver() { return mIsTurnOver; }
	inline bool& GetCooldown() { return mCooldown; }
	inline  vector <projectile*>& GetBullets() { return mBullets; }
	inline float& GetX() { return mX; }
	inline float& GetY() { return mY; }
	inline float& GetFiringPower() { return mFiringPower; }
	inline const int GetSpeed() { return mSpeed; }
	inline void SetSpeed(int val) { mSpeed = val; }

};

