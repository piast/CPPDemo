#include "globalconst.h"


//в этой файлик по-хорошему надо вынести все текстовые констаныт и magic numbers,
//но это все как-нибудь потом, и для какого-нибудь серьезного проекта, а не для этой демки

#define IS_DESKTOP_DEVICE 0
#define IS_MOBILE_DEVICE 1
//#define OS_LINUX

#if IS_DESKTOP_DEVICE == 1
    const QString PATH_TO_RESOURCES = "../demoGame/resources";
    const DeviceType DEVICE_TYPE = Desktop;
#endif


#if IS_MOBILE_DEVICE == 1
    const QString PATH_TO_RESOURCES = "assets:";
    const DeviceType DEVICE_TYPE = Mobile;
#endif

const int GAME_ORIGINAL_WIDTH = 762;
const int GAME_ORIGINAL_HEIGHT = 685;

