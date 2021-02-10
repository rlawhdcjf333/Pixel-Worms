#include "pch.h"
#include "player.h"
#include "Image.h"
#include "projectile.h"

void player::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"player");

	mX = 100;
	mY = WINSIZEY / 2;

	mFiringPower = 15;
	mSpeed = 3;
	mCooldown = true;
	mIsTurnOver = false;

	rc = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());

	mFrameCount = 0;
	mFrameX = 0;
	mFrameY = 0;
}

void player::Render(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	wstring power = to_wstring(mFiringPower);
	TextOutW(hdc, rc.left-CAMERAX, rc.top-CAMERAY, power.c_str(), power.size());

	mImage->ScaleFrameRender(hdc, rc.left-CAMERAX, rc.top-CAMERAY, mFrameX, mFrameY, mImage->GetFrameWidth(), mImage->GetFrameHeight());

	for (projectile* elem : mBullets) {
		elem->Render(hdc);
	}

}

void player::Release()
{

	for (projectile* elem : mBullets) {

		SafeDelete(elem);
	}

}

void player::Update()
{
	mIsTurnOver = false;

	if(command::GetInstance()->GetPlayer()==this)
	command::GetInstance()->ExecuteCommand();

	if (GetPixel(BKGROUND->GetHDC(), mX + 10, mY - 20) != RGB(255, 0, 255)) { mX -= mSpeed; }
	if (GetPixel(BKGROUND->GetHDC(), mX - 10, mY-20) != RGB(255, 0, 255)) {mX += mSpeed;}

	for (projectile* elem : mBullets) {
		elem->Update();
	}

	if (mCooldown==false and mBullets[0]->GetCollision()) {
		mCooldown = true;

		//그리고 배경지우개.. 는 projectile에서 하겠음

		SafeDelete(mBullets[0]);
		vector<projectile*> ().swap(mBullets);
		mIsTurnOver = true;
	}


	mFrameCount++;
	if (mFrameCount > 10) { mFrameCount = 0; mFrameY++; }
	if (mFrameY > mImage->GetFrameY() - 1) mFrameY = 0;

	rc = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());


	if (GetPixel(BKGROUND->GetHDC(), mX, rc.bottom-20) == RGB(255, 0, 255)) {

		mY +=3; //사실 중력 아님 걍 등속 하강 중
		rc = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());
	}
	else {

		for(int y=mY; y<mY+13;  y++)
			if (GetPixel(BKGROUND->GetHDC(), mX, y) != RGB(255, 0, 255)) {

				mY = y - 10;
				break;
			}
	}


}
