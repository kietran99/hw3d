#pragma once

#include "RR_Win.h"

#include <d3d11.h>
#include <wrl.h>

namespace RR
{
	class Renderer
	{
	public:
		Renderer(HWND hWnd);
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(Renderer&&) = delete;
		~Renderer() = default;

		void Update();

		void ClearColor(float r, float g, float b);
		void DrawTestTriangle();
	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> m_pSwapChain;
		Microsoft::WRL::ComPtr<ID3D11Device> m_pDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pContext;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pTarget;
	};
}