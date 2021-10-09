#pragma once

#include "ChiliWin.h"

class Window
{
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
	Window(int width, int height, const char* name) noexcept;
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