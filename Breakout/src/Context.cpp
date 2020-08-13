#include "Context.h"

bool Context::Init(HWND hWnd)
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT flags = 0;
#ifdef DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    if (D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        flags,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &pSwap,
        &pDevice,
        nullptr,
        &pContext
    ) != S_OK)
        return false;

    wrl::ComPtr<ID3D11Texture2D> pBackBuffer;
    pSwap->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    pDevice->CreateRenderTargetView(pBackBuffer.Get(), NULL, &pTarget);
    return true;
}

wrl::ComPtr<ID3D11Device> GetDevice(Context c)
{
	return c.pDevice;
}

wrl::ComPtr<ID3D11DeviceContext> GetContext(Context c)
{
	return c.pContext;
}

wrl::ComPtr<IDXGISwapChain> GetSwapChain(Context c)
{
	return c.pSwap;
}

wrl::ComPtr<ID3D11RenderTargetView> GetTarget(Context c)
{
	return c.pTarget;
}
