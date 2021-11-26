#include "Renderer.h"

#include "Window.h"
#include "Error.h"

namespace wrl = Microsoft::WRL;

RR::Renderer::Renderer(HWND hWnd)
	: m_pSwapChain(nullptr)
	, m_pDevice(nullptr)
	, m_pContext(nullptr)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

	UINT swapCreateFlags = 0u;

#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // !NDEBUG

	const auto createDevAndSwapChainRes = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_pSwapChain,
		&m_pDevice,
		nullptr,
		&m_pContext
	);

	CHECK_WND_HR(createDevAndSwapChainRes);

	wrl::ComPtr<ID3D11Resource> pBackBuf;
	const auto getBufRes = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuf);

	CHECK_WND_HR(getBufRes);
	
	const auto createTargetViewRes = m_pDevice->CreateRenderTargetView(pBackBuf.Get(), nullptr, &m_pTarget);

	CHECK_WND_HR(createTargetViewRes);
}

void RR::Renderer::Update()
{
	const auto hRes = m_pSwapChain->Present(1u, 0u);

	CHECK_WND_HR(hRes);
}

void RR::Renderer::ClearColor(float r, float g, float b)
{
	const FLOAT color[] = { r, g, b, 1.0f };
	m_pContext->ClearRenderTargetView(m_pTarget.Get(), color);
}
