/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* CPDriverState.h - ACPI Driver State Structure                   */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/
/* beeselmane - 1.8.2016   - 9:00 PM EST                           */
/**=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=**/

#ifndef __COREPOWER_CPDRIVERSTATE__
#define __COREPOWER_CPDRIVERSTATE__ 1

#include <Corona-X.h>
#include <Kernel/CoreDriver/ACPI/CPBase.h>

typedef struct {
    bool isRunningInVirtualMachine;
    OSAddress rootTableDescriptor;
} CPDriverState;

OSShared CPDriverState *CPDriverStateGetCurrent(void);
OSShared CPDriverState *CPDriverStateCopy(OSBuffer (*allocate)(OSSize size));

#endif /* !defined(__COREPOWER_CPDRIVERSTATE__) */
