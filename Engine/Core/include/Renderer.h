#pragma once

#include "RR_Win.h"

#include <d3d11.h>

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
		~Renderer();

		void Update();
	private:
		IDXGISwapChain* m_pSwapChain;
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pContext;
	};
}