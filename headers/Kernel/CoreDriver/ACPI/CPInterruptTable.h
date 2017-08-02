/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* CPInterruptTable.h - ACPI Interrupt Controller Table            */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* beeselmane - 1.8.2016   - 9:00 PM EST                           */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/

#ifndef __COREPOWER_CPINTERRUPTTABLE__
#define __COREPOWER_CPINTERRUPTTABLE__ 1

#include <Corona-X.h>
#include <Kernel/CoreDriver/ACPI/CPBase.h>

#define kCPInterruptRecordTypeLocal             0
#define kCPInterruptRecordTypeIO                1
#define kCPInterruptRecordTypeSourceOverride    2

typedef struct {
    CPSystemDescriptorTable();
    UInt32 localControllerAddress;
    UInt32 flags;
} OSPackedStructure CPInterruptTable;

typedef struct {
    UInt8 type;
    UInt8 length;
} CPInterruptRecordInfo;

typedef struct {
    CPInterruptRecordInfo info;
    UInt8 processorID;
    UInt8 controllerID;
    UInt32 flags;
} OSPackedStructure CPInterruptRecordLocal;

typedef struct {
    CPInterruptRecordInfo info;
    UInt8 controllerID;
    UInt8 reserved;
    UInt32 address;
    UInt32 interruptBase;
} OSPackedStructure CPInterruptRecordIO;

OSShared void CPInterruptTableDumpControllers(const CPInterruptTable *table);

#endif /* !defined(__COREPOWER_CPINTERRUPTTABLE__) */
