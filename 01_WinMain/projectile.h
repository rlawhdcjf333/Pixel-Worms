#pragma once
class Image;
class player;

class projectile
{

	Image* mImage;
	float mX;
	float mY;

	float mAngle;
	float mVec;

	int mFrameCount;
	int mFrameX;
	int mFrameY;

	RECT rc;

	float mGravity;

	bool IsCollision;
	player* mPlayer;

public:

	void Init();
	void Render(HDC hdc);
	void Release();
	void Update();

	inline const bool GetCollision() { return IsCollision; }

	inline void SetPlayer(player* playerptr) { mPlayer = playerptr; }

	inline float const GetVec() { return mVec; }
	inline void const SetVec(float value) { mVec=value; }

};

