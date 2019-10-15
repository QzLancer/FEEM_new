#pragma once

#include <qglobal.h>

#if defined(OPTIMIZE_LIBRARY)
#  define FEEM_OPTIMIZE_EXPORT Q_DECL_EXPORT
#elif defined(OPTIMIZE_STATIC_LIBRARY)
#  define FEEM_OPTIMIZE_EXPORT
#else
#  define FEEM_OPTIMIZE_EXPORT Q_DECL_IMPORT
#endif
