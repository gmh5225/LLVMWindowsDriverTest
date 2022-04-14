#include <fltKernel.h>
#include "math-int_fastdiv/int_fastdiv.h"

#define dprintf(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__)

DECLSPEC_NOINLINE
void
Test_int_fastdiv(int_fastdiv d)
{
    /*
    .text:0000000140001000                 push    rbp
    .text:0000000140001001                 sub     rsp, 30h
    .text:0000000140001005                 lea     rbp, [rsp+30h]
    .text:000000014000100A                 and     rsp, 0FFFFFFFFFFFFFFF0h
    .text:000000014000100E                 mov     [rsp+30h+var_4], 64h ; 'd'
    .text:0000000140001016                 mov     eax, [rsp+30h+var_4]
    .text:000000014000101A                 movsxd  rdx, dword ptr [rcx+4]
    .text:000000014000101E                 cdqe
    .text:0000000140001020                 imul    rdx, rax
    .text:0000000140001024                 shr     rdx, 20h
    .text:0000000140001028                 imul    eax, [rcx+0Ch]
    .text:000000014000102C                 add     eax, edx
    .text:000000014000102E                 mov     ecx, [rcx+8]
    .text:0000000140001031                 mov     edx, eax
    .text:0000000140001033                 sar     edx, cl
    .text:0000000140001035                 mov     r9d, eax
    .text:0000000140001038                 shr     r9d, 1Fh
    .text:000000014000103C                 add     r9d, edx
    .text:000000014000103F                 test    ecx, ecx
    .text:0000000140001041                 cmovs   r9d, eax
    .text:0000000140001045                 lea     r8, Format      ; "Test_int_fastdiv:q=%d\n"
    .text:000000014000104C                 mov     ecx, 4Dh ; 'M'  ; ComponentId
    .text:0000000140001051                 xor     edx, edx        ; Level
    .text:0000000140001053                 call    cs:__imp_DbgPrintEx
    .text:0000000140001059                 nop
    .text:000000014000105A                 mov     rsp, rbp
    .text:000000014000105D                 pop     rbp
    .text:000000014000105E                 retn
    */
    volatile int a = 100;
    int q = a / d;
    dprintf("Test_int_fastdiv:q=%d\n", q);
}

DECLSPEC_NOINLINE
void
Test_int_div(int d)
{
    /*
    .text:000000014000105F                 push    rbp
    .text:0000000140001060                 sub     rsp, 30h
    .text:0000000140001064                 lea     rbp, [rsp+30h]
    .text:0000000140001069                 and     rsp, 0FFFFFFFFFFFFFFF0h
    .text:000000014000106D                 mov     [rsp+30h+var_4], 64h ; 'd'
    .text:0000000140001075                 mov     eax, [rsp+30h+var_4]
    .text:0000000140001079                 cdq
    .text:000000014000107A                 idiv    ecx
    .text:000000014000107C                 lea     r8, aTestIntDivQD ; "Test_int_div:q=%d\n"
    .text:0000000140001083                 mov     ecx, 4Dh ; 'M'  ; ComponentId
    .text:0000000140001088                 xor     edx, edx        ; Level
    .text:000000014000108A                 mov     r9d, eax
    .text:000000014000108D                 call    cs:__imp_DbgPrintEx
    .text:0000000140001093                 nop
    .text:0000000140001094                 mov     rsp, rbp
    .text:0000000140001097                 pop     rbp
    .text:0000000140001098                 retn
    */
    volatile int a = 100;
    int q = a / d;
    dprintf("Test_int_div:q=%d\n", q);
}

EXTERN_C
void
TestDiv()
{
    dprintf("TestDiv begin\n");
    Test_int_fastdiv(10);
    Test_int_div(10);
    dprintf("TestDiv end\n");
}
