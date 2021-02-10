#include "pch.h"
#include "Camera.h"
#include "player.h"
#include "projectile.h"

void Camera::Init()
{
	mX = mPlayer->GetX();
	mY = mPlayer->GetY();
	rc = RectMakeCenter(mX, mY, WINSIZEX, WINSIZEY);

}

void Camera::Update()
{
	if (mTimer>0) mTimer--;
	mX = mPlayer->GetX();
	mY = mPlayer->GetY();


	if (!mPlayer->GetCooldown()) {

		mX = mPlayer->GetBullets()[0]->GetX();
		mY = mPlayer->GetBullets()[0]->GetY();

	}
	if (mPlayer->GetCooldown()) {
		mTimer = 100;
	}
	rc = RectMakeCenter(mX, mY, WINSIZEX, WINSIZEY);


	if (rc.left < 0) mX = WINSIZEX / 2;
	if (rc.right > 2560) mX = 2560 - WINSIZEX / 2;
	if (rc.top < 0) mY = WINSIZEY / 2;
	if (rc.bottom > 1440) mY = 1440-WINSIZEY / 2;

	Panning();


	rc = RectMakeCenter(mX, mY, WINSIZEX, WINSIZEY);


}

void Camera::Panning()
{
	if (mTimer > 0 and mTimer<100) {
		mAngle = PI * Random::GetInstance()->RandomInt(200) / 100;
		mVec = Random::GetInstance()->RandomInt(15);

		mX += mVec*cosf(mAngle);
		mY -= mVec*sinf(mAngle);
	}
}

void Camera::Render(HDC hdc)
{


}
