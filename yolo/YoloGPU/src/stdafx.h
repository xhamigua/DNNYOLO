
#ifndef STDAFX_H
#define STDAFX_H

//编译开关----------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS                     //警告宏
#define CONSOLE                                     //入口选项 GUIRUNC/NATIVEC/CONSOLE/HIDECMD

#include "CDefine.hpp"
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "resyolo.h"

//输出宏定义
#ifndef SQC_API
#define SQC_API extern "C" __declspec(dllexport)
#endif
#ifndef SQCPP_API
#define SQCPP_API __declspec(dllexport)
#endif
#ifndef DLL_API
    #define DLL_API SQCPP_API
#endif





#endif