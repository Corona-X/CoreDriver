#include <Kernel/CoreDriver/ACPI/CPBase.h>
#include <Kernel/XKSharedTarget.h>
#include <Kernel/XKUtilities.h>
#include <Kernel/XKDebugLog.h>
#include <Kernel/XKLegacy.h>

CPDriverState defaultState;

bool CPValidateChecksum(const UInt8 *data, OSCount from, OSCount to)
{
    UInt8 sum = 0;
    
    for (OSCount i = from; i < to; i++)
        sum += data[i];
    
    return !sum;
}

bool CPValidateTable(const OSAddress base, OSUTF8Char signature[4])
{
    if (CLMemoryCompare(base, signature, 4))
        return false;

    return CPValidateChecksum(base, 0, *((UInt32 *)(base + 4)));
}

void CPShutdownMachine(void)
{
    if (defaultState.isRunningInVirtualMachine) {
        // QEMU lets us just do this...
        XKWriteIOByte(0xF4, 0x00);
    } else {
        // Can't do this quite yet....
    }

    OSEndCode();
}

#if kCXBootloaderCode
    bool CPInitializeForSystemLoader(void)
    {
        CPRootDescriptor *rootDescriptor = SLSystemTableGetACPIRoot(SLSystemTableGetCurrent());

        if (!rootDescriptor)
        {
            XKLog(kXKLogLevelError, "No valid ACPI Root Table found! (Does thie machine have the proper version of ACPI?)\n");
            XKConsoleWaitForInput();

            return false;
        }

        defaultState.isRunningInVirtualMachine = CLMemoryCompare(rootDescriptor, "BOCHS ", 6);
        defaultState.rootTableDescriptor = rootDescriptor;

        XKLog(kXKLogLevelInfo, "Discovered valid ACPI Root Descriptor at %p\n", rootDescriptor);
        XKLog(kXKLogLevelInfo, "ACPI manufacturer is '%06s'\n", CPRootDescriptorGetManufacturerID(rootDescriptor));

        CPRootTable *rootTable = CPRootDescriptorGetRootTable(rootDescriptor);

        if (!rootTable)
        {
            XKLog(kXKLogLevelError, "Could not detect valid ACPI Root Table from the Root Descriptor!\n");
            XKConsoleWaitForInput();

            return false;
        }

        OSUTF8Char **entries = CPRootTableGetEntryNames(rootTable);
        OSCount entryCount = CPRootTableGetEntryCount(rootTable);

        XKLog(kXKLogLevelInfo, "Discovered valid ACPI Root Table at %p\n", rootTable);
        XKLog(kXKLogLevelInfo, "Root Table has %zu entries\n", entryCount);
        XKLog(kXKLogLevelInfo, "Root Table Entries (%p):\n", entries);

        OSIndex interruptEntry = -1;

        for (OSIndex i = 0; i < entryCount; i++)
        {
            if (!CLStringCompare8(entries[i], KCPSignatureInterruptTable))
                interruptEntry = i;

            XKLog(kXKLogLevelInfo, "%zu: %04s\n", i, entries[i]);
            XKFree(entries[i]);
        }

        XKFree(entries);

        if (interruptEntry == -1)
        {
            XKLog(kXKLogLevelError, "Could not locate the interrupt table!\n");
            XKConsoleWaitForInput();

            return false;
        }

        CPInterruptTable *interruptTable = CPRootTableGetEntry(rootTable, interruptEntry);
        bool valid = CPValidateTable(interruptTable, KCPSignatureInterruptTable);

        if (!valid)
        {
            XKLog(kXKLogLevelError, "Interrupt table is not valid at %p!\n", interruptTable);
            XKConsoleWaitForInput();

            return false;
        }

        XKLog(kXKLogLevelInfo, "Interrupt Table discovered at %p (root entry %zu)\n", interruptTable, interruptEntry);
        CPInterruptTableDumpControllers(interruptTable);

        return true;
    }
#endif /* kCXBootloaderCode */
