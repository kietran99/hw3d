#include "Renderer.h"

#include <d3dcompiler.h>

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
	DrawTestTriangle();
	const auto hRes = m_pSwapChain->Present(1u, 0u);

	CHECK_WND_HR(hRes);
}

void RR::Renderer::ClearColor(float r, float g, float b)
{
	const FLOAT color[] = { r, g, b, 1.0f };
	m_pContext->ClearRenderTargetView(m_pTarget.Get(), color);
}

void RR::Renderer::DrawTestTriangle()
{
	struct Vertex
	{
		float x, y;
	};

	Vertex vertices[] =
	{
		{ 0.0f, 0.5f },
		{ 0.5f, -0.5f },
		{ -0.5f, -0.5f }
	};

	D3D11_SUBRESOURCE_DATA subResData{};
	subResData.pSysMem = &vertices;

	D3D11_BUFFER_DESC bufDesc{};
	bufDesc.ByteWidth = sizeof(vertices);
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufDesc.CPUAccessFlags = 0;
	bufDesc.MiscFlags = 0;
	bufDesc.StructureByteStride = sizeof(Vertex);
	
	wrl::ComPtr<ID3D11Buffer> pBuf;
	const HRESULT createBufRes = m_pDevice->CreateBuffer(&bufDesc, &subResData, &pBuf);

	CHECK_WND_HR(createBufRes);

	const UINT strides = sizeof(Vertex), offsets = 0u;
	m_pContext->IASetVertexBuffers(0u, 1u, pBuf.GetAddressOf(), &strides, &offsets);

	wrl::ComPtr<ID3DBlob> pBlob;

	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	const HRESULT readPixelShaderRes = D3DReadFileToBlob(L"PixelShader.cso", &pBlob);

	CHECK_WND_HR(readPixelShaderRes);

	const HRESULT createPixelShaderRes = m_pDevice->CreatePixelShader(
		pBlob->GetBufferPointer()
		, pBlob->GetBufferSize()
		, nullptr
		, &pPixelShader);

	CHECK_WND_HR(createPixelShaderRes);

	m_pContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	D3D11_VIEWPORT viewPort{};
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = 800;
	viewPort.Height = 600;
	viewPort.MinDepth = 0;
	viewPort.MaxDepth = 1;

	m_pContext->RSSetViewports(1u, &viewPort);

	m_pContext->OMSetRenderTargets(1u, m_pTarget.GetAddressOf(), nullptr);

	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	const HRESULT readVertexShaderRes = D3DReadFileToBlob(L"VertexShader.cso", &pBlob);

	CHECK_WND_HR(readVertexShaderRes);

	const HRESULT createVertexShaderRes = m_pDevice->CreateVertexShader(
		pBlob->GetBufferPointer()
		, pBlob->GetBufferSize()
		, nullptr
		, &pVertexShader);

	CHECK_WND_HR(createVertexShaderRes);

	m_pContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	wrl::ComPtr<ID3D11InputLayout> pVertexLayout;
	D3D11_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "Position", 0u, DXGI_FORMAT_R32G32_FLOAT, 0u, 0u, D3D11_INPUT_PER_VERTEX_DATA, 0u }
	};

	const HRESULT createInputLayoutRes = m_pDevice->CreateInputLayout(
		inputElementDescs
		, (UINT) std::size(inputElementDescs)
		, pBlob->GetBufferPointer()
		, pBlob->GetBufferSize()
		, &pVertexLayout);

	CHECK_WND_HR(createInputLayoutRes);

	m_pContext->IASetInputLayout(pVertexLayout.Get());

	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pContext->Draw((UINT)std::size(vertices), 0u);
}
