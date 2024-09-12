#pragma once

static enum State {
	INTRO,
	MENU,
	OPTIONS,
	GAME,
	VICTORY
};

class StateManager
{
public:
	StateManager();
	~StateManager();
	State ChangeState(State _state);
	State getState() { return state; }
	
private:
	State state;
};

