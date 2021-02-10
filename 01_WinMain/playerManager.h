#pragma once

class player;
class playerManager
{

	vector <player*> playerList;

public:
	void Init();
	void Render(HDC hdc);
	void Update();
	void Release();


	inline const vector <player*>& GetPlayerList() { return playerList; }
};

