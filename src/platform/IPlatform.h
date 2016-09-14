#ifndef IPLATFORM_H
#define IPLATFORM_H

template <typename PlatformImpl>
class IPlatform {
    void init() {
        static_cast<PlatformImpl*>(this)->init();
    }

    void printk(const char *format) {
        static_cast<PlatformImpl*>(this)->printf(format);
    }
};

#endif
