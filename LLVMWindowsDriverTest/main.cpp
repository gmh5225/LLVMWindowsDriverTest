#include <fltKernel.h>
#include <intrin.h>

#define dprintf(...)                                                           \
  DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__)

EXTERN_C
NTSTATUS
DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
  dprintf("new wolrd!\n");

  // test readcr3
  {
    auto cr3 = __readcr3();
    dprintf("readcr3 cr3=%p\n", cr3);
  }

  // test writecr3
  {
    auto cr3 = __readcr3();
    __writecr3(cr3);
    cr3 = __readcr3();
    dprintf("writecr3 cr3=%p\n", cr3);
  }

  return STATUS_VIRUS_INFECTED;
}
