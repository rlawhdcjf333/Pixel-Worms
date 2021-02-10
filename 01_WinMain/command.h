#pragma once
class player;

//턴제 구현에 나는 명령패턴을 쓰겠음

class command
{
	Singleton(command)

	player* mPlayer;
	

public:

	inline const player* GetPlayer() { return mPlayer; }
	inline void SetPlayer(player* ptr) { mPlayer = ptr; }
	void ExecuteCommand();


};

