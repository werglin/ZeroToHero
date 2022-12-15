#pragma once

#include<exception>

// public keyword will make us take public things as public and protected things as protected
// we are still unable to reach private 
class MyException: public std::exception
{
private:

	//0 - 2147484646 i mean.. you cant be serious right 
	unsigned short int line;
	const char* fileName_c;

protected:
	// this needs to be checked
	mutable const char* whatBuffer;

public:

	MyException( int line, const char* fileName );
	// override makes same job as virtual but you cannot override twice
	// override simply breaks the base func
	const char* what() const noexcept override;
	// virtual keyword will make us call our custom "GetType" func 
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const char* GetFileName() const noexcept;
	const char* GetOriginString() const noexcept;

};

