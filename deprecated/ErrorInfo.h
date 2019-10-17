#pragma once

#include<fstream>
#include<string>

class ErrorInfo  
{
private:
     //保存log日志
     std::ofstream m_fileLog;
  static ErrorInfo *s_pInstance;
    ErrorInfo();
public:
     ~ErrorInfo();
  static ErrorInfo *Instance();
  void log(std::string str);
  void log(float num);
};
ErrorInfo*ErrorInfo::s_pInstance = NULL;

ErrorInfo::ErrorInfo()
{
	m_fileLog.open("log",std::ios::out);
}
ErrorInfo::~ErrorInfo()
{
}
ErrorInfo*ErrorInfo::Instance()
{
	if (s_pInstance == NULL)
	    s_pInstance = new ErrorInfo();
	return s_pInstance;
}
void ErrorInfo::log(std::string str)
{
	m_fileLog.open("log",std::ios::app);
	m_fileLog<<str<<std::endl;
	m_fileLog.close();
}
void ErrorInfo::log(float num)
{
	m_fileLog.open("log",std::ios::app);
	m_fileLog<<num<<std::endl;
	m_fileLog.close();
}