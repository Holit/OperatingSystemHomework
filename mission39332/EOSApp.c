#include "EOSApp.h"

int main(int argc, char* argv[])
{
	//
	// 启动调试 EOS 应用程序前要特别注意下面的问题：
	//
	// 1、如果要在调试应用程序时能够调试进入内核并显示对应的源码，
	//    必须使用 EOS 核心项目编译生成完全版本的 SDK 文件夹，然
	//    后使用此文件夹覆盖应用程序项目中的 SDK 文件夹，并且 EOS
	//    核心项目在磁盘上的位置不能改变。
	//
	
	STARTUPINFO StartupInfo;
    int i = 0;          //循环计数器
#define PROCESS_NUMBER 10
    PROCESS_INFORMATION piChildProc[PROCESS_NUMBER];
    BOOL bCreateRes[PROCESS_NUMBER];
	ULONG ulExitCode;	// 子进程退出码
	INT nResult = 0;	// main 函数返回值。0 表示成功，非 0 表示失败。

	printf("Create ten processes and wait for the processes exit...\n\n");

	StartupInfo.StdInput = GetStdHandle(STD_INPUT_HANDLE);
	StartupInfo.StdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	StartupInfo.StdError = GetStdHandle(STD_ERROR_HANDLE);
    //同时启动进程
    for(i = 0; i < PROCESS_NUMBER ; i ++)
    {
        bCreateRes[i] = CreateProcess("A:\\Hello.exe", NULL, 0, &StartupInfo, &piChildProc[i]);
    }
    //轮询等待进程结束
    for(i = 0; i < PROCESS_NUMBER ; i ++)
    {
        WaitForSingleObject(piChildProc[i].ProcessHandle, INFINITE);
    }
    //轮询退出码
    for(i = 0; i < PROCESS_NUMBER ; i ++)
    {
    	GetExitCodeProcess(piChildProc[i].ProcessHandle, &ulExitCode);
    	printf("\nThe process %d exit with %d.\n",i, ulExitCode);
    }
    //关闭所有句柄
    for(i = 0; i < PROCESS_NUMBER; i ++)
    {
    	CloseHandle(piChildProc[i].ProcessHandle);
    	CloseHandle(piChildProc[i].ThreadHandle);
    }
    printf("\nAll done.GetLastError()=%d\n",GetLastError());
    

	return nResult;
}
