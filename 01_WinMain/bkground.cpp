#include "pch.h"
#include "bkground.h"
#include "Image.h"

void bkground::Init()
{

}

void bkground::Render(HDC hdc)
{
	mImage->Render(hdc, 0-CAMERAX, 0-CAMERAY);
}

void bkground::Update()
{
}

void bkground::Release()
{
}
