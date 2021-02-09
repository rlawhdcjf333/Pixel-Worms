#include "pch.h"
#include "cursor.h"
#include "Image.h"
#include "player.h"

void cursor::Update()
{
	mX = _mousePosition.x;
	mY = _mousePosition.y;
	 
	rc = RectMakeCenter(mX, mY, mImage->GetWidth(), mImage->GetHeight());


	if (rc.top < 0) mY = mImage->GetHeight() / 2;
	if (rc.bottom > WINSIZEY) mY = WINSIZEY-mImage->GetHeight() / 2;
	if (rc.right > WINSIZEX) mX = WINSIZEX - mImage->GetWidth() / 2;
	if (rc.left <0) mX = mImage->GetWidth() / 2;
	rc = RectMakeCenter(mX, mY, mImage->GetWidth(), mImage->GetHeight());

	float Angle = Math::GetAngle(mPlayer->GetX(), mPlayer->GetY(), mX, mY);
	float Vec = mPlayer->GetFiringPower();
	for (int i = 0; i < 20; i++) {

		arc[i].x = mPlayer->GetX() + Vec*cosf(Angle)*Vec/7*i;
		arc[i].y = mPlayer->GetY() - Vec * sinf(Angle) *Vec/7* i + 0.5 * 0.58 * i * i*Vec*Vec/49;
	}

}

void cursor::Render(HDC hdc)
{

	mImage->Render(hdc, rc.left, rc.top);

	for (POINT elem : arc) {
		RenderEllipse(hdc, elem.x, elem.y, 1);

	}

}
