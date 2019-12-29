#pragma once

namespace Core {
namespace Constants {

#define STRINGIFY_INTERNAL(x) #x
#define STRINGIFY(x) STRINGIFY_INTERNAL(x)

const char IDE_DISPLAY_NAME[] = "FEEM";
const char IDE_ID[] = "feem";
const char IDE_CASED_ID[] = "FEEM";

#define IDE_VERSION 0.0.1
#define IDE_VERSION_STR STRINGIFY(IDE_VERSION)
#define IDE_VERSION_DISPLAY_DEF 0.0.1

#define IDE_VERSION_MAJOR 0
#define IDE_VERSION_MINOR 0
#define IDE_VERSION_RELEASE 1

const char * const IDE_VERSION_LONG      = IDE_VERSION_STR;
const char * const IDE_VERSION_DISPLAY   = STRINGIFY(IDE_VERSION_DISPLAY_DEF);
const char * const IDE_AUTHOR            = "Poofee";
const char * const IDE_YEAR              = "2019";

#ifdef IDE_REVISION
const char * const IDE_REVISION_STR      = STRINGIFY(IDE_REVISION);
#else
const char * const IDE_REVISION_STR      = "";
#endif

// changes the path where the settings are saved to
#ifdef IDE_SETTINGSVARIANT
const char * const IDE_SETTINGSVARIANT_STR      = STRINGIFY(IDE_SETTINGSVARIANT);
#else
const char * const IDE_SETTINGSVARIANT_STR      = "FEEM";
#endif

#ifdef IDE_COPY_SETTINGS_FROM_VARIANT
const char * const IDE_COPY_SETTINGS_FROM_VARIANT_STR = STRINGIFY(IDE_COPY_SETTINGS_FROM_VARIANT);
#else
const char * const IDE_COPY_SETTINGS_FROM_VARIANT_STR = "";
#endif

#undef IDE_VERSION_DISPLAY_DEF
#undef IDE_VERSION
#undef IDE_VERSION_STR
#undef STRINGIFY
#undef STRINGIFY_INTERNAL

} // Constants
} // Core
