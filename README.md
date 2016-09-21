
# husk

Husk is a small toy operating system I am developing.  My goals are to develop a basic multi-platform (arm, x86) os kernel and libc/c++, and to make it as easy to understand as possible.

# basic system x86 todo:
[x] Init GDT with basic flat layout for now

[x] Init IDT

[x] Successfully execute software interrupts

[x] PIC Driver / Initialization
    - PIC is initialized and interrupts work / are forwarded correctly to GDT

[-] Wrap ISR assembly stubs for X86 fault handler and forward upstream to a kernel panic
    - Currently I'm using a single catchall for Fault handling but it doesn't actually capture which fault triggered it.. this needs to change
    - Same thing for IRQ's

[ ] Enable paging

[ ] Setup Keyboard handler using IDT



## goals
- Platform Abstraction System
    - C++ based using Interfaces (Look into static-polymorphism and/or Variadic Templates for resolving these)
    - Platform Drivers
        - These will be the platform specific implementations of hardware features (spi, pci)
- Platform Feature abstractions
    - These will be backed by system drivers: For example, There would be a SPIPlatformFeature that would have a backing platform driver.  This would be solved at compile-time by static-polymorphism.
    - Platform features will be used by peripheral drivers
        - For example, you might have a driver for a specific SPI sensor.. This sensor driver would be a peripheral driver and can only access hardware THROUGH a platform feature.
- Scheduler model
    - Basic scheduler model should abstract actual Scheduling algorithm (Likely implemented as a TaskSwichingPlatformFeature)





need to figure out:
