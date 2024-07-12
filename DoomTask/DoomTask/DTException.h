#pragma once

#include <exception>
#include <string>
#include <sstream>

/// <summary>
/// The standard exception of this application 
/// </summary>
class DTException : public std::exception
{
public:
	DTException(int line, const char* file) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;
private: 
	int line;
	std::string file;

protected:
	mutable std::string whatBuffer;
};