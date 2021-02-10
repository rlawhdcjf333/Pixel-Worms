#include "pch.h"
#include "command.h"
#include "player.h"
#include "projectile.h"

void command::ExecuteCommand()
{
	if (mPlayer->GetCooldown()) {

		if (Input::GetInstance()->GetKey('W') && mPlayer->GetFiringPower() < 100) mPlayer->GetFiringPower() += 0.25f;
		if (Input::GetInstance()->GetKey('S') && mPlayer->GetFiringPower() > 10) mPlayer->GetFiringPower() -= 0.25f;

		if (Input::GetInstance()->GetKey('A')) mPlayer->GetX() -= mPlayer->GetSpeed();
		if (Input::GetInstance()->GetKey('D')) mPlayer->GetX() += mPlayer->GetSpeed();


		if (Input::GetInstance()->GetKeyDown(VK_LBUTTON) && mPlayer->GetCooldown()) {
		
			projectile* bullet = new projectile();
			bullet->SetPlayer(mPlayer);
			bullet->Init();
			bullet->SetVec(mPlayer->GetFiringPower());
			mPlayer->GetBullets().push_back(bullet);
		
			mPlayer->GetCooldown() = false;
		}

	}
}
