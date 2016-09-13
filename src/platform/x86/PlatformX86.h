#ifndef PLATFORM_X86
#define PLATFORM_X86

#include <IPlatform.h>

class PlatformImplX86 : IPlatform<PlatformImplX86> {
public:
    void init();
};

#endif
