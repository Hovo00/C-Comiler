#include "Exception.h"

CException::CException(std::string const sErrorMsg)
{
	m_sErrorMsg = sErrorMsg;
}

CException::~CException()
{
}

const char* CException::what() const noexcept
{
	return m_sErrorMsg.c_str();
}
