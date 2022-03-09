#include <fltKernel.h>

#define dprintf(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__)

EXTERN_C
void
TestintrinBySelfintrin();

EXTERN_C
void
TestintrinByUseintrin();

EXTERN_C
NTSTATUS
DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    dprintf("new wolrd!\n");

    TestintrinByUseintrin();
    TestintrinBySelfintrin();

    dprintf("end wolrd!\n");

    return STATUS_VIRUS_INFECTED;
}
