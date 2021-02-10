#include "pch.h"
#include "playerManager.h"
#include "player.h"


void playerManager::Init()
{

	player* player0 = new player();
	player0->Init();
	playerList.push_back(player0);

	player* player1 = new player();
	player1->Init();
	player1->GetX() = 2400;
	playerList.push_back(player1);

	cursor::GetInstance()->SetPlayer(playerList[0]);
	command::GetInstance()->SetPlayer(playerList[0]);
	Camera::GetInstance()->SetPlayer(playerList[0]);
}

void playerManager::Render(HDC hdc)
{

	playerList[0]->Render(hdc);
	playerList[1]->Render(hdc);

}

void playerManager::Update()
{
	if (playerList[0]->GetTurnOver()) {

		setTurn(playerList[1]);
	}

	if (playerList[1]->GetTurnOver()) {

		setTurn(playerList[0]);
	}

	playerList[0]->Update();
	playerList[1]->Update();

}

void playerManager::Release()
{

	for (player*& elem : playerList) {
		
		elem->Release();
		SafeDelete(elem);
	}
}
