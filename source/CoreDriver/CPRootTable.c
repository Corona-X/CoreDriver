#include <Kernel/CoreDriver/ACPI/CorePower.h>
#include <Kernel/XKSharedTarget.h>
#include <Kernel/XKUtilities.h>

bool CPRootDescriptorValidate(const CPRootDescriptor *descriptor)
{
    const static UInt8 signature[8] = kCPSignatureRootDescriptor;
    
    if (XKMemoryCompare(descriptor->signature, signature, sizeof(signature)))
        return false;
    
    if (descriptor->revision != kCPACPIRevision2) return false;
    if (!CPValidateChecksum(descriptor, 0,  20)) return false;
    if (!CPValidateChecksum(descriptor, 20, 36)) return false;
    
    return true;
}

CPRootTable *CPRootDescriptorGetRootTable(const CPRootDescriptor *descriptor)
{
    CPRootTable *table = ((CPRootTable *)descriptor->rootTableAddress);
    return (CPValidateTable(table, kCPSignatureRootTable) ? table : kOSNullPointer);
}

UInt8 *CPRootDescriptorGetManufacturerID(const CPRootDescriptor *descriptor)
{
    return descriptor->manufacturerID;
}

OSCount CPRootTableGetEntryCount(const CPRootTable *table)
{
    return ((table->length - sizeof(CPRootTable)) / sizeof(OSAddress));
}

// This function is why I hate ACPI
// I used to like ACPI... then the 64 bit addressed started
// coming up with the lower 32 bits in the high 32 bits and
// random junk in the lower 32 bits. I honestly have no clue
// why this is so terrible.....
OSUTF8Char **CPRootTableGetEntryNames(const CPRootTable *table)
{
    OSCount count = CPRootTableGetEntryCount(table);
    OSUTF8Char **entries = XKAllocate((count + 1) * sizeof(OSUTF8Char *)).address;
    OSAddress *tableEntries = ((OSAddress)table) + sizeof(CPRootTable);
    
    for (OSIndex i = 0; i < count; i++)
    {
        UInt64 entry = tableEntries[i];
        entry >>= 32;
        
        entries[i] = XKAllocate(5).address;
        XKMemoryCopy((OSAddress)entry, entries[i], 4);
        entries[i][4] = 0;
    }
    
    return entries;
}

OSAddress CPRootTableGetEntry(const CPRootTable *table, OSIndex entry)
{
    OSAddress *entries = ((OSAddress)table) + sizeof(CPRootTable);
    UInt64 pointerBase = entries[entry];

    return ((UInt64)(pointerBase >> 32));
}
