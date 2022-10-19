#include <fltKernel.h>

#define dprintf(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__)

DECLSPEC_NOINLINE
ULONG64
asm1()
{
#ifdef __clang__
    _asm {
        mov rax,1
    }
#else
    return 0;
#endif
}

DECLSPEC_NOINLINE
#ifdef __clang__
__declspec(naked)
#endif
    ULONG64 asm2()
{
#ifdef __clang__
    _asm {
        mov rax,2
        ret
    }
#else
    return 0;
#endif
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
