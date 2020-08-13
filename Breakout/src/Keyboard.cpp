#include "Keyboard.h"

std::queue<int> Keyboard::events = std::queue<int>();
std::queue<int> Keyboard::eventsup = std::queue<int>();
void Keyboard::OnKeyPressed(int key)
{
	events.push(key);
}

void Keyboard::OnKeyReleased(int key)
{
	eventsup.push(key);
}

bool Keyboard::GetKey(int key)
{
	if (!events.empty()) {
		if (events.front() == key) {
			events.pop();
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Keyboard::GetKeyUp(int key)
{
	if (!eventsup.empty()) {
		if (eventsup.front() == key) {
			eventsup.pop();
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
