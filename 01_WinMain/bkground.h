#pragma once
class Image;

class bkground
{
	Singleton(bkground)

private:

	Image* mImage = IMAGEMANAGER->FindImage(L"bkground");

public:

	Image* GetImage() { return mImage; }
	void Init();
	void Render(HDC hdc);
	void Update();
	void Release();

};

#define BKGROUND (bkground::GetInstance()->GetImage())
