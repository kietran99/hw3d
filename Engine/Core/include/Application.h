#pragma once

#include "RR_Win.h"

namespace RR
{
	class Window;

	class Application
	{
	public:
		Application(int width, int height, const char* name);
		~Application();

		WPARAM Start();

	private:
		void Update();

	private:
		Window* m_pWindow;
	};
}