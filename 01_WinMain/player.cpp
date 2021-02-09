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
	cursor::GetInstance()->SetPlayer(this);

	rc = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());

	mFrameCount = 0;
	mFrameX = 0;
	mFrameY = 0;
}

void player::Render(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	wstring power = to_wstring(mFiringPower);
	TextOutW(hdc, rc.left, rc.top, power.c_str(), power.size());

	mImage->ScaleFrameRender(hdc, rc.left, rc.top, mFrameX, mFrameY, mImage->GetFrameWidth(), mImage->GetFrameHeight());

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
	if (Input::GetInstance()->GetKey('W') && mFiringPower<100) mFiringPower+=0.25f;
	if (Input::GetInstance()->GetKey('S') && mFiringPower>10) mFiringPower-=0.25f;

	if (Input::GetInstance()->GetKey('A')) mX -= mSpeed;
	if (Input::GetInstance()->GetKey('D')) mX += mSpeed;

	if (GetPixel(BKGROUND->GetHDC(), mX + 10, mY - 20) != RGB(255, 0, 255)) { mX -= mSpeed; }
	if (GetPixel(BKGROUND->GetHDC(), mX - 10, mY-20) != RGB(255, 0, 255)) {mX += mSpeed;}


	if (Input::GetInstance()->GetKeyDown(VK_LBUTTON) && mCooldown) {

		projectile* bullet = new projectile();
		bullet->SetPlayer(this);
		bullet->Init();
		bullet->SetVec(mFiringPower);
		mBullets.push_back(bullet);

		mCooldown = false;
	}

	for (projectile* elem : mBullets) {
		elem->Update();
	}

	if (mCooldown==false and mBullets[0]->GetCollision()) {
		mCooldown = true;

		//그리고 배경지우개.. 는 projectile에서 하겠음

		SafeDelete(mBullets[0]);
		vector<projectile*> ().swap(mBullets);
	}


	mFrameCount++;
	if (mFrameCount > 10) { mFrameCount = 0; mFrameY++; }
	if (mFrameY > mImage->GetFrameY() - 1) mFrameY = 0;

	rc = RectMakeCenter(mX, mY, mImage->GetFrameWidth(), mImage->GetFrameHeight());


	if (GetPixel(BKGROUND->GetHDC(), mX, rc.bottom-20) == RGB(255, 0, 255)) {

		mY +=3;
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
