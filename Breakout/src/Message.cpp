#include "Message.h"

bool Message::ShouldClose()
{
	return msg.message == WM_QUIT;
}

bool Message::Peek()
{
	return PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE);
}

void Message::Dispatch()
{
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}
