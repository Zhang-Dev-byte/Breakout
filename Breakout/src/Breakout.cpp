#include <Windows.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Keyboard.h"
#include "Message.h"
#include "Context.h"


HRESULT hr;
WCHAR desc[512];

struct Vertex
{
	float x;
	float y;
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

#define LOG(x) std::cout << x << std::endl;
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
	case WM_KEYDOWN:
		Keyboard::OnKeyPressed((int)wParam);
		break;
	case WM_SYSKEYDOWN:
		Keyboard::OnKeyPressed((int)wParam);
		break;
	case WM_KEYUP:
		Keyboard::OnKeyReleased((int)wParam);
		break;
	case WM_SYSKEYUP:
		Keyboard::OnKeyReleased((int)wParam);
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
int main() {
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"Breakout", NULL };
	RegisterClassEx(&wc);
	HWND hWnd = CreateWindow(wc.lpszClassName, L"Breakout", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 720, NULL, NULL, wc.hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	Context c;
	if (!c.Init(hWnd)) {
		LOG("ERROR: Failed to init directx");
	}

	Vertex vertices[] =
	{
		{ 0.0f,0.5f,255,0,0,0 },
		{ 0.5f,-0.5f,0,255,0,0 },
		{ -0.5f,-0.5f,0,0,255,0 },
	};

	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(vertices);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = vertices;
	GFX_THROW_INFO(GetDevice(c)->CreateBuffer(&bd, &sd, &pVertexBuffer));

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	GetContext(c)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	GFX_THROW_INFO(D3DReadFileToBlob(L"PixelShader_ps.cso", &pBlob));
	GFX_THROW_INFO(GetDevice(c)->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader));

	GetContext(c)->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	GFX_THROW_INFO(D3DReadFileToBlob(L"VertexShader_vs.cso", &pBlob));
	GFX_THROW_INFO(GetDevice(c)->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader));

	GetContext(c)->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position",0,DXGI_FORMAT_R32G32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "Color",0,DXGI_FORMAT_R8G8B8A8_UNORM,0,8u,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	GFX_THROW_INFO(GetDevice(c)->CreateInputLayout(
		ied, (UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	));

	GetContext(c)->IASetInputLayout(pInputLayout.Get());

	GetContext(c)->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Message msg;
	while (!msg.ShouldClose()) {
		if (msg.Peek())
		{
			msg.Dispatch();
			continue;
		}
		float color[] = { 0.0f,0.5f,0.5f,1.0f };
		GetContext(c)->ClearRenderTargetView(GetTarget(c).Get(), color);
		GetContext(c)->Draw((UINT)std::size(vertices), 0u);
		GFX_THROW_INFO(GetSwapChain(c)->Present(0, 0));
	}
}