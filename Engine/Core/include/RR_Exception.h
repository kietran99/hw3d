#pragma once

#include <string>

namespace RR
{
	class RRException : public std::exception
	{
	public:
		RRException(int line, const char* file) noexcept;
		virtual const char* what() const noexcept;
		virtual const char* GetType() const noexcept;
		int GetLine() const noexcept;
		const std::string& GetFile() const noexcept;
		std::string GetOriginString() const noexcept;
	private:
		int m_line;
		std::string m_file;
	protected:
		mutable std::string m_whatBuf;
	};
}
