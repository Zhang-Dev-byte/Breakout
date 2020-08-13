#pragma once
#include <Windows.h>

class Message {
public:
	bool ShouldClose();
	bool Peek();
	void Dispatch();
private:
	MSG msg;
};