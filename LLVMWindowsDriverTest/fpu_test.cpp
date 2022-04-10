#include <fltKernel.h>

// https://docs.microsoft.com/en-us/windows-hardware/drivers/kernel/using-floating-point-or-mmx-in-a-wdm-driver

#define dprintf(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, __VA_ARGS__)

__declspec(noinline) VOID DoFloatingPointCalculation(VOID)
{
    double Duration;
    LARGE_INTEGER Frequency;

    Duration = 1000000.0;
    dprintf("%I64x\n", *(LONGLONG *)&Duration);
    KeQueryPerformanceCounter(&Frequency);
    Duration /= (double)Frequency.QuadPart;
    dprintf("%I64x\n", *(LONGLONG *)&Duration);
}

EXTERN_C
NTSTATUS
TestFPU()
{
    dprintf("TestFPU begin\n");

    XSTATE_SAVE SaveState;
    NTSTATUS Status;

    Status = KeSaveExtendedProcessorState(XSTATE_MASK_LEGACY, &SaveState);
    if (!NT_SUCCESS(Status))
    {
        goto exit;
    }

    __try
    {
        DoFloatingPointCalculation();
    }
    __finally
    {
        KeRestoreExtendedProcessorState(&SaveState);
    }

exit:
    dprintf("TestFPU end\n");
    return Status;
}
