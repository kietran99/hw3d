#include "RR_Exception.h"

#include <sstream>

namespace RR
{
	RRException::RRException(int line, const char* file) noexcept
		: m_line(line), m_file(file) {}

	const char* RRException::what() const noexcept
	{
		std::ostringstream oss;
		oss << GetType() << std::endl << GetOriginString();
		m_whatBuf = oss.str();
		return m_whatBuf.c_str();
	}

	const char* RRException::GetType() const noexcept
	{
		return "RR Error";
	}

	int RRException::GetLine() const noexcept
	{
		return m_line;
	}

	const std::string& RRException::GetFile() const noexcept
	{
		return m_file;
	}

	std::string RRException::GetOriginString() const noexcept
	{
		std::ostringstream oss;
		oss << "[File] " << GetFile() << std::endl
			<< "[Line] " << GetLine();
		return oss.str();
	}
}