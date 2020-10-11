//-----------------------------------------------------------------------------
//                      YoloDarknet 框架
//                                          @2018-11-15 AGAN
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "test.h"
#include "yolo_console_dll.h"
#include "yolo_mark.h"
#include <vector>

extern int yolo_fast(int argc, char** argv);

//控制台
int main(int argc, char** argv)
{
    DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
    DrawMenuBar(GetConsoleWindow());
    //system("color e0");
    //system("color 5f");
    //system("color e5");
    system("color ce");
    if (argc < 2)
    {
        //yolo_fast(argc, argv);
        //std::vector<box> objs;
        //yolo_detect((unsigned char*)"data/dog.jpg", 0, "data/coco.data", "data/yolov3-tiny.cfg", "data/yolov3-tiny.mo", objs);
        return 0;
    }
    //下面加入两个工具
#ifdef OPENCV
    if (0 == strcmp(argv[1], "cutpic"))
        cutpicforvideo(argc, argv);
    else if (0 == strcmp(argv[1], "yolo_mark"))
        yolo_mark(argc, argv);
    else if (0 == strcmp(argv[1], "yolo_resize"))
        yolo_resize(argc, argv);
    else if (0 == strcmp(argv[1], "yolo_fast"))
        yolo_fast(argc, argv);
#endif
    return yolov3main(argc, argv);
}

//窗口界面
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow)
{
    yolov3main(nCmdShow, &lpCmdLine);
    return 0;
}

//dll
bool APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_PROCESS_DETACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    }
    return true;
}






