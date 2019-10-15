#pragma once

#include <qglobal.h>

#if defined(BOUNCE_LIBRARY)
#  define FEEM_BOUNCE_EXPORT Q_DECL_EXPORT
#elif defined(BOUNCE_STATIC_LIBRARY)
#  define FEEM_BOUNCE_EXPORT
#else
#  define FEEM_BOUNCE_EXPORT Q_DECL_IMPORT
#endif
