#include "pch.h"
#include "cursor.h"
#include "Image.h"
#include "player.h"

void cursor::Update()
{
	mX = CAMERAX+_mousePosition.x;
	mY = CAMERAY+_mousePosition.y;
	 
	rc = RectMakeCenter(mX, mY, mImage->GetWidth(), mImage->GetHeight());

	if (mPlayer->GetCooldown()) {
		float Angle = Math::GetAngle(mPlayer->GetX(), mPlayer->GetY(), mX, mY);
		float Vec = mPlayer->GetFiringPower();
		for (int i = 0; i < 20; i++) {

			arc[i].x = mPlayer->GetX() + Vec * cosf(Angle) * Vec / 7 * i;
			arc[i].y = mPlayer->GetY() - Vec * sinf(Angle) * Vec / 7 * i + 0.5 * 0.58 * i * i * Vec * Vec / 49;
		}
	}
}

void cursor::Render(HDC hdc)
{

	mImage->Render(hdc, rc.left-CAMERAX, rc.top-CAMERAY);

	for (POINT elem : arc) {
		RenderEllipse(hdc, elem.x-CAMERAX, elem.y-CAMERAY, 2);

	}

}
