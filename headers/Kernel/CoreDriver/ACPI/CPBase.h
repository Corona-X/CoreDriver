/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* CPBase.h - Base include for CorePower                           */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* beeselmane - 1.8.2016   - 8:45 PM EST                           */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/

#ifndef __COREPOWER_CPBASE__
#define __COREPOWER_CPBASE__ 1

#include <Corona-X.h>
#include <System/OSCompilerMacros.h>
#include <System/OSTypes.h>

#define kCPSignatureRootDescriptor      "RSD PTR "
#define kCPSignatureRootTable           "XSDT"
#define KCPSignatureInterruptTable      "APIC"

#define kCPACPIRevision1                0
#define kCPACPIRevision2                2

#define CPSystemDescriptorTable()   \
    UInt8 signature[4];             \
    UInt32 length;                  \
    UInt8 revision;                 \
    UInt8 checksum;                 \
    UInt8 manufacturerID[6];        \
    UInt8 manufacturerTableID[8];   \
    UInt32 creatorID;               \
    UInt32 creatorRevision

#if kCXBootloaderCode
    OSShared bool CPInitializeForSystemLoader(void);
#endif /* kCXBootloaderCode */

OSShared bool CPValidateChecksum(const UInt8 *data, OSCount from, OSCount to);
OSShared bool CPValidateTable(const OSAddress base, OSUTF8Char signature[4]);
OSShared OSNoReturn void CPShutdownMachine(void);

#endif /* !defined(__COREPOWER_CPBASE__) */
