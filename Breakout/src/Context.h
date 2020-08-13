#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
namespace wrl = Microsoft::WRL;
#include "GraphicsThrowMacros.h"
class Context {
public:
	bool Init(HWND hWnd);
private:
	friend wrl::ComPtr<ID3D11Device> GetDevice(Context c);
	friend wrl::ComPtr<ID3D11DeviceContext> GetContext(Context c);
	friend wrl::ComPtr<IDXGISwapChain> GetSwapChain(Context c);
	friend wrl::ComPtr<ID3D11RenderTargetView> GetTarget(Context c);
	wrl::ComPtr<ID3D11Device> pDevice;
	wrl::ComPtr<ID3D11DeviceContext> pContext;
	wrl::ComPtr<IDXGISwapChain> pSwap;
	wrl::ComPtr<ID3D11RenderTargetView> pTarget;
};