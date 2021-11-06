#pragma once

namespace RR
{
	class Debug
	{
		friend class Window;

	public:
		static void Log(const char* fmt, ...);

	private:
		Debug();

	private:
		static Debug* s_instance;
	};
}