#pragma once

#include "RR_Win.h"
#include "RR_Exception.h"

namespace RR
{
	class Window
	{
	public:
		class Exception : public RRException
		{
		public:
			Exception(int line, const char* file, HRESULT hRes) noexcept;
			virtual const char* what() const noexcept override;
			virtual const char* GetType() const noexcept override;
			static std::string TranslateErrorCode(HRESULT hRes) noexcept;
			std::string GetErrorString() const noexcept;
		private:
			HRESULT m_hRes;
		};
	private:
		class WindowClass
		{
		public:
			static const char* GetName() noexcept;
			static const HINSTANCE GetInstance() noexcept;
		private:
			WindowClass() noexcept;
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;

			static constexpr const char* WND_CLS_NAME = "Chili Direct3D Engine Window";
			static WindowClass m_instance;
			HINSTANCE m_hInst;
		};

	public:
		Window(int width, int height, const char* name);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
		static LRESULT WINAPI HandleMessageSetup(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI HandleMessageThunk(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	private:
		int m_width, m_height;
		HWND m_hWnd;
	};

#define RR_WND_EXCEPT(hRes) RR::Window::Exception(__LINE__, __FILE__, hRes)
#define RR_WND_LAST_EXCEPT() RR::Window::Exception(__LINE__, __FILE__, GetLastError())
}