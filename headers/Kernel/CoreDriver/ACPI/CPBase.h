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

#define kCPSignatureRootDescriptor          0x2052545020445352  // "RSD PTR " (Table 5-27 of ACPI 6.3, `Signature` field)
#define kCPSignatureRootTable               0x54445358          // "XSDT" (Table 5-32 of ACPI 6.3, `Signature` field)
#define kCPSignatureFixedDescriptorTable    0x50434146          // "FACP" (Table 5-34 of ACPI 6.3, `Signature` field)
#define KCPSignatureInterruptConfigTable    0x43495041          // "APIC" (Table 5-43 of ACPI 6.3, `Signature` field)

#define kCPRootDescriptorVersionMin         2                   // Current Version in ACPI 6.3 (See Table 5-27, `Revision` field)
#define kCPRootTableVersionMin              1                   // Current Version in ACPI 6.3 (See Table 5-32, `Revision` field)
#define kCPFixedDescriptorMajorVersionMin   6                   // Current Version in ACPI 6.3 (See Table 5-32, `Revision` field)
#define kCPFixedDescriptorMinorVersionMin   3                   // Current Version in ACPI 6.3 (See Table 5-32, `Revision` field)

// Reference: Table 5-25 of ACPI 6.3
#define kCPAddressIdSystemMemory            0x00

// Reference: Table 5-28 of ACPI 6.3
// Note: This is a macro so these fields can be defined in every table more simply.
#define CPSystemDescriptorTable()   \
    UInt32 signature;               \
    UInt32 length;                  \
    UInt8 revision;                 \
    UInt8 checksum;                 \
    UInt8 oemID[6];                 \
    UInt8 oemTableID[8];            \
    UInt8 oemRevision[4];           \
    UInt8 creatorID[4];             \
    UInt8 creatorRevision[4]

// Note: This is just a structure declared as the macro above for convienience.
typedef OSPackedStructure() {
    CPSystemDescriptorTable();
} CPSystemPowerTable;

// Reference: Table 5-27 of ACPI 6.3
typedef OSPackedStructure() {
    UInt64 signature;
    UInt8 checksum;
    UInt8 oemID[6];
    UInt8 revision;
    UInt32 oldRootTablePointer;
    UInt32 length;
    UInt64 rootTablePointer;
    UInt8 extendedChecksum;
    UInt8 reserved[3];
} CPRootDescriptor;

// Reference: Table 5-25 of ACPI 6.3
typedef OSPackedStructure() {
    UInt8 addressSpace;
    UInt8 bitWidth;
    UInt8 bitOffset;
    UInt8 accessSize;
    UInt64 address;
} CPAddressStructure;

// Reference: Table 5-32 of ACPI 6.3
typedef OSPackedStructure() {
    CPSystemDescriptorTable();
    // 64-bit entry pointers follow
} CPRootTable;

// Reference: Table 5-33 of ACPI 6.3
typedef OSPackedStructure() {
    CPSystemDescriptorTable();

    UInt32 oldFirmwareControl;
    UInt32 oldDSDT;

    UInt8 reserved0;
    UInt8 profile;
    UInt16 sciNumber;
    UInt16 smiPort;
    UInt8 acpiEnable;
    UInt8 acpiDisable;
    UInt8 firmwareS4Request;
    UInt8 pstateControl;

    UInt32 oldPM1AEvent;
    UInt32 oldPM1BEvent;
    UInt32 oldPM1AControl;
    UInt32 oldPM1BControl;
    UInt32 oldPM2Control;
    UInt32 oldPMTimer;
    UInt32 oldGPE0;
    UInt32 oldGPE1;

    UInt8 pm1EventLength;
    UInt8 pm1ControlLength;
    UInt8 pm2ControlLength;
    UInt8 pmTimerLength;
    UInt8 gpe0Length;
    UInt8 gpe1Length;
    UInt8 gpe1Base;
    UInt8 cstateControl;

    UInt32 c2Latency;
    UInt32 c3Latency;

    UInt16 cacheFlushSize;
    UInt16 cacheStride;

    UInt8 dutyCycleOffset;
    UInt8 dutyCycleWidth;

    UInt8 dayAlarm;
    UInt8 monthAlarm;
    UInt8 century;

    UInt16 iaBootFlags;
    UInt8 reserved1;
    UInt32 flags;

    CPAddressStructure resetRegister;
    UInt8 resetValue;

    UInt16 armBootFlags;
    UInt8 acpiMinorVersion;

    OSAddress firmwareControlPointer;
    OSAddress dsdtPointer;

    CPAddressStructure pm1aEvent;
    CPAddressStructure pm1bEvent;
    CPAddressStructure pm1aControl;
    CPAddressStructure pm1bControl;
    CPAddressStructure pm2Control;
    CPAddressStructure pmTimer;
    CPAddressStructure gpe0;
    CPAddressStructure gpe1;

    CPAddressStructure sleepControl;
    CPAddressStructure skeeoStatus;

    UInt64 hypervisorIdentity;
} CPFixedDescriptorTable;

