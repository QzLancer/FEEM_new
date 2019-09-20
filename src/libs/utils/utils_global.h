#pragma once

#include <qglobal.h>

#if defined(UTILS_LIBRARY)
#  define FEEM_UTILS_EXPORT Q_DECL_EXPORT
#elif  defined(FEEM_UTILS_STATIC_LIB) // Abuse single files for manual tests
#  define FEEM_UTILS_EXPORT
#else
#  define FEEM_UTILS_EXPORT Q_DECL_IMPORT
#endif
