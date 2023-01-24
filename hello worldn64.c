#include <ultra64.h>

void main() {
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);
    osViSetSpecialFeatures(OS_VI_GAMMA_OFF);
    osViBlack(TRUE);

    printf("Hello, World!");

    while (1) {
        osViSwapBuffer(osViGetNextFramebuffer());
    }
}
