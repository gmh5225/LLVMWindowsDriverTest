#include <fltKernel.h>

#define dprintf(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__)

DECLSPEC_NOINLINE
ULONG64
asm1()
{
    _asm {
        mov rax,1
        ret
    }
}

DECLSPEC_NOINLINE
__declspec(naked) ULONG64 asm2()
{
    _asm {
        mov rax,2
        ret
    }
}

EXTERN_C
void
TestInlineAsm()
{
    dprintf("TestInlineAsm begin\n");
    auto asm1ret1 = asm1();
    auto asm2ret2 = asm2();
    dprintf("asm1ret1=%p\n", asm1ret1);
    dprintf("asm2ret2=%p\n", asm2ret2);
    dprintf("TestInlineAsm end\n");
}
