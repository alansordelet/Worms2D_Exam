#include "StateManager.h"

StateManager::StateManager()
{
	state = State::MENU;
}
StateManager::~StateManager()
{

}

State StateManager::ChangeState(State _state)
{
	state = _state;
	return state;
}