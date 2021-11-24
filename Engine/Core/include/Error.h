#pragma once

#include "RR_Win.h"

#include <stdlib.h>

#include "Window.h"

#define CHECK_WND(expr) \
	if (!expr) \
	{ \
		const auto err = RR::Window::Exception(__LINE__, __FILE__, GetLastError()); \
		MessageBox(nullptr, err.what(), err.GetType(), MB_OK | MB_ICONEXCLAMATION); \
		exit(0); \
	}

#define CHECK_WND_HR(hRes) \
	if (FAILED(hRes)) \
	{ \
		const auto err = RR::Window::Exception(__LINE__, __FILE__, hRes); \
		MessageBox(nullptr, err.what(), err.GetType(), MB_OK | MB_ICONEXCLAMATION); \
		exit(0); \
	}