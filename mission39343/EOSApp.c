#include "EOSApp.h"

int main(int argc, char *argv[])
{
    // 调用 API 函数 VirtualAlloc，分配一个整型变量所需的空间，并使用一个整型变量的指针指向这个空间。
    PVOID pAddress = NULL;
    SIZE_T sizeBuffer = sizeof(int);

    int *piBuffer = VirtualAlloc(pAddress, sizeBuffer, MEM_RESERVE | MEM_COMMIT);
    if(!piBuffer)
    {
        printf("Unexpected error occured!\nat VirtualAlloc: %d\n",GetLastError());
        return ERROR_INVALID_PARAMETER;
    }
    printf("Allocate %d bytes virtual memory at 0x%X\n\n", sizeof(int), piBuffer);

    //修改整型变量的值为 0xFFFFFFFF。在修改前输出整型变量的值，在修改后再输出整型变量的值。
    printf("Virtual memory original value: 0x%X\n", *piBuffer);
    *piBuffer = 0xFFFFFFFF;
    printf("Virtual memory new value: 0x%X\n", *piBuffer);

    // 调用 API 函数 Sleep，等待 10 秒钟。
    printf("\nWait for 10 second\n");
    Sleep(10 * 1000);

    // 调用 API 函数 VirtualFree，释放之前分配的整型变量的空间。
    STATUS Status = VirtualFree(piBuffer, 0, MEM_RELEASE);
    if(!EOS_SUCCESS(Status))
    {
        printf("Unexpected error occured!\nat VirtualFree: %d\n",GetLastError());
        return ERROR_INVALID_PARAMETER;
    }

    printf("\nRelease virtual memory success!\n");

    // 进入死循环，这样应用程序就不会结束。
    printf("\nEndless loop!\n");
    while (TRUE)
    {
        for(;;)
        {
            __asm("nop");
        }
    }

    return NO_ERROR;
}
