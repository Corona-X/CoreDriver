#include <Kernel/CoreDriver/ACPI/CorePower.h>
#include <Kernel/XKShared.h>

OSInline bool CPValidateChecksum(UInt8 *data, OSCount from, OSCount to)
{
    UInt8 sum = 0;

    for (OSCount i = from; i < to; i++)
        sum += data[i];

    return !sum;
}

bool CPRootDescriptorValidate(CPRootDescriptor *descriptor)
{
    const static UInt8 signature[8] = kCPRootDescriptorSignature;

    if (XKMemoryCompare(descriptor->signature, signature, sizeof(signature)))
        return false;

    if (descriptor->revision != kCPRevision2) return false;
    if (!CPValidateChecksum(descriptor, 0,  20)) return false;
    if (!CPValidateChecksum(descriptor, 20, 36)) return false;

    return true;
}

CPRootTable *CPRootDescriptorGetRootTable(CPRootDescriptor *descriptor)
{
    CPRootTable *table = ((CPRootTable *)descriptor->rootTableAddress);
    return (CPRootTableValidate(table) ? table : kOSNullPointer);
}

UInt8 *CPRootDescriptorGetManufacturerID(CPRootDescriptor *descriptor)
{
    return descriptor->manufacturerID;
}

bool CPRootTableValidate(CPRootTable *table)
{
    const static UInt8 signature[4] = kCPRootTableSignature;

    if (XKMemoryCompare(table->signature, signature, sizeof(signature)))
        return false;

    return CPValidateChecksum(table, 0, table->length);
}

OSCount CPRootTableGetEntryCount(CPRootTable *table)
{
    return ((table->length - sizeof(CPRootTable)) / sizeof(OSAddress));
}
