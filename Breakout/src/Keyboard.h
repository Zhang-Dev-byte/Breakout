#pragma once
#include <queue>

/* The unknown key */
#define KEY_UNKNOWN            -1
enum Key {
	/* Printable keys */
	SPACE = 32,
	APOSTROPHE = 39,  /* ' */
	COMMA = 44,  /* , */
	MINUS = 45,  /* - */
	PERIOD = 46,  /* . */
	SLASH = 47,  /* / */
	K0 = 48,
	K1 = 49,
	K2 = 50,
	K3 = 51,
	K4 = 52,
	K5 = 53,
	K6 = 54,
	K7 = 55,
	K8 = 56,
	K9 = 57,
	SEMICOLON = 59,  /* ; */
	EQUAL = 61,  /* = */
	A = 65,
	B = 66,
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	H = 72,
	I = 73,
	J = 74,
	K = 75,
	L = 76,
	M = 77,
	N = 78,
	O = 79,
	P = 80,
	Q = 81,
	R = 82,
	S = 83,
	T = 84,
	U = 85,
	V = 86,
	W = 87,
	X = 88,
	Y = 89,
	Z = 90,
	LBRACKET = 91,  /* [ */
	BACKSLASH = 92,  /* \ */
	RBRACKET = 93,  /* ] */
	GRAVE = 96,  /* ` */
	WORLD_1 = 161, /* non-US #1 */
	WORLD_2 = 162, /* non-US #2 */

	/* Function keys */
	ESCAPE = 256,
	ENTER = 257,
	TAB = 258,
	BACKSPACE = 259,
	INSERT = 260,
	KDELETE = 261,
	RIGHT = 262,
	LEFT = 263,
	DOWN = 264,
	UP = 265,
	PAGE_UP = 266,
	PAGE_DOWN = 267,
	HOME = 268,
	END = 269,
	CAPS_LOCK = 280,
	SCROLL_LOCK = 281,
	NUM_LOCK = 282,
	PRINT_SCREEN = 283,
	PAUSE = 284,
	F1 = 290,
	F2 = 291,
	F3 = 292,
	F4 = 293,
	F5 = 294,
	F6 = 295,
	F7 = 296,
	F8 = 297,
	F9 = 298,
	F10 = 299,
	F11 = 300,
	F12 = 301,
	F13 = 302,
	F14 = 303,
	F15 = 304,
	F16 = 305,
	F17 = 306,
	F18 = 307,
	F19 = 308,
	F20 = 309,
	F21 = 310,
	F22 = 311,
	F23 = 312,
	F24 = 313,
	F25 = 314,
	KP0 = 320,
	KP1 = 321,
	KP2 = 322,
	KP3 = 323,
	KP4 = 324,
	KP5 = 325,
	KP6 = 326,
	KP7 = 327,
	KP8 = 328,
	KP9 = 329,
	DIVIDE = 331,
	MULTIPLY = 332,
	SUBTRACT = 333,
	ADD = 334,
	LSHIFT = 340,
	LCONTROL = 341,
	LALT = 342,
	LSUPER = 343,
	RSHIFT = 344,
	RCONTROL = 345,
	RALT = 346,
	RSUPER = 347,
	MENU = 348
};

class Keyboard {
public:
	static void OnKeyPressed(int key);
	static void OnKeyReleased(int key);
	static bool GetKey(int key);
	static bool GetKeyUp(int key);
private:
	static std::queue<int> events;
	static std::queue<int> eventsup;
};
