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

  // test cr0
  {
    auto cr0 = __readcr0();
    dprintf("readcr0 cr0=%p\n", cr0);
    __writecr0(cr0);
    cr0 = __readcr0();
    dprintf("writecr0 cr0=%p\n", cr0);
  }

  // test cr2
  {
    auto cr2 = __readcr2();
    dprintf("readcr2 cr2=%p\n", cr2);
    __writecr2(cr2);
    cr2 = __readcr2();
    dprintf("writecr2 cr2=%p\n", cr2);
  }

  // test cr3
  {
    auto cr3 = __readcr3();
    dprintf("readcr3 cr3=%p\n", cr3);
    __writecr3(cr3);
    cr3 = __readcr3();
    dprintf("writecr3 cr3=%p\n", cr3);
  }

  // test dr
  {
    auto dr0 = __readdr(0);
    dprintf("read dr0=%p\n", dr0);
    __writedr(0, dr0);
    dr0 = __readdr(0);
    dprintf("write dr0=%p\n", dr0);

    auto dr7 = __readdr(7);
    dprintf("read dr7=%p\n", dr7);
    __writedr(0, dr7);
    dr7 = __readdr(7);
    dprintf("write dr7=%p\n", dr7);
  }

  // test msr
  {
    auto msr_C0000082 = __readmsr(0xC0000082);
    dprintf("read msr 0xC0000082 =%p\n", msr_C0000082);

    __writemsr(0xC0000082, 0);
    auto msr_C0000082_temp = __readmsr(0xC0000082);
    dprintf("write msr 0xC0000082 =%p\n", msr_C0000082_temp);

    __writemsr(0xC0000082, msr_C0000082);
    msr_C0000082 = __readmsr(0xC0000082);
    dprintf("write msr 0xC0000082 =%p\n", msr_C0000082);
  }

  // test cpuidex
  {
    int a[4] = {0};
    __cpuidex(a, 1, 0);
    auto ecx = a[2];
    if (ecx & 0x80000000) {
      dprintf("You are in virtual machine!\n");
    }
  }

  return STATUS_VIRUS_INFECTED;
}
