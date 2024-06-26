#include "DTException.h"

DTException::DTException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* DTException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	whatBuffer = oss.str();

	return whatBuffer.c_str();
}

const char* DTException::GetType() const noexcept
{
	return "DT Exception";
}

int DTException::GetLine() const noexcept
{
	return line;
}

const std::string& DTException::GetFile() const noexcept
{
	return file;
}

std::string DTException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}



