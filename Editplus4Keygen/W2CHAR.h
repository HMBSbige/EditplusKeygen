#pragma once
#include <iostream>  
#include <windows.h>  
#include <string>  
using namespace std;  
class W2CHAR  
{  
public:  
    W2CHAR();  
    virtual~ W2CHAR();  
    char* WcharToChar(const wchar_t* wp);  
    char* StringToChar(const string& s);  
    char* WstringToChar(const wstring& ws);  
    wchar_t* CharToWchar(const char* c);  
    wchar_t* WstringToWchar(const wstring& ws);  
    wchar_t* StringToWchar(const string& s);  
    wstring StringToWstring(const string& s);  
    string WstringToString(const wstring& ws);  
    void Release();  
private:  
    char* m_char;  
    wchar_t* m_wchar;  
}; 