#include <fltKernel.h>
#include <stdarg.h>

#define dprintf(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__)

EXTERN_C
void
TestVaList(const char *szFunction, const char *szSourcePath, int nLine, const char *szFormat, ...)
{
    // This code only be used for testing. it's useless.
    char msg[1024] = "";
    int size = 0;
    int remain = sizeof(msg) / sizeof(char);

    memcpy(msg, szSourcePath, nLine);

    char *pLogSpace = msg + size;
    va_list v1;
    va_start(v1, szFormat);
    va_end(v1);
    dprintf(msg);
}
