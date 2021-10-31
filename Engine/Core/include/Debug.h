#pragma once

namespace RR
{
	class Debug
	{
		friend class Window;

	public:
		static void Log(const char* msg);

	private:
		Debug();

	private:
		static Debug* s_instance;
	};
}