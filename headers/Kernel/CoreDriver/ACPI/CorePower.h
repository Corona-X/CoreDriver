/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* CorePower.h - Include all submodules for CorePower (ACPI)       */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* beeselmane - 6.11.2016  - 12:30 PM EST                          */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/

#ifndef __KERNEL_COREDRIVER_COREPOWER__
#define __KERNEL_COREDRIVER_COREPOWER__ 1

#include <Corona-X.h>

#include <System/OSCompilerMacros.h>
#include <System/OSTypes.h>

#define CPSystemDescriptorTable()           \
    UInt8 signature[4];                         \
    UInt32 length;                              \
    UInt8 revision;                             \
    UInt8 checksum;                             \
    UInt8 manufacturerID[6];                    \
    UInt8 manufacturerTableID[8];               \
    UInt32 creatorID;                           \
    UInt32 creatorRevision

#define kCPRootDescriptorSignature "RSD PTR "
#define kCPRootTableSignature      "XSDT"

#define kCPRevision1        0
#define kCPRevision2        2

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
} CPRootTable;

OSShared bool CPRootDescriptorValidate(CPRootDescriptor *descriptor);
OSShared CPRootTable *CPRootDescriptorGetRootTable(CPRootDescriptor *descriptor);
OSShared UInt8 *CPRootDescriptorGetManufacturerID(CPRootDescriptor *descriptor);

OSShared bool CPRootTableValidate(CPRootTable *table);
OSShared OSCount CPRootTableGetEntryCount(CPRootTable *table);

#endif /* !defined(__KERNEL_COREDRIVER_COREPOWER__) */
