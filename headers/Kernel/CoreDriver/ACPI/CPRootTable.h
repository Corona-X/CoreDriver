/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* CPRootTable.h - ACPI Root Table Functions                       */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* beeselmane - 1.8.2016   - 8:45 PM EST                           */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/

#ifndef __COREPOWER_CPROOTTABLE__
#define __COREPOWER_CPROOTTABLE__ 1

#include <Corona-X.h>
#include <Kernel/CoreDriver/ACPI/CPBase.h>

typedef struct {
    UInt8 signature[8];
    UInt8 checksum;
    UInt8 manufacturerID[6];
    UInt8 revision;
    UInt32 oldRootTableAddress;
    UInt32 length;
    OSAddress rootTableAddress;
    UInt8 extendedChecksum;
    UInt8 reserved[3];
} OSPackedStructure CPRootDescriptor;

typedef struct {
    CPSystemDescriptorTable();
} OSPackedStructure CPRootTable;

OSShared bool CPRootDescriptorValidate(const CPRootDescriptor *descriptor);
OSShared CPRootTable *CPRootDescriptorGetRootTable(const CPRootDescriptor *descriptor);
OSShared UInt8 *CPRootDescriptorGetManufacturerID(const CPRootDescriptor *descriptor);

OSShared OSCount CPRootTableGetEntryCount(const CPRootTable *table);
OSShared OSUTF8Char **CPRootTableGetEntryNames(const CPRootTable *table);
OSShared OSAddress CPRootTableGetEntry(const CPRootTable *table, OSIndex entry);

#endif /* !defined(__COREPOWER_CPROOTTABLE__) */
