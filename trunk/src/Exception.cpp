#include "Exception.h"

ISD::Db::Exception::Exception(const wchar_t* msg) : m_msg(msg)
{
}

ISD::Db::Exception::~Exception()
{
}

const std::wstring&
ISD::Db::Exception::what() const
{
   return m_msg;
}
