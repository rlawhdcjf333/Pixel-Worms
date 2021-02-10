#include "pch.h"
#include "projectile.h"
#include "Image.h"
#include "player.h"

void projectile::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"dynamite");

	mX = mPlayer->GetX();
	mY = mPlayer->GetY();

	rc = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());

	mAngle = Math::GetAngle(mX, mY, CAMERAX+_mousePosition.x, CAMERAY+_mousePosition.y);

	IsCollision = false;
}

void projectile::Render(HDC hdc)
{
	mImage->FrameRender(hdc, rc.left-CAMERAX, rc.top-CAMERAY, mFrameX,mFrameY);

}

void projectile::Release()
{
}

void projectile::Update()
{
	mGravity += 0.58f;

	mX += mVec*cosf(mAngle);
	mY -= mVec * sinf(mAngle);
	mY += mGravity;
	rc = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());

	mFrameCount++;
	if (mFrameCount > 10) { mFrameY++; mFrameCount = 0; }

	if (GetPixel(BKGROUND->GetHDC(), mX, mY) != RGB(255, 0, 255)) {

		int ExplosionPower = 50;

		HBRUSH newb = CreateSolidBrush(RGB(255, 0, 255));
		HBRUSH oldb = (HBRUSH)SelectObject(BKGROUND->GetHDC(), newb);
		HPEN newp = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
		HPEN oldp = (HPEN)SelectObject(BKGROUND->GetHDC(), newp);
		RenderEllipse(BKGROUND->GetHDC(), mX, mY, ExplosionPower);
		SelectObject(BKGROUND->GetHDC(), oldp);
		SelectObject(BKGROUND->GetHDC(), oldb);
		DeleteObject(newp);
		DeleteObject(newb);

		IsCollision = true;
	}

}
