#include <Kernel/CoreDriver/ACPI/CPInterruptTable.h>
#include <Kernel/XKSharedTarget.h>
#include <Kernel/XKUtilities.h>

void CPInterruptTableDumpControllers(const CPInterruptTable *table)
{
    OSOffset offset = 44;
    UInt8 *entryStart = table + 1;

    XKLog(kXKLogLevelVerbose, "Local Controller Address: %p\n", table->localControllerAddress);
    XKLog(kXKLogLevelDebug, "Offset: %zu\nSize: %u\n", offset, table->length);

    while (offset < table->length)
    {
        XKLog(kXKLogLevelDebug, "Offset: %zu\n", offset);
        XKLog(kXKLogLevelDebug, "Size: %u\n", table->length);
        CPInterruptRecordInfo *info = entryStart;

        XKLog(kXKLogLevelDebug, "Type: 0x%02X\n", info->type);
        XKLog(kXKLogLevelDebug, "Length: %u\n", info->length);

        switch (info->type)
        {
            case kCPInterruptRecordTypeLocal: {
                CPInterruptRecordLocal *record = info;
                UInt8 length = info->length;

                XKLog(kXKLogLevelVerbose, "CPU ACPI ID: %u\n", record->processorID);
                XKLog(kXKLogLevelVerbose, "APIC ID:     %u\n", record->controllerID);
                XKLog(kXKLogLevelVerbose, "Enabled:     %s\n", ((record->flags & 1) ? "yes" : "no"));

                entryStart += length;
                offset += length;
            } break;
            case kCPInterruptRecordTypeIO: {
                CPInterruptRecordIO *record = info;
                UInt8 length = info->length;

                XKLog(kXKLogLevelVerbose, "I/O APIC ID: %u\n", record->controllerID);
                XKLog(kXKLogLevelVerbose, "I/O APIC:    0x%X\n", record->address);
                XKLog(kXKLogLevelVerbose, "GSIB:        0x%X\n", record->interruptBase);

                entryStart += length;
                offset += length;
            } break;
            default:
                XKLog(kXKLogLevelVerbose, "Ignoring entry of unknown type '0x%02X'\n", info->type);
                entryStart += info->length;
                offset += info->length;
            break;
        }
    }
}
