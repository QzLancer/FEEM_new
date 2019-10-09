#pragma once

#include <qglobal.h>

#if defined(CORE_LIBRARY)
#  define FEEM_CORE_EXPORT Q_DECL_EXPORT
#elif defined(CORE_STATIC_LIBRARY)
#  define FEEM_CORE_EXPORT
#else
#  define FEEM_CORE_EXPORT Q_DECL_IMPORT
#endif
