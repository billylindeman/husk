#ifndef IPLATFORM_H
#define IPLATFORM_H

template <typename PlatformImpl>
class IPlatform {
    void init() {
        static_cast<PlatformImpl*>(this)->init();
    }
};

#endif
