#include "MyException.h"
#include <sstream>

MyException::MyException(int line, const char* fileName)
	:line(line), fileName_c(fileName)
{
}

const char* MyException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	this->whatBuffer = oss.str().c_str();
	return this->whatBuffer;
}

const char* MyException::GetType() const noexcept
{
	return "MyException";
}

int MyException::GetLine() const noexcept
{
	return this->line;
}

const char* MyException::GetFileName() const noexcept
{
	return this->fileName_c;
}

const char* MyException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << this->fileName_c << std::endl
		<< "[Line] " << this->line;
	return oss.str().c_str();
}

