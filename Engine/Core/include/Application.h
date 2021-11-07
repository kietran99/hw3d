#pragma once

#include "RR_Win.h"

namespace RR
{
	class Window;

	class Application
	{
	public:
		Application();
		~Application();
		int Start();

	private:
		void Update();

	private:
		Window* m_window;
	};
}