// Reference: Table 5-35 of ACPI 6.3
typedef OSEnum(UInt32, CPFixedDescriptorFlags) {
    kCPFixedFlagWBINVDWorks         = 0x00000001,
    kCPFixedFlagWBINVDFlushWorks    = 0x00000002,
    kCPFixedFlagAllCPUsHaveC1       = 0x00000004,
    kCPFixedFlagAllCPUsHaveC2       = 0x00000008,
    kCPFixedFlagNoFixedPowerButton  = 0x00000010,
    kCPFixedFlagNoFixedSleepButton  = 0x00000020,
    kCPFixedFlagNoFixedRTC          = 0x00000040,
    kCPFixedFlagRTCSupportsS4Wake   = 0x00000080,
    kCPFixedFlagTimerIs32Bit        = 0x00000100,
    kCPFixedFlagSupportsDocking     = 0x00000200,
    kCPFixedFlagSupportsResetReg    = 0x00000400,
    kCPFixedFlagSealedCase          = 0x00000800,
    kCPFixedFlagHeadless            = 0x00001000,
    kCPFixedFlagSleepNeedsCPU       = 0x00002000,
    kCPFixedFlagSupportsPCIWake     = 0x00004000,
    kCPFixedFlagWantsPlatformClock  = 0x00008000,
    kCPFixedFlagRTCFlagValidAfterS4 = 0x00010000,
    kCPFixedFlagSupportsRemotePower = 0x00020000,
    kCPFixedFlagAPICMustCluster     = 0x00040000,
    kCPFixedFlagAPICNeedsPhysical   = 0x00080000,
    kCPFixedFlagHardwareReduced     = 0x00100000,
    kCPFixedFlagS0LikeS3            = 0x00200000
};

// Reference: Table 5-43 of ACPI 6.3
typedef OSPackedStructure() {
    CPSystemDescriptorTable();
    UInt32 localIntrCntrAddress;
    UInt32 flags;
    OSAddress interruptControllers[0];
} CPIntrCntrDescriptorTable;

// Reference: Table 5-44 of ACPI 6.3
typedef OSEnum(UInt32, CPInterruptConfigFlags) {
    kCPInterruptConfigHasLegacyCntrl = 0x00000001
};

// Reference: Table 5-46 of ACPI 6.3
typedef OSPackedStructure() {
    UInt8 type;
    UInt8 length;
    UInt8 processorUID;
    UInt8 apicID;
    UInt32 flags;
} CPLocalAPIC;

// Reference: Table 5-48 of ACPI 6.3
typedef OSPackedStructure() {
    UInt8 type;
    UInt8 length;
    UInt8 reserved;
    UInt32 address;
    UInt32 globalInterruptBase;
} CPIOAPIC;

// Reference: Table 5-49 of ACPI 6.3
typedef OSPackedStructure() {
    UInt8 type;
    UInt8 length;
    UInt8 bus;
    UInt8 source; // irq
    UInt32 globalInterrupt;
    UInt16 flags;
} CPIntrSourceOverride;

// Reference: Table 5-52 of ACPI 6.3
typedef OSPackedStructure() {
    UInt8 type;
    UInt8 length;
    UInt8 processorUID;
    UInt16 flags;
    UInt8 nmiLint;
} CPLocalAPICNMI;

#if kCXBootloaderCode
    OSShared bool CPInitializeForSystemLoader(void);
#endif /* kCXBootloaderCode */

OSShared bool CPValidateChecksum(const UInt8 *data, OSCount from, OSCount to);
OSShared bool CPValidateTable(const OSAddress base, OSUTF8Char signature[4]);
OSShared OSNoReturn void CPShutdownMachine(void);

#endif /* !defined(__COREPOWER_CPBASE__) */
