#include <fltKernel.h>
#include <intrin.h>

#define dprintf(...)                                                           \
  DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__)

EXTERN_C
void __writecr2(ULONG_PTR);

EXTERN_C
NTSTATUS
DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
  dprintf("new wolrd!\n");

  // test cr2
  {
    auto cr3 = __readcr3();
    dprintf("readcr3 cr3=%p\n", cr3);
    __writecr3(cr3);
    cr3 = __readcr3();
    dprintf("writecr3 cr3=%p\n", cr3);
  }

  // test cr2
  {
    auto cr2 = __readcr2();
    dprintf("readcr2 cr2=%p\n", cr2);
    __writecr2(cr2);
    cr2 = __readcr2();
    dprintf("writecr2 cr2=%p\n", cr2);
  }

  return STATUS_VIRUS_INFECTED;
}
