#include <fltKernel.h>

#define dprintf(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__)

EXTERN_C
void
TestintrinBySelfintrin();

EXTERN_C
void
TestintrinByUseintrin();

EXTERN_C
void
TestVaList(const char *szFunction, const char *szSourcePath, int nLine, const char *szFormat, ...);

EXTERN_C
NTSTATUS
TestFPU();

EXTERN_C
void
TestDiv();

EXTERN_C
NTSTATUS
DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    dprintf("new world!\n");

    TestintrinByUseintrin();
    TestintrinBySelfintrin();
    TestVaList("aha", "aha", 123, "%d", 3);
    TestFPU();
    TestDiv();
    dprintf("end world!\n");

    return STATUS_VIRUS_INFECTED;
}
