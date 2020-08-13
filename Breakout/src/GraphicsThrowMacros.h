#pragma once
#include <windows.h>
#include <windowsx.h>
#include "dxerr.h"
#include <string>
#include <sstream>
#include <cmath>

#define GFX_THROW_INFO(hrcall) if( FAILED( hr = (hrcall) ) ){ DXGetErrorDescription(hr, desc, sizeof(desc));std::wstringstream wss;wss << "\nLine: ";wss << __LINE__;wss << ", File: ";wss << __FILE__;std::wstring wdesc = desc;wdesc += L"\nGet More info by looking in the output window";wdesc += wss.str();MessageBox(NULL, wdesc.c_str(), TEXT(#hrcall), MB_ICONERROR);__debugbreak(); }