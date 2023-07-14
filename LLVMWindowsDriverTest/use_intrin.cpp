#include <fltKernel.h>
#include <intrin.h>

#define dprintf(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__)

EXTERN_C
void __writecr2(ULONG_PTR);

EXTERN_C
void
_sgdt(void *Destination);

EXTERN_C
unsigned char
_xtest(void);

EXTERN_C
void
TestintrinByUseintrin()
{
    dprintf("----TestintrinByUseintrin begin----\n");
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

    // test cr4
    {
        auto cr4 = __readcr4();
        dprintf("readcr4 cr4=%p\n", cr4);
        __writecr4(cr4);
        cr4 = __readcr4();
        dprintf("writecr4 cr4=%p\n", cr4);
    }

    // test cr8
#ifdef _WIN64
    {
        auto cr8 = __readcr8();
        dprintf("readcr8 cr8=%p\n", cr8);
        __writecr8(cr8);
        cr8 = __readcr8();
        dprintf("writecr8 cr8=%p\n", cr8);
    }
#endif

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

    // test cpuid
    {
        int a[4] = {0};
        __cpuid(a, 1);
        auto ecx = a[2];
        if (ecx & 0x80000000)
        {
            dprintf("cpuid: You are in virtual machine!\n");
        }

        memset(a, 0, sizeof(a));
        // CPUID_ADDR_WIDTH 0x80000008
        __cpuid(a, 0x80000008);
        unsigned int AddrWidth = ((a[0] >> 8) & 0x0ff);
        dprintf("cpuid: AddrWidth=%d\n", AddrWidth);
    }

    // test cpuidex
    {
        int a[4] = {0};
        __cpuidex(a, 1, 0);
        auto ecx = a[2];
        if (ecx & 0x80000000)
        {
            dprintf("cpuidex: You are in virtual machine!\n");
        }

        memset(a, 0, sizeof(a));
        // CPUID_ADDR_WIDTH 0x80000008
        __cpuidex(a, 0x80000008, 0);
        unsigned int AddrWidth = ((a[0] >> 8) & 0x0ff);
        dprintf("cpuidex: AddrWidth=%d\n", AddrWidth);
    }

    // test xbeign/xend
    {
        dprintf("test xbeign/xend\n");
        __try
        {
            _xbegin();
            _xend();
        }
        __except (1)
        {
            dprintf("test xbeign/xend goto except handler\n");
        }
    }

    // test stosb
    {
        unsigned char c = 0x40; /* '@' character */
        unsigned char s[] = "*********************************";

        dprintf("%s\n", s);
        __stosb((unsigned char *)s + 1, c, 6);
        dprintf("%s\n", s);
        //*********************************
        //*@@@@@@**************************
    }

    // test stosw
    {
        unsigned short val = 128;
        unsigned short a[100];
        memset(a, 0, sizeof(a));
        __stosw(a + 10, val, 2);
        dprintf("%u %u %u %u\n", a[9], a[10], a[11], a[12]);
        // 0 128 128 0
    }

    // test stosd
    {
        unsigned long val = 99999;
        unsigned long a[10];

        memset(a, 0, sizeof(a));
        __stosd(a + 1, val, 2);

        dprintf("%u %u %u %u\n", a[0], a[1], a[2], a[3]);
        // 0 99999 99999 0
    }

#ifdef _WIN64
    // test stosq
    {
        unsigned __int64 val = 0xFFFFFFFFFFFFI64;
        unsigned __int64 a[10];
        memset(a, 0, sizeof(a));
        __stosq(a + 1, val, 2);
        dprintf("%I64x %I64x %I64x %I64x\n", a[0], a[1], a[2], a[3]);
        // 0 ffffffffffff ffffffffffff 0
    }
#endif

    // test readpmc
    {
        auto pmc0 = __readpmc(0);
        dprintf("pmc0:%I64x\n", pmc0);
    }

    // test readtscp
    {
        unsigned int aux;
        auto tickcount = __rdtscp(&aux);
        dprintf("aux:0x%x\n", aux);
        dprintf("tickcount:%I64x\n", tickcount);
    }

    // test inbyte
    {
        ///* VMware I/O Port  */
        __try
        {
            auto PortRead = __inbyte(5658);
            dprintf("inbyte:%x\n", PortRead);
        }
        __except (1)
        {
            dprintf("inbyte in except hanlder\n");
        }
    }

    // test inword
    {
        ///* VMware I/O Port  */
        __try
        {
            auto PortRead = __inword(5658);
            dprintf("inword:%x\n", PortRead);
        }
        __except (1)
        {
            dprintf("inword in except hanlder\n");
        }
    }

    // test indword
    {
        ///* VMware I/O Port  */
        __try
        {
            auto PortRead = __indword(5658);
            dprintf("indword:%x\n", PortRead);
        }
        __except (1)
        {
            dprintf("indword in except hanlder\n");
        }
    }

    // test invlpg
    {
        auto mem = ExAllocatePool(NonPagedPool, 0x1000);
        if (mem)
        {
            __invlpg(mem);
            dprintf("__invlpg addr=%p\n", mem);
            ExFreePool(mem);
        }
    }

    // test invpcid
    {
        ULONG_PTR pcid = 0;
        _invpcid(2, &pcid);
        dprintf("_invpcid pcid=%p\n", pcid);
    }

    // test inbytestring
    {
        ///* VMware I/O Port  */
        char buf[100] = {0};
        __inbytestring(5658, (PUCHAR)buf, sizeof(buf));
        dprintf("buf=%s\n", buf);
    }

    // test cti/sti
    {
        dprintf("test cti/sti begin\n");
        _disable();
        _enable();
        dprintf("test cti/sti end\n");
    }

    // test lsl
    {
        dprintf("test lsl begin\n");

#define EFLAGS_ZF 0x00000040
#define KGDT_R3_DATA 0x0020
#define RPL_MASK 0x3

#ifdef _M_IX86
        typedef unsigned int READETYPE;
#else
        typedef unsigned __int64 READETYPE;
#endif

        const unsigned long initsl = 0xbaadbabe;
        READETYPE eflags = 0;
        unsigned long sl = initsl;

        dprintf("Before: segment limit =0x%x eflags =0x%x\n", sl, eflags);
        sl = __segmentlimit(KGDT_R3_DATA + RPL_MASK);

        eflags = __readeflags();

        dprintf(
            "After: segment limit =0x%x eflags =0x%x eflags.zf = %s\n",
            sl,
            eflags,
            (eflags & EFLAGS_ZF) ? "set" : "clear");

        // If ZF is set, the call to lsl succeeded; if ZF is clear, the call failed.
        dprintf("%s\n", eflags & EFLAGS_ZF ? "Success!" : "Fail!");

        // You can verify the value of sl to make sure that the instruction wrote to it
        dprintf("sl was %s\n", (sl == initsl) ? "unchanged" : "changed");

        dprintf("test lsl end\n");

        /*
        Before: segment limit =0xbaadbabe eflags =0x0
        After: segment limit =0xffffffff eflags =0x256 eflags.zf = set
        Success!
        sl was changed
        */
    }

    // test wbinvd
    {
        dprintf("test wbinvd begin\n");
        __wbinvd();
        dprintf("test wbinvd end\n");
    }

    struct Idtr
    {
        unsigned short limit;
        ULONG_PTR base;
    };
    // test sidt/lidt
    {
        Idtr IDT{};
        __sidt(&IDT);
        __lidt(&IDT);
        dprintf("test sidt/lidt end\n");
    }

    // test gdtr
    {
        using Gdtr = Idtr;
        Gdtr gdtr = {};
        _sgdt(&gdtr);
        dprintf("test _sgdt end\n");
    }

    /*  __rdtsc();
      __rdtscp(NULL);
      __segmentlimit(123);
      __invlpg((void *)0xaabbccddaabbccdd);
      __sidt((void *)0xaabbccddaabbccdd);
      __lidt((void *)0xaabbccddaabbccdd);
      _sgdt((void *)0xaabbccddaabbccdd);
      _xbegin();
      _xend();
      _xabort(0);
      _xtest();
      _invpcid(1, NULL);*/

    dprintf("----TestintrinByUseintrin end----\n");
}
