#pragma once
class player;

//���� ������ ���� ��������� ������

class command
{
	Singleton(command)

	player* mPlayer;
	

public:

	inline const player* GetPlayer() { return mPlayer; }
	inline void SetPlayer(player* ptr) { mPlayer = ptr; }
	void ExecuteCommand();


};

